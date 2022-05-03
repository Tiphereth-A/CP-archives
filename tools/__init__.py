import hashlib
import os
import tkinter as tk


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
