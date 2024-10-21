message ("-- Building on Win32 ...")

message ("-- Using C Compiler: ${CMAKE_C_COMPILER} (${CMAKE_C_COMPILER_VERSION})")
message ("-- Using C++ Compiler: ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_VERSION})")

# using warning options W2
option (SUPRESS_W3_WARNINGS "Configure warning level to /W2" ON)
if (SUPRESS_W3_WARNINGS)
    add_compile_options ("/W2")
endif ()

# configure compiler MSVC with Ccache
# please use MSVC to satisfy Ccache, not other compilers 
add_compile_options ("/Z7")

find_program (CCACHE_EXECUTABLE ccache)
if (CCACHE_EXECUTABLE)
    message ("-- Ccache executable found at: ${CCACHE_EXECUTABLE}")
    file (COPY "${CCACHE_EXECUTABLE}" DESTINATION "${PROJECT_BINARY_DIR}")
    file (RENAME "${PROJECT_BINARY_DIR}/ccache.exe" "${PROJECT_BINARY_DIR}/cl.exe")
    set (CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
    set (CMAKE_VS_GLOBALS
        "CLToolExe=cl.exe"
        "CLToolPath=${PROJECT_BINARY_DIR}"
        "TrackFileAccess=false"
        "UseMultiToolTask=true"
        "DebugInformationFormat=OldStyle"
    )

else ()
    message ("-- CCache not found.")

endif ()


option (BUILD_SHARED_LIBS "Build using shared libraries" OFF)
