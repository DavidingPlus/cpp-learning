cmake_minimum_required (VERSION 3.12)

set (CMAKE_CXX_STANDARD 11)

project ("Thread Sorter")

# configuring compiler cross platform
if (CMAKE_HOST_WIN32)
    include (config-win32.cmake)

elseif (CMAKE_HOST_UNIX)
    include (config-unix.cmake)

else ()
    message (FATAL_ERROR "Unknown platform.")

endif ()

# TODO 为了兼顾 Windows，后续引入 __declspec() 机制导出动态库
# 目前 Linux 下使用动态库，Windows 下使用静态库
aux_source_directory ("${PROJECT_SOURCE_DIR}/src" PROJECT_SOURCE_FILES)
add_library (lzxthreadsorter ${PROJECT_SOURCE_FILES})

add_subdirectory ("snippet")
