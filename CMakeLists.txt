cmake_minimum_required(VERSION 3.20)
project(casidlkai_httpd C)

set(CMAKE_C_STANDARD 99)

add_executable(casidlkai_httpd src/main.c src/cat.c include/cat.h src/error_die.c include/error_die.h src/get_line.c include/get_line.h src/accept_request.c include/accept_request.h src/unimplement.c include/unimplement.h src/startup.c include/startup.h src/server_file.c include/server_file.h src/not_found.c include/not_found.h src/headers.c include/headers.h src/get_mime_type.c include/get_mime_type.h include/macros.h)

# 使CLion识别并链接到ws2_32库
target_link_libraries(casidlkai_httpd ws2_32)
