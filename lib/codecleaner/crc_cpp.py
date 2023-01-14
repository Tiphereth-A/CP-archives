import re
from enum import IntEnum, auto
from random import randint


RE_PRAGMA = re.compile(r'^\s*#\s*pragma')
RE_LINE = re.compile(r'^\s*#\s*line')
RE_EMPTY_LINE = re.compile(r'^\s*;')
RE_DEFINE = re.compile(r'^\s*?#\s*?define\s+?(\w+)')
RE_TEMPLATE = re.compile(r'^\s*?template')
STR_TEMPLATE_WITH_ARGS = r'template\s*(?:<>|<(?:\s*[\w\.:]+\s+[\w =:]+(?:\((?:[^,)]+,)*[^,)]+\)|\{(?:[^,}]+,)*[^,}]+}|\[(?:[^,\]]+,)*[^,\]]+]|<(?:[^,>]+,)*[^,>]+>)*,)*\s*[\w\.:]+\s+[\w =:]+(?:\((?:[^,)]+,)*[^,)]+\)|\{(?:[^,}]+,)*[^,}]+}|\[(?:[^,\]]+,)*[^,\]]+]|<(?:[^,>]+,)*[^,>]+>)?>)'
RE_TEMPLATE_WITH_ARGS = re.compile(STR_TEMPLATE_WITH_ARGS)
RE_USING_TYPEDEF = re.compile(
    rf'^\s*(?:{STR_TEMPLATE_WITH_ARGS})?\s*using\s+(\w+)\s*(?==)')
RE_TYPEDEF = re.compile(r'(?<=typedef)\s[ \w]+\s(\w+)')
RE_CONST = re.compile(
    r'(?<=const)(?:expr)?\s\S+\s(\w+)(?=(?:\[\w+])*\s?=\s?(?:\w*?\(.+?\))*?(?:\{.+?})*?[^,]*?)')
RE_IMPLFUNC = re.compile(
    rf'^\s*(?:{STR_TEMPLATE_WITH_ARGS})?\s*constexpr \w+\s*(\w+)(?=_impl_)')
RE_IF1 = re.compile(r'^ *# *if 1\n')
RE_IF0 = re.compile(r'^ *# *if 0\n')
RE_IFDEF = re.compile(r'^\s*#\s*ifdef\s+(\w+)')
RE_IFNDEF = re.compile(r'^\s*#\s*ifndef\s+(\w+)')
RE_ELSE = re.compile(r'^\s*#\s*else')
RE_ENDIF = re.compile(r'^\s*#\s*endif')
RE_DEFINE_FLAG = re.compile(r'^\s*#\s*define\s+(\w+)\n')
RE_UNDEF_FLAG = re.compile(r'^\s*#\s*undef\s+(\w+)\n')
RE_DEBUG_FUNC = re.compile(
    rf'^\s*(?:{STR_TEMPLATE_WITH_ARGS})\s*(?:inline\s*|void\s*)+debug\([^\)]+\)\s*\{{\s*\}}')
RE_DEBUG_USAGE = re.compile(r'^\s*debug\w*\([^;]+\)(?:;|,)')
RE_DEBUG_USAGE_CASE = re.compile(
    r'\s*debug\w*\("(?:C|K|c|k)ase[^"]*",\s*\w+\),?')
RE_UNUSED_STATIC = re.compile(
    r'\s*(?:const\w*\s*)?auto\s*(_*STATIC_*)\s*=\s*\[]\(\)\s*\{\s*return 0(?:.0)?;\s*\}\s*\(\);')
RE_MAIN_PARAM = re.compile(
    r'main\s*\(\w+\s*argc,\s*(?:char\s*|const\s*){,2}\*argv\[]\)')

# qualifiers and specifiers
QS = ['static', 'mutable', 'const', 'volatile',
      'inline', 'constexpr', 'consteval', 'constinit']
PREDEFINED_MACROS: set[str] = {
    '__clang__',
    '__cplusplus',
    '__linux__',
    '__DATE__',
    '__FILE__',
    '__GNUC__',
    '__GNUG__',
    '__LINE__',
    '__PRETTY_FUNCTION__',
    '__TIME__',
    'DISABLE_PRAGMA_',
    'ONLINE_JUDGE'
}


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

    # remove unused STATIC__
    temp_codes: str = ''.join(code)
    match_res = re.search(RE_UNUSED_STATIC, temp_codes)
    if match_res:
        static_name: str = match_res.group(1)
        temp_codes = re.sub(RE_UNUSED_STATIC, '', temp_codes)
        temp_codes = re.sub(static_name, '0', temp_codes)

    code = temp_codes.split('\n')
    for column in code:
        if column:
            new_code.append(column + '\n')
    code, new_code = new_code, []

    # remove `register`
    code = [column.replace('register', '') for column in code]

    # remove #pragma and #line
    for column in code:
        if re.search(RE_PRAGMA, column) or re.search(RE_LINE, column):
            continue
        new_code.append(column)
    code, new_code = new_code, []

    # remove unused params in main()
    for column in code:
        new_code.append(re.sub(RE_MAIN_PARAM, 'main()', column))
    code, new_code = new_code, []

    # rearrange qualifiers and specifiers in:
    # static/mutable const volatile inline constexpr/consteval/constinit
    # then replace `inline constexpr` to `constexpr`
    for column in code:
        mp: dict = {k: column.find(k) for k in QS}
        idx = min(1145141919810 if i == -1 else i for i in mp.values())
        tmp = column[:idx]
        column = column[idx:]
        for qs in QS:
            column = column.replace(f"{qs} ", '')
        for qs in QS[::-1]:
            if mp[qs] != -1:
                column = f"{qs} {column}"
        column = tmp+column
        column = column.replace('inline constexpr', 'constexpr')

    # remove break of template declaration
    past_col: str = ''
    flag: bool = False
    for column in code:
        column = column.removesuffix('\n').strip()
        if flag or (re.search(RE_TEMPLATE, column) and not (column.endswith(';') or column.endswith('}'))):
            flag = True
            column = column.removesuffix('\\').strip()
            past_col += column + ' '
            if column.endswith('>') or column.endswith(';') or column.endswith('{'):
                flag = False
            continue
        if column.strip().startswith('#'):
            if past_col:
                new_code.append(past_col.strip() + '\n')
            new_code.append(column + '\n')
        else:
            new_code.append(past_col + column + '\n')
        past_col = ''
    code, new_code = new_code, []

    # remove debug()
    for column in code:
        column = column.replace('debugl_', '').replace('debug_line_', '')
        column = re.sub(RE_DEBUG_USAGE_CASE, '', column)
        column = re.sub(RE_DEBUG_USAGE, '', column)

        match_res = re.search(RE_DEBUG_FUNC, column)
        if match_res:
            continue
        new_code.append(column)
    code, new_code = new_code, []

    # remove some skipped #ifdef and #ifndef block
    rand_token = randint(114514, 1919810)
    for column in code:
        if re.search(RE_IF1, column):
            column = f'#ifdef ALWAYS_TRUE_{rand_token}\n'
        elif re.search(RE_IF0, column):
            column = f'#ifdef ALWAYS_FALSE_{rand_token}\n'
        new_code.append(column)
    code, new_code = new_code, []

    defined_flag: set[str] = PREDEFINED_MACROS | {f'ALWAYS_TRUE_{rand_token}'}
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
            delete_tuple: tuple[int, int, int, DeleteState] = (
                0, 0, 0, DeleteState.skip)
            if stack_status[-1] == DefineBlockState.in_ifdef:
                prev_idx: int = stack_index.pop()
                match_res = re.search(RE_IFDEF, code[prev_idx - 1])
                if match_res.group(1) not in defined_flag:
                    if prev_idx < stack_else_index[-1] < line_num:
                        delete_tuple = (
                            prev_idx, stack_else_index.pop(), line_num, DeleteState.pre)
                    else:
                        delete_tuple = (prev_idx, line_num,
                                        line_num, DeleteState.pre)
                elif prev_idx <= stack_else_index[-1] <= line_num:
                    delete_tuple = (
                        prev_idx, stack_else_index.pop(), line_num, DeleteState.suc)
            elif stack_status[-1] == DefineBlockState.in_ifndef:
                prev_idx: int = stack_index.pop()
                match_res = re.search(RE_IFNDEF, code[prev_idx - 1])
                if match_res.group(1) in defined_flag:
                    if prev_idx <= stack_else_index[-1] <= line_num:
                        delete_tuple = (
                            prev_idx, stack_else_index.pop(), line_num, DeleteState.pre)
                    else:
                        delete_tuple = (prev_idx, line_num,
                                        line_num, DeleteState.pre)
                elif prev_idx < stack_else_index[-1] < line_num:
                    delete_tuple = (
                        prev_idx, stack_else_index.pop(), line_num, DeleteState.suc)
            else:
                raise ValueError(
                    f"Unknown status: {stack_status[-1]} at line {line_num}")

            if delete_tuple:
                would_be_deleted_range.append(delete_tuple)

            stack_status.pop()
            continue

    line_num = 0
    now_del_range: tuple[int, int, int, DeleteState] = (
        0, 0, 0, DeleteState.skip)
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
            # and `constexpr type N = x;`, `constexpr type N = f(x, y);`, `constexpr type N[xxx] = {yyy, zzz};`
            if not match_res:
                match_res = re.search(RE_CONST, column)
            # capture `constexpr type func_impl_`, `template <...> constexpr type func_impl_`
            if not match_res:
                match_res = re.search(RE_IMPLFUNC, column)

            if match_res:
                keywords: str = match_res.group(1)
                if len(re.split(rf'\b{keywords}\b', code_content)) <= 2:
                    has_unused_macros = True
                    skip_next_column = bool(re.search(r'\\\n', column))
                    continue

            new_code.append(column)
        code, new_code = new_code, []

    # remove empty lines
    for column in code:
        if re.search(RE_EMPTY_LINE, column):
            continue
        new_code.append(column)
    code, new_code = new_code, []

    return code
