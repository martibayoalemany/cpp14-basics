from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager(username="user", channel="testings")
    builder.add_common_builds(shared_option_name="cpp14-basic:shared")
    builder.run()
