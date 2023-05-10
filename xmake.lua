add_rules("mode.debug", "mode.release")
add_requires("stb")

target("image_merger")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("stb");