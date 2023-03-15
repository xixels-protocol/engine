
target("core_math")
    set_kind("static")

    add_files("core/math/*.cpp")
    add_includedirs("core/base")
    add_includedirs("core")