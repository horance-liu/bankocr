# Bank OCR

### Dependences 

- build tools: [bazel](https://www.bazel.build)
- C++14: tools/bazel.rc

### Run Tests

```bash
$ bazel test //bank_ocr/... 
```

### Run Main

```bash
$ bazel build //bank_ocr/core:main
$ bazel-bin/bank_ocr/core/main bank_ocr/core/usecase.in
```
