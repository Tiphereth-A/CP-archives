import hashlib
import logging
import os
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
                logger.warning(
                    rf"({filepath}, {filename}) failed with exception '{e}'")
                traceback.print_exc()
                fail_cnt += 1
        if fail_cnt:
            logger.warning(f'{fail_cnt} file(s) failed')

        logger.info('finished')

    return _log_default


def remove_file(full_filename: str, logger: logging.Logger) -> None:
    os.remove(full_filename)
    logger.debug(rf"'{full_filename}' removed")


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
