#!/usr/bin/python3
# -*- coding: utf-8 -*-

import random
import re
import subprocess

import click
import coloredlogs

from lib.codecleaner import *
from lib.codecleaner.crc_cpp import clean_redundant_code_cpp
from lib.codecleaner.cls import cpp, python


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level',
              default='INFO')
def cli(level: str):
    coloredlogs.install(milliseconds=True,
                        level=level,
                        fmt='%(asctime)s,%(msecs)03d %(levelname)s %(programname)s::%(name)s [%(process)d] %(message)s',
                        field_styles={'asctime': {'color': 'green'},
                                      'msecs': {'color': 'green'},
                                      'hostname': {'color': 'red'},
                                      'levelname': {'bold': True, 'color': 'magenta'},
                                      'name': {'faint': True, 'color': 'blue'},
                                      'programname': {'bold': True, 'color': 'cyan'},
                                      'process': {'faint': True, 'color': 'green'},
                                      'username': {'color': 'yellow'}},
                        level_styles={'critical': {'bold': True, 'color': 'red'},
                                      'debug': {'color': 'cyan'},
                                      'error': {'color': 'red'},
                                      'info': {'bright': True, 'color': 'white'},
                                      'notice': {'color': 'magenta'},
                                      'spam': {'color': 'green', 'faint': True},
                                      'success': {'bold': True, 'color': 'green'},
                                      'verbose': {'color': 'blue'},
                                      'warning': {'bright': True, 'color': 'yellow'}})


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
        'cc': cpp.clean,
        'c++': cpp.clean,
        'cpp': cpp.clean,
        'cs': cpp.clean,
        'cxx': cpp.clean,
        'h': cpp.clean,
        'hpp': cpp.clean,
        'java': cpp.clean,
        'js': cpp.clean,
        'm': cpp.clean,
        'mm': cpp.clean,
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
        logger.debug(
            rf"'{full_filename}': {prev_size} B -> {now_size} B, {(prev_size - now_size) / prev_size * 100}% saved")

    return remove_comments


@cli.command('cr')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def remove_redundant_codes(src: str):
    """clean useless codes in files, such as `#pragma` in C/C++ files"""

    __commands = {
        'c': clean_redundant_code_cpp,
        'cpp': clean_redundant_code_cpp,
    }

    @log_default(get_all_files(src))
    def remove_redundant_codes(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)
        code = __commands.get(get_extname(filename), lambda _: _)(
            list(filter(bool, list(open(full_filename, 'r', encoding='utf8')))))

        with open(full_filename, 'w', encoding='utf8') as f:
            f.writelines(code)

        now_size = os.path.getsize(full_filename)
        if now_size != prev_size:
            logger.debug(
                rf"'{full_filename}': {prev_size} B -> {now_size} B, {(prev_size - now_size) / prev_size * 100}% saved")

    return remove_redundant_codes


@cli.command('f')
@click.option('-s', '--src', type=str, help='src folder', default='src')
@click.option('--pre/--no-pre', help='pre process / standard (default)', default=False)
def unify_code_format(src: str, pre: bool):
    """format all files"""

    def autopep8_cmd(filepath, filename):
        return ['autopep8', '-i', os.path.join(filepath, filename)]

    def clangformat_cmd(filepath, filename):
        return ['clang-format', rf"-style=file:lint-conf\{'pre' if pre else ''}.clang-format", '-i', os.path.join(filepath, filename)]

    def gofmt_cmd(filepath, filename):
        return ['gofmt', '-s', '-w', os.path.join(filepath, filename)]

    def jcf_cmd(filepath, filename):
        return [get_file_in_toolbin('jcf',
                                    [('win32', 'jcf-win-64.exe'),
                                     ('darwin', 'jcf-osx-64'),
                                     ('cygwin', 'jcf-linux-64'),
                                     ('linux', 'jcf-linux-64')]),
                os.path.join(filepath, filename),
                '-clarify',
                '-inplace',
                r"-config=lint-conf\jcf.xml"]

    def ktlint_cmd(filepath, filename):
        return ['ktlint', '-F', os.path.join(filepath, filename)]

    def rustfmt_cmd(filepath, filename):
        return ['rustfmt', os.path.join(filepath, filename), os.path.join(filepath, filename)]

    __commands = {
        'c': clangformat_cmd,
        'cc': clangformat_cmd,
        'c++': clangformat_cmd,
        'cpp': clangformat_cmd,
        'cs': clangformat_cmd,
        'cxx': clangformat_cmd,
        'go': gofmt_cmd,
        'h': clangformat_cmd,
        'hpp': clangformat_cmd,
        'java': clangformat_cmd,
        'js': clangformat_cmd,
        'kt': ktlint_cmd,
        'm': clangformat_cmd,
        'mm': clangformat_cmd,
        'pas': jcf_cmd,
        'py': autopep8_cmd,
        'rs': rustfmt_cmd
    }

    @log_default(get_all_files(src))
    def unify_code_format(filepath: str, filename: str, logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, filename)
        prev_size = os.path.getsize(full_filename)

        subprocess.run(__commands.get(get_extname(filename), lambda _, __: ['echo', rf"Format: unknown type: ({_}, {__})"])(filepath, filename), encoding='utf8',
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
def rename_all_files(src: str):
    """rename all files"""

    @log_default(get_filemap(src))
    def rename_all_files(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        tmp_filenames = [rf"{i}_{random.randint(0, max(2147483647, len(filenames)))}.{get_extname(filenames[i])}" for i
                         in range(0, len(filenames))]
        for (filename, tmp_filename) in zip(filenames, tmp_filenames):
            pre_name = os.path.join(filepath, filename)
            new_name = os.path.join(filepath, tmp_filename)
            os.rename(pre_name, new_name)

            logger.debug(rf"'{pre_name}' -> '{new_name}'")

        cnt: int = 0
        for filename in tmp_filenames:
            pre_name = os.path.join(filepath, filename)
            new_name = os.path.join(filepath,
                                    rf"{cnt}.{get_extname(filename)}")
            os.rename(pre_name, new_name)
            cnt += 1

            logger.debug(rf"'{pre_name}' -> '{new_name}'")

    return rename_all_files


@cli.command('n')
@click.option('-o', '--oj', type=str, help='OJ name', required=True)
@click.option('-i', '--pid', type=str, help='problem ID', required=True)
@click.option('-e', '--ext-name', type=str, help='extension name', default="cpp")
def add_new_file(oj: str, pid: str, ext_name: str):
    """add new file, and copy content in clipboard to the new file"""

    src: str = rf'.\src\{oj}\{pid}'
    try:
        os.makedirs(src)
    except OSError as e:
        pass

    @log_default(get_filemap(src))
    def add_new_file(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        full_filename = os.path.join(filepath, rf"{len(filenames)}.{ext_name}")
        with open(full_filename, 'w', encoding='utf8') as f:
            f.write(get_clipboard_text())
            logger.info(rf"'{full_filename}' created")

    return add_new_file


@cli.command('t')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def test_all_files(src: str):
    """test all files"""

    def gcc_cmd(filepath, filename):
        return ['gcc', '-std=c20', '-O2', os.path.join(filepath, filename)]

    def gpp_cmd(filepath, filename):
        return ['g++', '-std=c++20', '-O2', os.path.join(filepath, filename)]

    __commands = {
        'c': gcc_cmd,
        'c++': gpp_cmd,
        'cpp': gpp_cmd,
        'cxx': gpp_cmd
    }

    @log_default(get_filemap(src))
    def test_all_files(filepath: str, filenames: list[str], logger: logging.Logger) -> None:
        success_cnt: int = 0
        failed_cnt: int = 0
        for filename in filenames:
            try:
                subprocess.run(__commands.get(get_extname(filename), lambda _, __: ['echo', rf"Test: unknown type: ({_}, {__})"])(filepath, filename), encoding='utf8',
                               check=True)
                success_cnt += 1
            except Exception as e:
                failed_cnt += 1

        logger.debug(
            rf"{filepath}: {success_cnt} file(s) OK, {failed_cnt} file(s) failed")

    return test_all_files


@cli.command('doall')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def do_all(src: str):
    """do all"""

    loop_max: int = 2

    rename_all_files.callback(src)
    unify_code_format.callback(src, True)
    remove_comments.callback(src)
    unify_code_format.callback(src, True)
    remove_blanks.callback(src)
    for i in range(loop_max):
        remove_redundant_codes.callback(src)
        unify_code_format.callback(src, True)
    unify_code_format.callback(src, False)
    remove_comments.callback(src)
    unify_code_format.callback(src, False)
    remove_blanks.callback(src)
    unify_code_format.callback(src, False)

    prev_cnt = len(get_all_files(src))
    remove_non_ext_files.callback(src)
    remove_empty_files.callback(src)
    remove_duplicate_files.callback(src)
    next_cnt = len(get_all_files(src))
    if prev_cnt != next_cnt:
        rename_all_files.callback(src)


@cli.command('d')
@click.option('-o', '--oj', type=str, prompt='OJ name', help='OJ name')
@click.option('-i', '--pid', type=str, prompt='problem ID', help='problem ID')
@click.option('-e', '--ext-name', type=str, prompt='extension name', help='extension name', default="cpp")
@click.option('--git/--no-git', help='auto commit after process(default) / do nothing after process', default=True)
@click.option('--amend/--no-amend', default=True)
def default_process(oj: str, pid: str, ext_name: str, git: bool, amend: bool):
    """default process"""

    src: str = rf'.\src\{oj}\{pid}'
    try:
        os.makedirs(src)
    except OSError as e:
        pass

    rename_all_files.callback(src)
    add_new_file.callback(oj, pid, ext_name)
    do_all.callback(src)
    
    if git:
        subprocess.run(['git', 'add', r'src/\*'],
                       encoding='utf8',
                       check=True)
        if amend:
            subprocess.run(['git', 'commit', '--amend', '--message', rf'build: upload'],
                           encoding='utf8',
                           check=True)
        else:
            subprocess.run(['git', 'commit', '--message', rf'feat: add {oj} {pid}'],
                           encoding='utf8',
                           check=True)


if __name__ == '__main__':
    cli()
