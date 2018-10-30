package(
    default_visibility = [
        "//bank_ocr:internal",
    ],
)

licenses(["notice"])  # Apache 2.0

exports_files(["LICENSE"])

cc_library(
    name = "bank_ocr",
    hdrs = [
        "line.h",
        "line_set.h",
        "check_sum.h",        
        "account_number.h",
        "illformed_number_error.h",        
    ],
    srcs = [
        "line.cc",
        "line_set.cc",
        "check_sum.cc",
        "account_number.cc",
        "illformed_number_error.cc",        
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":bank_ocr",
    ],
)

cc_test(
    name = "bank_ocr_test",
    srcs = [
        "check_sum_test.cc",
        "account_number_test.cc",
    ],
    deps = [
        ":bank_ocr",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)
