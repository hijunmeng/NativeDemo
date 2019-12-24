# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# 打印部分预定义变量的值，可在目录app/.cxx/cmake/debug/arm64-v8a/build_output.txt下查看
message(“PROJECT_SOURCE_DIR：${PROJECT_SOURCE_DIR}”)
message(“CMakeLists.txt文件所在目录：CMAKE_CURRENT_SOURCE_DIR：${CMAKE_CURRENT_SOURCE_DIR}”)
message(“CMAKE_SOURCE_DIR：${CMAKE_SOURCE_DIR}”)



#设置jniLibs路径
set(JNILIBS_SO_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs)
message(“JNILIBS_SO_PATH：${JNILIBS_SO_PATH}”)

# 定义源文件目录
get_filename_component(CPP_SRC_DIR  ${CMAKE_SOURCE_DIR}  ABSOLUTE)
message(“CPP_SRC_DIR：${CPP_SRC_DIR}”)

# 定义源文件目录下的源文件，虽然这样可以避免写一大堆文件列表，但由于ide支持不够好，因此有新文件增加时需要手动删除生成的.cxx文件夹后再编译
file(GLOB_RECURSE CPP_SOURCES *.c *.cpp)

if (ANDROID_ABI MATCHES "^armeabi-v7a$")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon")
elseif(ANDROID_ABI MATCHES "^arm64-v8a")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ftree-vectorize")
endif()

# Specifies a path to native header files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${CPP_SOURCES} )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )


#升级到gradle4之后会报错误：More than one file was found with OS independent path 'lib/armeabi/libstreamhandler.so'
#解决办法有两个：一是删除jniLibs/armeabi/libstreamhandler.so,同时注释掉下面生成so输出路径的语句即可
#二是在当前build.gradle中添加 android{ packagingOptions { pickFirst 'lib/armeabi/libstreamhandler.so' }}

#在指定目录生成so文件，注意目录区分大小写
#set_target_properties(
#        native-lib
#        PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY
#        "${JNILIBS_SO_PATH}/${ANDROID_ABI}")