#!/usr/bin/python3
# -*- coding: utf-8 -*-

import random
import subprocess

import click
import coloredlogs

from tools import *
from tools.cmcleaner.src.comments_cleaner import cpp, python


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level',
              default='INFO')
def cli(level: str):
    coloredlogs.install(level=level,
                        fmt='%(asctime)s %(levelname)s %(programname)s::%(name)s [%(process)d] %(message)s',
                        field_styles={'asctime': {'color': 'green'},
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
        'cpp': cpp.clean,
        'cs': cpp.clean,
        'java': cpp.clean,
        'js': cpp.clean,
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
        code = list(filter(bool, list(open(full_filename, 'r', encoding='utf8'))))
        code = __commands.get(get_extname(filename), lambda _: _)(code)

        with open(full_filename, 'w', encoding='utf8') as f:
            f.writelines(code)

        now_size = os.path.getsize(full_filename)
        if now_size != prev_size:
            logger.debug(
                rf"'{full_filename}': {prev_size} B -> {now_size} B, {(prev_size - now_size) / prev_size * 100}% saved")

    return remove_redundant_codes


@cli.command('f')
@click.option('-s', '--src', type=str, help='src folder', default='src')
def unify_code_format(src: str):
    """format all files"""

    AUTOPEP8_ARGS: list[str] = ['autopep8', '-i']
    CLANGFORMAT_ARGS: list[str] = ['clang-format', '-style=file:formatter-config\.clang-format', '-i']
    JCF_ARGS_PRE: list[str] = [get_file_in_toolbin('jcf', [('win32', 'jcf-win-64.exe'),
                                                           ('darwin', 'jcf-osx-64'),
                                                           ('cygwin', 'jcf-linux-64'),
                                                           ('linux', 'jcf-linux-64')])]
    JCF_ARGS_SUF: list[str] = ['-clarify', '-inplace', r"-config=formatter-config\jcf.xml"]
    KTLINT_ARGS: list[str] = ['ktlint', '-F']

    __commands = {
        'c': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'cc': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'c++': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'cpp': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'cs': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'cxx': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'h': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'hpp': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'java': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'js': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'kt': lambda filepath, filename: KTLINT_ARGS + [os.path.join(filepath, filename)],
        'm': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'mm': lambda filepath, filename: CLANGFORMAT_ARGS + [os.path.join(filepath, filename)],
        'pas': lambda filepath, filename: JCF_ARGS_PRE + [os.path.join(filepath, filename)] + JCF_ARGS_SUF,
        'py': lambda filepath, filename: AUTOPEP8_ARGS + [os.path.join(filepath, filename)]
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
            new_name = os.path.join(filepath, rf"{cnt}.{get_extname(filename)}")
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


@cli.command('d')
@click.option('-o', '--oj', type=str, prompt='OJ name', help='OJ name')
@click.option('-i', '--pid', type=str, prompt='problem ID', help='problem ID')
@click.option('-e', '--ext-name', type=str, prompt='extension name', help='extension name', default="cpp")
@click.option('--git/--no-git', help='auto commit after process(default) / do nothing after process', default=True)
def default_process(oj: str, pid: str, ext_name: str, git: bool):
    """default process"""

    src: str = rf'.\src\{oj}\{pid}'
    try:
        os.makedirs(src)
    except OSError as e:
        pass

    rename_all_files.callback(src)
    add_new_file.callback(oj, pid, ext_name)
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
        rename_all_files.callback(src)

    if not git:
        return

    subprocess.run(['git', 'add', r'src/\*'], encoding='utf8', check=True)
    subprocess.run(['git', 'commit', '--message', rf'feat: add {oj} {pid}'], encoding='utf8', check=True)
    # subprocess.run(['git', 'push', 'origin', 'main'], encoding='utf8', check=True)


if __name__ == '__main__':
    cli()
