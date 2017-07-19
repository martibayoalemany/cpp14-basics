from conans import ConanFile, CMake
import os


channel = os.getenv("CONAN_CHANNEL", "testings")
username = os.getenv("CONAN_USERNAME", "user")


class Cpp14basicTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "cpp14-basic/1.0.0@%s/%s" % (username, channel)
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        # Current dir is "test_package/build/<build_id>" and CMakeLists.txt is in "test_package"
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")

    def test(self):
        os.chdir("bin")
        self.run(".%sexample" % os.sep)
