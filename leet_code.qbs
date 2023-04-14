import qbs

CppApplication {
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++20"
    files: [
        "**/*.h",
        "**/*.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    // cpp.includePaths: ["D:/dependencies/Visual Leak Detector/include"]
    // cpp.dynamicLibraries: ["D:/dependencies/Visual Leak Detector/lib/Win64/vld.lib"]
}
