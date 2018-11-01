licenses(["notice"])  # Apache 2.0

exports_files(["LICENSE"])

cc_library(
    name = "str_utils",
    hdrs = ["str_utils.h"],
    srcs = ["str_utils.cc"],
)

cc_test(
    name = "str_utils_test",
    srcs = ["str_utils_test.cc"],
    deps = [
        ":str_utils",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_library(
    name = "check_sum",
    hdrs = ["check_sum.h"],
    srcs = ["check_sum.cc"],
    deps = [":str_utils"],
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
    deps = [":str_utils"],
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
    name = "account",
    hdrs = ["account.h"],
    srcs = ["account.cc"],
    deps = [
      ":line",
      ":check_sum",
      ":str_utils",
    ],
)

cc_test(
    name = "account_test",
    srcs = ["account_test.cc"],
    deps = [
        ":account",
        "@xunit_cut//:cut",       
        "@xunit_cut//:cut_main",        
    ],
)

cc_binary(
    name = "bankocr",
    srcs = ["main.cc"],
    deps = [ ":account"],
)
