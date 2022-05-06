import sys
from enum import auto, IntEnum


class state (IntEnum):
    text = auto()
    string = auto()
    character = auto()
    comment_start = auto()
    block_comment = auto()
    block_comment_almost_end = auto()
    inline_comment = auto()
    escaped_string = auto()
    escaped_character = auto()
    escaped_comment_start = auto()
    escaped_block_comment = auto()
    escaped_block_comment_almost_end = auto()
    escaped_block_comment_end = auto()
    escaped_inline_comment = auto()

    def is_escaped(self) -> bool:
        return self in [state .escaped_string,
                        state .escaped_character,
                        state .escaped_comment_start,
                        state .escaped_block_comment,
                        state .escaped_block_comment_almost_end,
                        state .escaped_inline_comment]

    def is_comment(self) -> bool:
        return self in [state .comment_start,
                        state .block_comment,
                        state .block_comment_almost_end,
                        state .inline_comment,
                        state .escaped_comment_start,
                        state .escaped_block_comment,
                        state .escaped_block_comment_almost_end,
                        state .escaped_inline_comment]


def default_state() -> state:
    return state .text


transfer = {
    state .text: lambda char: {
        '/': state .comment_start,
        '"': state .string,
        "'": state .character,
    }.get(char, state .text),
    state .string: lambda char: {
        '\\': state .escaped_string,
        '"': state .text,
    }.get(char, state .string),
    state .character: lambda char: {
        '\\': state .escaped_character,
        "'": state .text,
    }.get(char, state .character),
    state .comment_start: lambda char: {
        '*': state .block_comment,
        '/': state .inline_comment,
        '\\': state .escaped_comment_start,
    }.get(char, state .text),
    state .block_comment: lambda char: {
        '*': state .block_comment_almost_end
    }.get(char, state .block_comment),
    state .block_comment_almost_end: lambda char: {
        '\\': state .escaped_block_comment_almost_end,
        '/': state .text,
        '*': state .block_comment_almost_end
    }.get(char, state .block_comment),
    state .inline_comment: lambda char: {
        '\\': state .escaped_inline_comment,
        '\n': state .text
    }.get(char, state .inline_comment),
    state .escaped_string: lambda char: state .string,
    state .escaped_character: lambda char: state .character,
    state .escaped_comment_start: lambda char: state .comment_start,
    state .escaped_block_comment: lambda char: state .block_comment,
    state .escaped_block_comment_almost_end: lambda char: {
        '\n': state .escaped_block_comment_end,
        '*': state .block_comment_almost_end
    }.get(char, state .block_comment),
    state .escaped_block_comment_end: lambda char: {
        '/': state .text,
        '*': state .block_comment_almost_end,
        '\\': state .escaped_block_comment_almost_end
    }.get(char, state .block_comment),
    state .escaped_inline_comment: lambda char: {
        '\\': state .escaped_inline_comment
    }.get(char, state .inline_comment)
}


def clean(source_code: str) -> str:
    now_state: state = default_state()
    cleaned_code: str = ''
    temporary_stored_code: str = ''
    for char in source_code:
        now_state = transfer[now_state](char)
        if now_state in [state .comment_start, state .escaped_comment_start]:
            temporary_stored_code += char
        elif now_state == state .text:
            cleaned_code += temporary_stored_code
            temporary_stored_code = ''
        elif now_state in [state .block_comment, state .inline_comment]:
            temporary_stored_code = ''
        if now_state == state .text and char != '/':
            cleaned_code += char
        elif now_state in [state .character, state .escaped_character, state .string, state .escaped_string]:
            cleaned_code += char
    return cleaned_code


if __name__ == '__main__':
    s = "".join(sys .stdin)
    print(clean(s))
