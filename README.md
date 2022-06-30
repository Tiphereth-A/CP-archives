# CP-archives

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-archives)
![Lines of code](https://img.shields.io/tokei/lines/github/Tiphereth-A/CP-archives)
![GitHub repo size](https://img.shields.io/github/repo-size/Tiphereth-A/CP-archives)
![GitHub language count](https://img.shields.io/github/languages/count/Tiphereth-A/CP-archives)
![GitHub top language](https://img.shields.io/github/languages/top/Tiphereth-A/CP-archives)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Tiphereth-A/CP-archives)
![GitHub last commit](https://img.shields.io/github/last-commit/Tiphereth-A/CP-archives)

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

| code type                                  | formatter                                                    |
| ------------------------------------------ | ------------------------------------------------------------ |
| `c`, `cpp`, `cs`, `h`, `hpp`, `java`, `js` | [clang-format](https://clang.llvm.org/docs/ClangFormat.html) |
| `kt`                                       | [ktlint](https://github.com/pinterest/ktlint)                |
| `py`                                       | [autopep8](https://github.com/hhatto/autopep8)               |
| `pas`                                      | [jcf-cli](https://github.com/git-bee/jcf-cli) [^1]           |

[^1]: You should copy bin files into `.\tools\bin\jcf`
