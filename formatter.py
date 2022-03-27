import hashlib
import os
import random
import re
import subprocess
from logging import Logger, basicConfig, getLogger
from typing import List, Tuple, Any

from tools.cmcleaner.src.comments_cleaner import cpp, python

logger = getLogger(__name__)  # type: Logger
basicConfig(
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
    level=os.getenv('LOG_LEVEL', 'INFO'),
)


def get_filemap(src: str) -> List[Tuple[str, List[str]]]:
    filemap = []
    for filepath, dirnames, filenames in os.walk(src):
        filemap.append((filepath, filenames))
    return filemap


def get_all_files(src: str) -> List[Tuple[str, str]]:
    files = []
    for filepath, dirnames, filenames in os.walk(src):
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

        success_cnt, fail_cnt = 0, 0
        for filepath, filename in files:
            try:
                func(filepath, filename)
                success_cnt += 1
            except Exception as e:
                logger.info(rf"'{filepath}' '{filename}' failed with exception {e}")
                fail_cnt += 1

        logger.info(f'{success_cnt} file(s) succeed, {fail_cnt} file(s) failed')

    return inner_wrapper


def remove_non_ext_and_empty_files(src: str):
    @wrapper(get_all_files(src))
    def _remove_non_ext_and_empty_files(filepath: str, filename: str) -> None:
        if len(filename.split('.')) == 1 or not os.path.getsize(os.path.join(filepath, filename)):
            os.remove(os.path.join(filepath, filename))

    return _remove_non_ext_and_empty_files


def remove_redundant_comments_and_blanks(src: str):
    @wrapper(get_all_files(src))
    def _remove_redundant_comments_and_blanks(filepath: str, filename: str) -> None:
        with open(os.path.join(filepath, filename), 'r', encoding='utf8') as f:
            code = '\n'.join(filter(bool, f.readlines()))

        code = re.sub(r'\t', ' ' * 4, code)
        code = re.sub(r'\r', '\n', code)

        extname = get_extname(filename)
        if extname == 'cpp' or extname == 'c' or extname == 'java':
            code = cpp.clean(code)
        elif extname == 'py':
            code = python.clean(code)

        code = re.sub(r'^\n+', '', code)
        code = re.sub(r'\s+\n', '\n', code)

        with open(os.path.join(filepath, filename), 'w', encoding='utf8') as f:
            f.write(code)

    return _remove_redundant_comments_and_blanks


def remove_redundant_codes(src: str):
    def __cpp(code: List[str]) -> List[str]:
        ret_list: List[str] = []
        for column in code:
            if re.match(r'^\s*#pragma', column):
                continue

            ret_list.append(column)

        return ret_list

    @wrapper(get_all_files(src))
    def _remove_redundant_codes(filepath: str, filename: str) -> None:
        code: List[str] = []
        with open(os.path.join(filepath, filename), 'r', encoding='utf8') as f:
            code = list(filter(bool, f.readlines()))

        extname = get_extname(filename)
        if extname == 'cpp' or extname == 'c':
            code = __cpp(code)

        with open(os.path.join(filepath, filename), 'w', encoding='utf8') as f:
            f.writelines(code)

    return _remove_redundant_codes


def unify_code_format(src: str):
    @wrapper(get_all_files(src))
    def _unify_code_format(filepath: str, filename: str) -> None:
        extname = get_extname(filename)
        if extname == 'cpp':
            subprocess.run(['clang-format', '-style=file', '-i', os.path.join(filepath, filename)], encoding='utf8',
                           check=True)
        elif extname == 'py':
            subprocess.run(['autopep8 ', '-i', os.path.join(filepath, filename)], encoding='utf8', check=True)

    return _unify_code_format


def remove_duplicate_files(src: str):
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


def remove_empty_folder(src: str):
    @wrapper(get_filemap(src))
    def _remove_empty_folder(filepath: str, filenames: List[str]) -> None:
        if not filenames:
            os.removedirs(filepath)

    return _remove_empty_folder


def rename_all_files(src: str):
    @wrapper(get_filemap(src))
    def _rename_all_files(filepath: str, filenames: List[str]) -> None:
        filenames.sort()
        cnt: int = 0
        for filename in filenames:
            pre_name = os.path.join(filepath, filename)
            new_name = os.path.join(filepath, rf"{cnt}_{random.randint(0, 2147483648)}.{filename.split('.')[-1]}")
            os.rename(pre_name, new_name)
            cnt += 1

    return _rename_all_files


DIR = 'src'
if __name__ == '__main__':
    remove_non_ext_and_empty_files(DIR)
    unify_code_format(DIR)
    remove_redundant_comments_and_blanks(DIR)
    remove_redundant_codes(DIR)
    remove_non_ext_and_empty_files(DIR)
    unify_code_format(DIR)
    remove_duplicate_files(DIR)
    remove_empty_folder(DIR)
    rename_all_files(DIR)
