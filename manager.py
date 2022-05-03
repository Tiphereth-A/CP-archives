#!/usr/bin/python3
# -*- coding: utf-8 -*-

import logging
import os
import random
import re
import subprocess

import click

from tools import get_clipboard_text, get_filemap, get_all_files, md5sum, get_extname, log_default, remove_file
from tools.cmcleaner.src.comments_cleaner import cpp, python


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level', default='INFO')
def cli(level: str):
    logging.basicConfig(level=level, format='%(asctime)s [%(levelname)s] <%(name)s> %(message)s')


@cli.command('rne')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_non_ext_files(src: str):
    """remove files with no extension name"""

    @log_default(get_all_files(src))
    def remove_non_ext_files(filepath: str, filename: str, logger: logging.Logger) -> None:
        if len(filename.split('.')) == 1:
            full_filename = os.path.join(filepath, filename)
            remove_file(full_filename, logger)

    return remove_non_ext_files


@cli.command('rnf')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_empty_files(src: str):
    """remove empty files"""

    @log_default(get_all_files(src))
    def remove_empty_files(filepath: str, filename: str, logger: logging.Logger) -> None:
        if not os.path.getsize(os.path.join(filepath, filename)):
            full_filename = os.path.join(filepath, filename)
            remove_file(full_filename, logger)

    return remove_empty_files


@cli.command('cb')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_blanks(src: str):
    """clean blank in files"""

    @log_default(get_all_files(src))
    def remove_blanks(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)
        with open(full_filename, 'r', encoding='utf8') as f:
            code = '\n'.join(filter(bool, f.readlines()))

        code = re.sub(r'\s+\n', '\n', code)
        code = re.sub(r'^\n+', '', code)

        with open(full_filename, 'w', encoding='utf8') as f:
            f.write(code)

        now_size = os.path.getsize(full_filename)
        logger.debug(rf"'{full_filename}': {prev_size} B -> {now_size} B")

    return remove_blanks


@cli.command('cc')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_comments(src: str):
    """clean comments in files"""
    __commands = {
        'c': cpp.clean,
        'cpp': cpp.clean,
        'py': python.clean
    }

    @log_default(get_all_files(src))
    def remove_comments(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)
        with open(full_filename, 'r', encoding='utf8') as f:
            code = '\n'.join(filter(bool, f.readlines()))

        code = re.sub(r'\t', ' ' * 4, code)
        code = re.sub(r'\r', '\n', code)
        code = re.sub(r'\n\n', '\n', code)

        code = __commands.get(get_extname(filename), lambda _: _)(code)

        with open(full_filename, 'w', encoding='utf8') as f:
            f.write(code)

        now_size = os.path.getsize(full_filename)
        logger.debug(rf"'{full_filename}': {prev_size} B -> {now_size} B, {(prev_size-now_size)/prev_size*100}% saved")

    return remove_comments


@cli.command('cr')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_redundant_codes(src: str):
    """clean useless codes in files, such as `#pragma` in C/C++ files"""

    def __cpp(code: list[str]) -> list[str]:
        ret_list: list[str] = []
        for column in code:
            if re.match(r'^\s*#pragma', column):
                continue

            ret_list.append(column)

        return ret_list

    __commands = {
        'c': __cpp,
        'cpp': __cpp,
    }

    @log_default(get_all_files(src))
    def remove_redundant_codes(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)
        code = list(filter(bool, list(open(full_filename, 'r', encoding='utf8'))))
        __commands.get(get_extname(filename), lambda _: None)(code)

        with open(full_filename, 'w', encoding='utf8') as f:
            f.writelines(code)

        now_size = os.path.getsize(full_filename)
        logger.debug(rf"'{full_filename}': {prev_size} B -> {now_size} B, {(prev_size-now_size)/prev_size*100}% saved")

    return remove_redundant_codes


@cli.command('f')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def unify_code_format(src: str):
    """format all files"""

    __commands = {
        'cpp': lambda filepath, filename: ['clang-format', '-style=file', '-i', os.path.join(filepath, filename)],
        'py': lambda filepath, filename: ['autopep8', '-i', os.path.join(filepath, filename)]
    }

    @log_default(get_all_files(src))
    def unify_code_format(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)

        subprocess.run(__commands.get(get_extname(filename), lambda _, __: [])(filepath, filename), encoding='utf8',
                       check=True)

        now_size = os.path.getsize(full_filename)
        logger.debug(rf"'{full_filename}': {prev_size} B -> {now_size} B")

    return unify_code_format


@cli.command('rdf')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_duplicate_files(src: str):
    """remove duplicate files"""

    @log_default(get_filemap(src))
    def remove_duplicate_files(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        prev_len = len(filenames)

        if len(filenames) < 2:
            return
        md5_list: list = []
        for filename in filenames:
            full_filename = os.path.join(filepath, filename)
            current_md5 = md5sum(full_filename)
            logger.debug(rf"MD5 of '{full_filename}': {current_md5}")

            if current_md5 in md5_list:
                remove_file(full_filename, logger)
            else:
                md5_list.append(current_md5)

        now_len = len(md5_list)
        logger.debug(rf"'{filepath}': {prev_len} file(s) -> {now_len} file(s)")

    return remove_duplicate_files


@cli.command('rnd')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_empty_folder(src: str):
    """remove empty dirs"""

    @log_default(get_filemap(src))
    def remove_empty_folder(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        logger.debug(rf"{filepath} has {len(filenames)} file(s)")

        if not filenames:
            os.removedirs(filepath)

    return remove_empty_folder


@cli.command('rn')
@click.option('-s', '--src', type=str, help='src folder', default='src')
@click.option('-m', '--max-int', help='maximum of rand', type=int, default=2147483647)
def rename_all_files(src: str, max_int: int):
    """rename all files"""

    @log_default(get_filemap(src))
    def rename_all_files(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        filenames.sort()
        cnt: int = 0
        for filename in filenames:
            pre_name = os.path.join(filepath, filename)
            new_name = os.path.join(filepath, rf"{cnt}_{random.randint(0, max_int)}.{get_extname(filename)}")
            os.rename(pre_name, new_name)
            cnt += 1

            logger.debug(rf"'{pre_name}' -> '{new_name}'")

    return rename_all_files


@cli.command('n')
@click.option('-o', '--oj', type=str, help='OJ name', required=True)
@click.option('-i', '--id', type=str, help='problem ID', required=True)
@click.option('-e', '--ext-name', type=str, help='extension name', default="cpp")
@click.option('-m', '--max-int', help='maximum of rand', type=int, default=2147483647)
def add_new_file(oj: str, id: str, ext_name: str, max_int: int):
    """add new file, and copy content in clipboard to the new file"""

    src: str = rf'.\src\{oj}\{id}'
    try:
        os.makedirs(src)
    except:
        pass

    @log_default(get_filemap(src))
    def add_new_file(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, rf"{len(filenames)}_{random.randint(0, max_int)}.{ext_name}")
        with open(full_filename, 'w', encoding='utf8') as f:
            f.write(get_clipboard_text())
            logger.info(rf"'{full_filename}' created")

    return add_new_file


@cli.command('d')
@click.option('-o', '--oj', type=str, prompt='OJ name', help='OJ name')
@click.option('-i', '--id', type=str, prompt='problem ID', help='problem ID')
@click.option('-e', '--ext-name', type=str, prompt='extension name', help='extension name', default="cpp")
@click.option('-m', '--max-int', help='maximum of rand', type=int, default=2147483647)
@click.option('--git/--no-git', help='auto commit after process(default) / do nothing after process', default=True)
def default_process(oj: str, id: str, ext_name: str, max_int: int, git: bool):
    """default process"""

    src: str = rf'.\src\{oj}\{id}'
    try:
        os.makedirs(src)
    except:
        pass

    add_new_file.callback(oj, id, ext_name, max_int)
    unify_code_format.callback(src)
    remove_comments.callback(src)
    remove_blanks.callback(src)
    remove_redundant_codes.callback(src)
    unify_code_format.callback(src)

    prev_cnt = len(get_all_files(src))
    remove_non_ext_files.callback(src)
    remove_empty_files.callback(src)
    remove_duplicate_files.callback(src)
    next_cnt = len(get_all_files(src))
    if prev_cnt != next_cnt:
        rename_all_files.callback(src, max_int)

    if not git:
        return

    subprocess.run(['git', 'add', r'src/\*'], encoding='utf8', check=True)
    subprocess.run(['git', 'commit', '--message', rf'feat: add {oj} {id}'], encoding='utf8', check=True)
    # subprocess.run(['git', 'push', 'origin', 'main'], encoding='utf8', check=True)


if __name__ == '__main__':
    cli()
