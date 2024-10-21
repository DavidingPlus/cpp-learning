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

aux_source_directory ("${PROJECT_SOURCE_DIR}/src" PROJECT_SOURCE_FILES)
add_library (lzxthreadsorter SHARED ${PROJECT_SOURCE_FILES})

add_subdirectory ("snippet")
