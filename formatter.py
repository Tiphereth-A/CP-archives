#!/usr/bin/python3
# -*- coding: utf-8 -*-

import hashlib
import os
import random
import re
import subprocess
from logging import Logger, basicConfig, getLogger
from typing import List, Tuple, Any

import click

from tools.cmcleaner.src.comments_cleaner import cpp, python

logger: Logger = getLogger(__name__)
basicConfig(
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
    level=os.getenv('LOG_LEVEL', 'INFO'),
)


def get_filemap(src: str) -> List[Tuple[str, List[str]]]:
    filemap = []
    for filepath, _, filenames in os.walk(src):
        filemap.append((filepath, filenames))
    return filemap


def get_all_files(src: str) -> List[Tuple[str, str]]:
    files = []
    for filepath, _, filenames in os.walk(src):
        for filename in filenames:
            files.append((filepath, filename))
    return files


def get_extname(filename: str) -> str:
    return filename.split('.')[-1]


def md5sum(filepath: str, filename: str) -> str:
    with open(os.path.join(filepath, filename), 'rb') as f:
        md5 = hashlib.md5()
        while True:
            fb = f.read(8096)
            if not fb:
                break
            md5.update(fb)
        f.close()
        return md5.hexdigest()


def wrapper(files: List[Tuple[str, Any]]):
    def inner_wrapper(func):
        logger.info(rf"function '{func.__name__}' called")

        fail_cnt = 0
        for filepath, filename in files:
            try:
                func(filepath, filename)
            except Exception as e:
                logger.info(rf"'{filepath}' '{filename}' failed with exception {e}")
                fail_cnt += 1
        if fail_cnt:
            logger.info(f'{fail_cnt} file(s) failed')

    return inner_wrapper


@click.group()
def cli():
    pass


@cli.command('rne')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_non_ext_files(src: str):
    """remove files with no extension name"""

    @wrapper(get_all_files(src))
    def _remove_non_ext_files(filepath: str, filename: str) -> None:
        if len(filename.split('.')) == 1:
            os.remove(os.path.join(filepath, filename))

    return _remove_non_ext_files


@cli.command('rnf')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_empty_files(src: str):
    """remove empty files"""

    @wrapper(get_all_files(src))
    def _remove_empty_files(filepath: str, filename: str) -> None:
        if not os.path.getsize(os.path.join(filepath, filename)):
            os.remove(os.path.join(filepath, filename))

    return _remove_empty_files


@cli.command('cb')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_blanks(src: str):
    """clean blank in files"""

    @wrapper(get_all_files(src))
    def _remove_blanks(filepath: str, filename: str) -> None:
        with open(os.path.join(filepath, filename), 'r', encoding='utf8') as f:
            code = '\n'.join(filter(bool, f.readlines()))

        code = re.sub(r'^\n+', '', code)
        code = re.sub(r'\s+\n', '\n', code)

        with open(os.path.join(filepath, filename), 'w', encoding='utf8') as f:
            f.write(code)

    return _remove_blanks


@cli.command('cc')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_comments(src: str):
    """clean comments in files"""
    __commands = {
        'c': cpp.clean,
        'cpp': cpp.clean,
        'py': python.clean
    }

    @wrapper(get_all_files(src))
    def _remove_comments(filepath: str, filename: str) -> None:
        with open(os.path.join(filepath, filename), 'r', encoding='utf8') as f:
            code = '\n'.join(filter(bool, f.readlines()))

        code = re.sub(r'\t', ' ' * 4, code)
        code = re.sub(r'\r', '\n', code)

        __commands.get(get_extname(filename), lambda _: None)(code)

        with open(os.path.join(filepath, filename), 'w', encoding='utf8') as f:
            f.write(code)

    return _remove_comments


@cli.command('cr')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_redundant_codes(src: str):
    """clean useless codes in files, such as `#pragma` in C/C++ files"""

    def __cpp(code: List[str]) -> List[str]:
        ret_list: List[str] = []
        for column in code:
            if re.match(r'^\s*#pragma', column):
                continue

            ret_list.append(column)

        return ret_list

    __commands = {
        'c': __cpp,
        'cpp': __cpp,
    }

    @wrapper(get_all_files(src))
    def _remove_redundant_codes(filepath: str, filename: str) -> None:
        code = list(filter(bool, list(open(os.path.join(filepath, filename), 'r', encoding='utf8'))))
        __commands.get(get_extname(filename), lambda _: None)(code)

        with open(os.path.join(filepath, filename), 'w', encoding='utf8') as f:
            f.writelines(code)

    return _remove_redundant_codes


@cli.command('f')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def unify_code_format(src: str):
    """format all files"""

    __commands = {
        'cpp': lambda filepath, filename: ['clang-format', '-style=file', '-i', os.path.join(filepath, filename)],
        'py': lambda filepath, filename: ['autopep8 ', '-i', os.path.join(filepath, filename)]
    }

    @wrapper(get_all_files(src))
    def _unify_code_format(filepath: str, filename: str) -> None:
        subprocess.run(__commands.get(get_extname(filename), lambda _, __: [])(filepath, filename), encoding='utf8',
                       check=True)

    return _unify_code_format


@cli.command('rdf')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_duplicate_files(src: str):
    """remove duplicate files"""

    @wrapper(get_filemap(src))
    def _remove_duplicate_files(filepath: str, filenames: List[str]) -> None:
        if len(filenames) < 2:
            return
        md5_list: List = []
        for filename in filenames:
            current_md5 = md5sum(filepath, filename)
            if current_md5 in md5_list:
                os.remove(os.path.join(filepath, filename))
            else:
                md5_list.append(current_md5)

    return _remove_duplicate_files


@cli.command('rnd')
@click.option('--src', '-s', type=str, help='src folder', default='src')
def remove_empty_folder(src: str):
    """remove empty dirs"""

    @wrapper(get_filemap(src))
    def _remove_empty_folder(filepath: str, filenames: List[str]) -> None:
        if not filenames:
            os.removedirs(filepath)

    return _remove_empty_folder


@cli.command('n')
@click.option('--src', '-s', type=str, help='src folder', default='src')
@click.option('--random-max-int', '-m', help='maximum of rand', type=int, default=2147483647)
def rename_all_files(src: str, max_int: int):
    """rename all files"""

    @wrapper(get_filemap(src))
    def _rename_all_files(filepath: str, filenames: List[str]) -> None:
        filenames.sort()
        cnt: int = 0
        for filename in filenames:
            pre_name = os.path.join(filepath, filename)
            new_name = os.path.join(filepath, rf"{cnt}_{random.randint(0, max_int)}.{get_extname(filename)}")
            os.rename(pre_name, new_name)
            cnt += 1

    return _rename_all_files


if __name__ == '__main__':
    cli()
