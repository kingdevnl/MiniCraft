cmake_minimum_required(VERSION 3.25)
project(QuickJS C)





set(CMAKE_C_STANDARD 99)



add_library(quickjs
        cutils.h
        cutils.c
        libregexp.c
        libunicode.c
        quickjs.c
        quickjs-libc.c
        libbf.c
        libregexp.h
        libregexp-opcode.h
        libunicode.h
        libunicode-table.h
        list.h
        quickjs.h
        quickjs-atom.h
        quickjs-libc.h
        quickjs-opcode.h
)

#define JS_STRICT_NAN_BOXING
target_compile_definitions(quickjs PUBLIC JS_STRICT_NAN_BOXING)
target_compile_definitions(quickjs PUBLIC CONFIG_BIGNUM)
