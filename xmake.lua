
target("core")
    set_kind("static")

    add_files("core/base/*.cpp")
    add_files("core/math/*.cpp")
    add_includedirs("core/base")
    add_includedirs("core/math")
    add_includedirs("core")