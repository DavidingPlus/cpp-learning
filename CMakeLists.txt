cmake_minimum_required (VERSION 3.12)

set (CMAKE_CXX_STANDARD 11)

project ("Thread Sorter")

# configure compiler cross platform
if (CMAKE_HOST_WIN32)
    include (config-win32.cmake)

elseif (CMAKE_HOST_UNIX)
    include (config-unix.cmake)

else ()
    message (FATAL_ERROR "Unknown platform.")

endif ()


# configure output dir of static and shared library
include (GNUInstallDirs)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

aux_source_directory ("${PROJECT_SOURCE_DIR}/src" PROJECT_SOURCE_FILES)

# TODO 为了兼顾 Windows，后续引入 __declspec() 机制导出动态库
# 目前 Linux 下使用动态库，Windows 下使用静态库
add_library (lzxthreadsorter ${PROJECT_SOURCE_FILES})

add_subdirectory ("snippet")
