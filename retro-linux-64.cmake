
# Target System
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

# Compiler
set(CMAKE_C_COMPILER x86_64-linux-gnu-gcc-16)
set(CMAKE_CXX_COMPILER x86_64-linux-gnu-g++-16)
set(CMAKE_AR x86_64-linux-gnu-gcc-ar-16)
set(CMAKE_RANLIB x86_64-linux-gnu-gcc-ranlib-16)
set(CMAKE_STRIP x86_64-linux-gnu-strip)
set(CMAKE_LINKER x86_64-linux-gnu-ld)

# SysRoot
get_filename_component(AB_TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
set(CMAKE_SYSROOT "${AB_TOOLCHAIN_DIR}/BuildEnv/CentOS")
string(APPEND CMAKE_C_FLAGS_INIT
  " --sysroot=${CMAKE_SYSROOT}"
  " -B${CMAKE_SYSROOT}/usr/lib/gcc/x86_64-redhat-linux/4.8.5"
  " -B${CMAKE_SYSROOT}/usr/lib64"
  " -isystem ${CMAKE_SYSROOT}/usr/include"
  " -m64"
)
string(APPEND CMAKE_CXX_FLAGS_INIT
  " --sysroot=${CMAKE_SYSROOT}"
  " -B${CMAKE_SYSROOT}/usr/lib/gcc/x86_64-redhat-linux/4.8.5"
  " -B${CMAKE_SYSROOT}/usr/lib64"
  " -isystem ${CMAKE_SYSROOT}/usr/include"
  " -isystem ${CMAKE_SYSROOT}/usr/include/c++/4.8.5"
  " -isystem ${CMAKE_SYSROOT}/usr/include/c++/4.8.5/x86_64-redhat-linux"
  " -m64"
)
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT
  " -B${CMAKE_SYSROOT}/usr/lib/gcc/x86_64-redhat-linux/4.8.5"
  " -L${CMAKE_SYSROOT}/usr/lib64"
  " -L${CMAKE_SYSROOT}/lib"
  " -m64"
)
string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT
  " ${CMAKE_EXE_LINKER_FLAGS_INIT}"
  " -m64"
)
string(APPEND CMAKE_MODULE_LINKER_FLAGS_INIT " -m64")

# Search Behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

