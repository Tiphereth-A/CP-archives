import hashlib
import logging
import os
import re
import sys
import tkinter as tk
import traceback
from enum import IntEnum, auto
from random import randint
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


RE_PRAGMA = re.compile(r'^\s*#pragma')
RE_DEFINE = re.compile(r'^\s*?#\s*?define\s+?(\w+)')
RE_TEMPLATE = re.compile(r'^\s*?template')
STR_TEMPLATE_WITH_ARGS = r'template\s*<(?:\w+?\s*?\w*?(?:\(.+?\)|\{.+?}|\[.+?]|<.+?>)*?,?)+>'
RE_TEMPLATE_WITH_ARGS = re.compile(STR_TEMPLATE_WITH_ARGS)
RE_USING_TYPEDEF = re.compile(rf'^(?:\s*?{STR_TEMPLATE_WITH_ARGS}\s*)?\s*?using\s+?(\w+)\s*?(?==)')
RE_TYPEDEF = re.compile(r'(?<=typedef)\s[ \w]+\s(\w+)')
RE_CONST = re.compile(r'(?<=const)\s\S+\s(\w+)(?=(?:\[\w+])*\s?=\s?(?:\w*?\(.+?\))*?(?:\{.+?})*?[^,]*?)')
RE_IF1 = re.compile(r'^ *# *if 1\n')
RE_IF0 = re.compile(r'^ *# *if 0\n')
RE_IFDEF = re.compile(r'^\s*#\s*ifdef\s+(\w+)')
RE_IFNDEF = re.compile(r'^\s*#\s*ifndef\s+(\w+)')
RE_ELSE = re.compile(r'^\s*#\s*else')
RE_ENDIF = re.compile(r'^\s*#\s*endif')
RE_DEFINE_FLAG = re.compile(r'^\s*#\s*define\s+(\w+)\n')
RE_UNDEF_FLAG = re.compile(r'^\s*#\s*undef\s+(\w+)\n')


def clean_redundant_code_cpp(code: list[str]) -> list[str]:
    class DefineBlockState(IntEnum):
        plaintext = auto()
        in_ifdef = auto()
        in_ifndef = auto()

    class DeleteState(IntEnum):
        skip = auto()
        pre = auto()
        suc = auto()

    code = [i if i.endswith('\n') else i + '\n' for i in code]
    new_code: list[str] = []

    # remove #pragma
    for column in code:
        if re.search(RE_PRAGMA, column):
            continue
        new_code.append(column)
    code, new_code = new_code, []

    # remove break of template declaration
    past_col: str = ''
    for column in code:
        if re.search(RE_TEMPLATE, column):
            past_col += column
            past_col = past_col.removesuffix('\n') + ' '
            continue
        new_code.append(past_col + column)
        past_col = ''
    code, new_code = new_code, []

    # remove some skipped #ifdef and #ifndef block
    rand_token = randint(114514, 1919810)
    for column in code:
        if re.search(RE_IF1, column):
            column = f"#ifdef ALWAYS_TRUE_{rand_token}\n"
        elif re.search(RE_IF0, column):
            column = f"#ifdef ALWAYS_FALSE_{rand_token}\n"
        new_code.append(column)
    code, new_code = new_code, []

    defined_flag: set[str] = {'ONLINE_JUDGE', f"ALWAYS_TRUE_{rand_token}", "DISABLE_PRAGMA_", "__GNUG__"}
    stack_index: list[int] = []
    stack_else_index: list[int] = [0]
    stack_status: list[DefineBlockState] = [DefineBlockState.plaintext]
    line_num: int = 0
    would_be_deleted_range: list[tuple[int, int, int, DeleteState]] = []

    for column in code:
        line_num += 1
        match_res = re.search(RE_DEFINE_FLAG, column)
        if match_res:
            defined_flag.add(match_res.group(1))
            continue

        match_res = re.search(RE_UNDEF_FLAG, column)
        if match_res:
            if match_res.group(1) in defined_flag:
                defined_flag.remove(match_res.group(1))
            continue

        match_res = re.search(RE_IFDEF, column)
        if match_res:
            stack_index.append(line_num)
            stack_status.append(DefineBlockState.in_ifdef)
            continue
        match_res = re.search(RE_IFNDEF, column)
        if match_res:
            stack_index.append(line_num)
            stack_status.append(DefineBlockState.in_ifndef)
            continue

        if stack_status[-1] != DefineBlockState.plaintext:
            match_res = re.search(RE_ELSE, column)
            if match_res:
                stack_else_index.append(line_num)
                continue
            match_res = re.search(RE_ENDIF, column)
            if not match_res:
                continue
            delete_tuple: tuple[int, int, int, DeleteState] = (0, 0, 0, DeleteState.skip)
            if stack_status[-1] == DefineBlockState.in_ifdef:
                prev_idx: int = stack_index.pop()
                match_res = re.search(RE_IFDEF, code[prev_idx - 1])
                if match_res.group(1) not in defined_flag:
                    if prev_idx < stack_else_index[-1] < line_num:
                        delete_tuple = (prev_idx, stack_else_index.pop(), line_num, DeleteState.pre)
                    else:
                        delete_tuple = (prev_idx, line_num, line_num, DeleteState.pre)
                elif prev_idx <= stack_else_index[-1] <= line_num:
                    delete_tuple = (prev_idx, stack_else_index.pop(), line_num, DeleteState.suc)
            elif stack_status[-1] == DefineBlockState.in_ifndef:
                prev_idx: int = stack_index.pop()
                match_res = re.search(RE_IFNDEF, code[prev_idx - 1])
                if match_res.group(1) in defined_flag:
                    if prev_idx <= stack_else_index[-1] <= line_num:
                        delete_tuple = (prev_idx, stack_else_index.pop(), line_num, DeleteState.pre)
                    else:
                        delete_tuple = (prev_idx, line_num, line_num, DeleteState.pre)
                elif prev_idx < stack_else_index[-1] < line_num:
                    delete_tuple = (prev_idx, stack_else_index.pop(), line_num, DeleteState.suc)
            else:
                raise ValueError(f"Unknown status: {stack_status[-1]} at line {line_num}")

            if delete_tuple:
                would_be_deleted_range.append(delete_tuple)

            stack_status.pop()
            continue

    line_num = 0
    now_del_range: tuple[int, int, int, DeleteState] = (0, 0, 0, DeleteState.skip)
    for column in code:
        line_num += 1
        if line_num > now_del_range[2]:
            if would_be_deleted_range:
                now_del_range = would_be_deleted_range.pop(0)
        if now_del_range[3] == DeleteState.pre:
            if now_del_range[0] < line_num < now_del_range[1]:
                continue
            if now_del_range[1] == now_del_range[2] and (line_num == now_del_range[0] or line_num == now_del_range[1]):
                continue
        elif now_del_range[3] == DeleteState.suc:
            if now_del_range[1] <= line_num < now_del_range[2]:
                continue
        new_code.append(column)
    code, new_code = new_code, []

    for column in code:
        match_res = re.search(RE_IFDEF, column)
        if not match_res:
            match_res = re.search(RE_IFNDEF, column)
        if not match_res:
            match_res = re.search(RE_ELSE, column)
        if not match_res:
            match_res = re.search(RE_ENDIF, column)

        if match_res:
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
            match_res = re.search(RE_DEFINE, column)
            # capture `using Tp = type;`, `template <...> using Tp = type;`
            if not match_res:
                match_res = re.search(RE_USING_TYPEDEF, column)
            # capture `typedef type Tp`
            if not match_res:
                match_res = re.search(RE_TYPEDEF, column)
            # capture `const type N = x;`, `const type N = f(x, y);`, `const type N[xxx] = {yyy, zzz};`
            if not match_res:
                match_res = re.search(RE_CONST, column)

            if match_res:
                if len(re.split(rf'\b{match_res.group(1)}\b', code_content)) == 2:
                    has_unused_macros = True
                    skip_next_column = bool(re.search(r'\\\n', column))
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
