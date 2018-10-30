package(
    default_visibility = [
        "//bank_ocr:internal",
    ],
)

licenses(["notice"])  # Apache 2.0

exports_files(["LICENSE"])

cc_library(
    name = "check_sum",
    hdrs = ["check_sum.h"],
    srcs = ["check_sum.cc"],
)

cc_test(
    name = "check_sum_test",
    srcs = ["check_sum_test.cc"],
    deps = [
        ":check_sum",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_library(
    name = "line",
    hdrs = ["line.h"],
    srcs = ["line.cc"],
)

cc_test(
    name = "line_test",
    srcs = ["line_test.cc"],
    deps = [
        ":line",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_library(
    name = "bank_ocr",
    hdrs = [
        "line_set.h",
        "account_number.h",
        "illformed_number_error.h",        
    ],
    srcs = [
        "line_set.cc",
        "account_number.cc",
        "illformed_number_error.cc",        
    ],
    deps = [
      ":line",
      ":check_sum",
    ],
)

cc_test(
    name = "account_number_test",
    srcs = ["account_number_test.cc"],
    deps = [
        ":bank_ocr",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [ ":bank_ocr"],
)