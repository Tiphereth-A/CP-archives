import hashlib
import logging
import os
import tkinter as tk
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


def get_extname(filename: str) -> str:
    return filename.split('.')[-1]


def log_default(files: list[tuple[str, Any]]):
    def _log_default(func):
        logger: logging.Logger = logging.getLogger(func.__name__)
        logger.info(rf"function '{func.__name__}' called")

        fail_cnt = 0
        for filepath, filename in files:
            try:
                logger.debug(rf"running {func.__name__}('{filepath}', '{filename}')")
                func(filepath, filename)
            except Exception as e:
                logger.warning(rf"'{filepath}' '{filename}' failed with exception {e}")
                fail_cnt += 1
        if fail_cnt:
            logger.warning(f'{fail_cnt} file(s) failed')

        logger.info(rf"function '{func.__name__}' finished")
    return _log_default
