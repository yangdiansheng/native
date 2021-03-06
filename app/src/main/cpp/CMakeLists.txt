# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(var hello) #定义变量
message(${var})
set(var 111)
message(${var})

message(${CMAKE_CURRENT_LIST_FILE})
message(${CMAKE_CURRENT_LIST_DIR})

if (ture)
    message("if is exe")
endif ()

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        ${CMAKE_SOURCE_DIR}/basic-type-operation.cpp
        ${CMAKE_SOURCE_DIR}/base/jvm.cpp
        ${CMAKE_SOURCE_DIR}/string-type-operation.cpp
        ${CMAKE_SOURCE_DIR}/filed-and-animal-operation.cpp
        ${CMAKE_SOURCE_DIR}/invoke-constructor-operation.cpp
        ${CMAKE_SOURCE_DIR}/local-and-global-reference.cpp
        ${CMAKE_SOURCE_DIR}/exception-operation.cpp
        ${CMAKE_SOURCE_DIR}/product-and-consumer.cpp
        ${CMAKE_SOURCE_DIR}/bitmap-operation.cpp
        ${CMAKE_SOURCE_DIR}/memory/memory.cpp
        ${CMAKE_SOURCE_DIR}/thread_operation.cpp)


add_library(
        common
        SHARED
        ${CMAKE_SOURCE_DIR}/common/commonutil.cpp
)

add_library(people-lib
        SHARED #动态库
        people/people.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

include_directories(people/) #查找代码
include_directories(${CMAKE_SOURCE_DIR}/common/)

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        people-lib
        common
        jnigraphics
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})