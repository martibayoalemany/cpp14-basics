

new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "gtest.BUILD",
)
cc_library(
    name = "main",
    srcs = glob(
        ["googletest-release-1.7.0/src/*.cc"],
        exclude = ["googletest-release-1.7.0/src/gtest-all.cc"]
    ),
    hdrs = glob([
        "googletest-release-1.7.0/include/**/*.h",
        "googletest-release-1.7.0/src/*.h"
    ]),
    copts = [
        "-Iexternal/gtest/googletest-release-1.7.0/include"
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cpp14-basics",
    srcs = ["main.cpp"
        "cpp/car.cpp"
        "cpp/Tables/Table.cpp"
        "cpp/Tables/Table2.cpp"
        "cpp/Tables/OnTheFlyTable.cpp"
        "cpp/Tables/RandomTable.cpp"
        "cpp/Tables/TableInPrivate.cpp"
        "cpp/Tables/TableInProtected.cpp"
        "cpp/Tables/TableInPrivateChild.cpp"
        "cpp/Tables/TableInProtectedChild.cpp"
        "cpp/Tables/AbsoluteTable.cpp"
        "cpp/Tables/TableClient.cpp"],
    hdrs = ["cpp/car.h"
            "cpp/Tables/Table.h"
            "cpp/Tables/Table2.h"
            "cpp/Tables/OnTheFlyTable.h"
            "cpp/Tables/RandomTable.h"
            "cpp/Tables/TableInPrivate.h"
            "cpp/Tables/TableInProtected.h"
            "cpp/Tables/TableInPrivateChild.h"
            "cpp/Tables/TableInProtectedChild.h"
            "cpp/Tables/AbsoluteTable.h"
            "cpp/Tables/TableClient.h"]
    ],
    deps = [
        ":gtest"
    ]
)
