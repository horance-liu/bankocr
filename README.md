# Bank OCR

### Dependences 

- build tools: bazel
- C++14 

### Run Tests

```bash
$ bazel test //bank_ocr/... 
```

### Run Main

```bash
$ bazel build //bank_ocr/core:main
$ bazel-bin/bank_ocr/core/main bank_ocr/core/usecase.in
```

### Algorithm

```
from_digits = to_digits.reverse

def alts(ch) {
  from_digits.filter { digit =>
    diff(digit, ch) == 1
  }
}

def alts(account) {
  account.chars { ch =>
    prefix, posix = account.split(ch)
    alts(ch) { => alt
      prefix + alt + posix
    }
  }
}
```

