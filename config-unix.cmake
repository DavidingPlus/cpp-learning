message ("-- Building on Linux ...")

# configure compiler gcc with Ccache
set (CMAKE_C_COMPILER "gcc")
set (CMAKE_CXX_COMPILER "g++")

message ("-- Using C Compiler: ${CMAKE_C_COMPILER} (${CMAKE_C_COMPILER_VERSION})")
message ("-- Using C++ Compiler: ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_VERSION})")
