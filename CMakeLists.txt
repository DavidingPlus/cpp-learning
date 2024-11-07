cmake_minimum_required (VERSION 3.12)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED true)

project ("Cpp 11 Thread")

# configure compiler cross platform
if (CMAKE_HOST_WIN32)
    include (config-win32.cmake)

elseif (CMAKE_HOST_UNIX)
    include (config-unix.cmake)

else ()
    message (FATAL_ERROR "Unknown platform.")

endif ()


add_subdirectory ("snippet")
