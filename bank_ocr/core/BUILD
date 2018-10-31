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
    name = "account_number",
    hdrs = [
        "account_number.h",
        "number_format_error.h",
        ],
    srcs = [
        "account_number.cc",
        "number_format_error.cc",
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
        ":account_number",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [ ":account_number"],
)