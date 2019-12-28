# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

##################################################################
# 特别注意此文件对格式有一定要求(特别注意半角英文，空格换行等，一旦出错真的难以察觉和排错)，如果格式出现错误将导致一些奇怪的问题，难以排查
##################################################################

# 以下演示打印部分预定义变量的值，可在目录app/.cxx/cmake/debug/arm64-v8a/build_output.txt下查看
message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
message("当前正在处理的列表文件即CMakeLists.txt:CMAKE_CURRENT_LIST_FILE:${CMAKE_CURRENT_LIST_FILE}")
message("当前正在处理的列表文件的目录:CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")
message("CMakeLists.txt文件所在目录:CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")

#以下演示设置变量并打印
set(myvar hello)
message(${myvar}) #打印出hello



#设置jniLibs路径
set(JNILIBS_SO_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs)
message(“JNILIBS_SO_PATH：${JNILIBS_SO_PATH}”)

# 定义源文件目录
get_filename_component(CPP_SRC_DIR  ${CMAKE_SOURCE_DIR}  ABSOLUTE)
message(“CPP_SRC_DIR：${CPP_SRC_DIR}”)

# 定义源文件目录下的源文件，虽然这样可以避免写一大堆文件列表，但由于ide支持不够好，因此有新文件增加时需要手动删除生成的.cxx文件夹后再编译
file(GLOB_RECURSE CPP_SOURCES *.c *.cc *.cpp)
message(list_all_source_filepath_and_filename:)
foreach(FILE_PATH ${CPP_SOURCES})
    message(${FILE_PATH})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    message(${FILE_NAME})#不包含后缀名
endforeach(FILE_PATH)

if (ANDROID_ABI MATCHES "^armeabi-v7a$")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon")
elseif(ANDROID_ABI MATCHES "^arm64-v8a")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ftree-vectorize")
endif()

# Specifies a path to native header files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/)

#添加预编译动态库或静态库，注意动静态库都必须放置在${ANDROID_ABI}文件夹下
#add_library(libcamera  SHARED IMPORTED )
#set_target_properties(libcamera PROPERTIES IMPORTED_LOCATION
#${JNILIBS_SO_PATH}/${ANDROID_ABI}/libcamera.so )


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
            native-lib

             # Sets the library as a shared library.
            SHARED

             # Provides a relative path to your source file(s).
             # ${CPP_SOURCES} #这里为了演示多个动态库，故暂时不用
            jni/callback-lib.cpp
            jni/object-lib.cpp
            jni/native-lib.cpp
            common/GJvm.cpp
            common/ALog.cpp
        )



add_library( # Sets the name of the library.
            dynamic-lib

            # Sets the library as a shared library.
            SHARED

            # Provides a relative path to your source file(s).
            jni/dynamic-lib.cpp
            common/GJvm.cpp
            common/ALog.cpp
        )

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
#以下会打印出liblog.so的路径，例如/home/hwj/Android/Sdk/ndk/20.1.5948944/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/21/liblog.so
message(find_log_path：${log-lib})

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       # 如果有依赖关系，被依赖的要放置在后面
                       ${log-lib} )

target_link_libraries(  # Specifies the target library.
                        dynamic-lib

                        # Links the target library to the log library
                        # included in the NDK.
                        # 如果有依赖关系，被依赖的要放置在后面
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