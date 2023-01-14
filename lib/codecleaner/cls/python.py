#!/usr/bin/python3
# -*- coding: utf-8 -*-
import tokenize
from io import StringIO


def clean(source_code: str) -> str:
    cleaned_code = []
    g = tokenize.generate_tokens(StringIO(source_code).readline)
    for token_id, token_val, _, _, _ in g:
        if token_id != tokenize.COMMENT:
            cleaned_code.append((token_id, token_val))
    return tokenize.untokenize(cleaned_code)
