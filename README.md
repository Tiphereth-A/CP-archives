# CP-archives

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-archives)
![GitHub repo size](https://img.shields.io/github/repo-size/Tiphereth-A/CP-archives)
![GitHub language count](https://img.shields.io/github/languages/count/Tiphereth-A/CP-archives)
![GitHub top language](https://img.shields.io/github/languages/top/Tiphereth-A/CP-archives)

![](https://img.shields.io/badge/work-on--my--machine-success)

My code about Competitive Programming in daily practice

## Feature of `manager.py`

-   Remove useless files (empty files, duplicate files, files with no extension name, ...)
-   Clean content of files (comments, blanks, ...)
-   Add new file
-   Reformat files
-   Rename files

## Usage of `manager.py`

### Simple usage

```shell
python manager d
```

Then input OJ, problem ID and Extension name

### Advanced usage

```text
python manager.py [options] command [args]
```

See more info by

```text
python manager.py [command] --help
```

### About formatting

| code type                                                                             | formatter                                                    |
| ------------------------------------------------------------------------------------- | ------------------------------------------------------------ |
| `c`, `cc`, `c`, `cpp`, `cs`, `cxx`, `h`, `hpp`, `java`, `js`, `m` (Objective-C), `mm` | [clang-format](https://clang.llvm.org/docs/ClangFormat.html) |
| `go`                                                                                  | [gofmt](https://golang.org/cmd/gofmt)                        |
| `kt`                                                                                  | [ktlint](https://github.com/pinterest/ktlint)                |
| `py`                                                                                  | [autopep8](https://github.com/hhatto/autopep8)               |
| `pas`                                                                                 | [jcf-cli](https://github.com/git-bee/jcf-cli) [^1]           |
| `rs`                                                                                  | [rustfmt](https://github.com/rust-lang/rustfmt)              |

[^1]: You should copy bin files into `.\tools\bin\jcf`
