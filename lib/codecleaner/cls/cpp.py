#!/usr/bin/python3
# -*- coding: utf-8 -*-

from enum import auto, IntEnum


class __state_(IntEnum):
    text = auto()
    single_quotations = auto()
    double_quotations = auto()
    comment_start = auto()
    block_comment = auto()
    block_comment_almost_end = auto()
    inline_comment = auto()
    escaped_single_quotations = auto()
    escaped_double_quotations = auto()
    escaped_comment_start = auto()
    escaped_block_comment = auto()
    escaped_block_comment_almost_end = auto()
    escaped_block_comment_end = auto()
    escaped_inline_comment = auto()


def __default_state_() -> __state_:
    return __state_.text


__transfer_ = {
    __state_.text: lambda char: {
        '/': __state_.comment_start,
        '"': __state_.double_quotations,
        "'": __state_.single_quotations,
    }.get(char, __state_.text),
    __state_.single_quotations: lambda char: {
        '\\': __state_.escaped_single_quotations,
        "'": __state_.text,
    }.get(char, __state_.single_quotations),
    __state_.double_quotations: lambda char: {
        '\\': __state_.escaped_double_quotations,
        '"': __state_.text,
    }.get(char, __state_.double_quotations),
    __state_.comment_start: lambda char: {
        '*': __state_.block_comment,
        '/': __state_.inline_comment,
        '\\': __state_.escaped_comment_start,
    }.get(char, __state_.text),
    __state_.block_comment: lambda char: {
        '*': __state_.block_comment_almost_end
    }.get(char, __state_.block_comment),
    __state_.block_comment_almost_end: lambda char: {
        '\\': __state_.escaped_block_comment_almost_end,
        '/': __state_.text,
        '*': __state_.block_comment_almost_end
    }.get(char, __state_.block_comment),
    __state_.inline_comment: lambda char: {
        '\\': __state_.escaped_inline_comment,
        '\n': __state_.text
    }.get(char, __state_.inline_comment),
    __state_.escaped_single_quotations: lambda char: __state_.single_quotations,
    __state_.escaped_double_quotations: lambda char: __state_.double_quotations,
    __state_.escaped_comment_start: lambda char: {
        '\n': __state_.comment_start,
    }.get(char, __state_.text),
    __state_.escaped_block_comment: lambda char: __state_.block_comment,
    __state_.escaped_block_comment_almost_end: lambda char: {
        '\n': __state_.escaped_block_comment_end,
        '*': __state_.block_comment_almost_end
    }.get(char, __state_.block_comment),
    __state_.escaped_block_comment_end: lambda char: {
        '/': __state_.text,
        '*': __state_.block_comment_almost_end,
        '\\': __state_.escaped_block_comment_almost_end
    }.get(char, __state_.block_comment),
    __state_.escaped_inline_comment: lambda char: {
        '\\': __state_.escaped_inline_comment
    }.get(char, __state_.inline_comment)
}


def clean(source_code: str) -> str:
    now_state: __state_ = __default_state_()
    cleaned_code: str = ''
    temporary_stored_code: str = ''
    for char in source_code:
        now_state = __transfer_[now_state](char)

        if now_state in [__state_.comment_start, __state_.escaped_comment_start]:
            temporary_stored_code += char
        elif now_state == __state_.text:
            cleaned_code += temporary_stored_code
            temporary_stored_code = ''
        elif now_state in [__state_.block_comment, __state_.inline_comment]:
            temporary_stored_code = ''

        if now_state == __state_.text and char != '/':
            cleaned_code += char
        elif now_state in [__state_.single_quotations,
                           __state_.escaped_single_quotations,
                           __state_.double_quotations,
                           __state_.escaped_double_quotations]:
            cleaned_code += char
    return cleaned_code
