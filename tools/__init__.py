import hashlib
import logging
import os
import re
import sys
import tkinter as tk
import traceback
from typing import Any


def get_clipboard_text():
    root = tk.Tk()
    root.withdraw()
    return root.clipboard_get()


def get_filemap(src: str) -> list[tuple[str, list[str]]]:
    filemap = []
    for filepath, _, filenames in os.walk(src):
        filemap.append((filepath, filenames))
    return filemap


def get_all_files(src: str) -> list[tuple[str, str]]:
    files = []
    for filepath, _, filenames in os.walk(src):
        for filename in filenames:
            files.append((filepath, filename))
    return files


def md5sum(full_filename: str) -> str:
    with open(full_filename, 'rb') as f:
        md5 = hashlib.md5()
        while True:
            fb = f.read(8096)
            if not fb:
                break
            md5.update(fb)
        f.close()
        return md5.hexdigest()


def get_extname(filename: str) -> str:
    return filename.split('.')[-1]


def log_default(files: list[tuple[str, Any]]):
    def _log_default(func):
        logger: logging.Logger = logging.getLogger(func.__name__)

        fail_cnt = 0
        for filepath, filename in files:
            try:
                logger.debug(rf"running with ({filepath}, {filename})")
                func(filepath, filename, logger)
                logger.debug(rf"({filepath}, {filename}) succeed")
            except Exception as e:
                logger.warning(rf"({filepath}, {filename}) failed with exception '{e}'")
                traceback.print_exc()
                fail_cnt += 1
        if fail_cnt:
            logger.warning(f'{fail_cnt} file(s) failed')

        logger.info('finished')

    return _log_default


def remove_file(full_filename: str, logger: logging.Logger) -> None:
    os.remove(full_filename)
    logger.debug(rf"'{full_filename}' removed")


def clean_redundant_code_cpp(code: list[str]) -> list[str]:
    new_code: list[str] = []

    # remove #pragma
    for column in code:
        if re.search(r'^\s*#pragma', column):
            continue
        new_code.append(column)
    code, new_code = new_code, []

    # remove unused macro, typedef and const
    has_unused_macros = True
    while has_unused_macros:
        has_unused_macros = False
        code_content: str = '\n'.join(code)
        skip_next_column: bool = False

        for column in code:
            if skip_next_column:
                skip_next_column = bool(re.search(r'\\n*', column))
                continue

            # capture `#define macros`
            match_res = re.search(r'^\s*?#\s*?define\s+?(\w+)', column)
            # capture `using Tp = type;`
            if not match_res:
                match_res = re.search(r'^\s*?using\s+?(\w+)\s*?(?==)', column)
            # capture `typedef type Tp`
            if not match_res:
                match_res = re.search(r'(?<=typedef)\s(?:[ \w]+)\s(\w+)', column)
            # capture `const type N = x;`, `const type N = f(x, y);`, `const type N[xxx] = {yyy, zzz};`
            if not match_res:
                match_res = re.search(r'(?<=const)\s(?:\S+)\s(\w+)(?=(?:\[\w+\])*\s?=\s?(?:\(.+?\))*?(?:\{.+?\})*?[^,]*?)', column)

            if match_res:
                if len(re.split(rf'\b{match_res.group(1)}\b', code_content)) == 2:
                    has_unused_macros = True
                    skip_next_column = bool(re.search(r'\\n*', column))
                    continue

            new_code.append(column)
        code, new_code = new_code, []

    return code


__TOOL_BIN_ = r"./tools/bin/{_folder}/{_name}"
__PLATFORM_ = sys.platform


def get_file_in_toolbin(folder: str, names: list[tuple[str, str]]):
    name: str = ''
    for k, v in names:
        if __PLATFORM_.startswith(k):
            name = v
            break
    if not name:
        raise KeyError()

    return __TOOL_BIN_.format(_folder=folder, _name=name)
