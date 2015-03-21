cmake_minimum_required(VERSION 3.1)
project(Ukrainian_Text_Watchface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    "src/main.c"
    appinfo.json
    wscript)

include_directories("/Users/darednaxella/pebble-dev/PebbleSDK-3.0-dp4/Pebble/aplite/include")

add_executable(Ukrainian_Text_Watchface ${SOURCE_FILES} src/text_formal.h src/text_formal.c)