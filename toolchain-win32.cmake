
# Toolchain for cross-compiling to Windows XP (32-bit MinGW)
set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX i686-w64-mingw32)

# Cross compiler executables (adjust if using MXE prefix)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_RC_COMPILER  ${TOOLCHAIN_PREFIX}-windres)

# Force 32-bit target
set(CMAKE_C_FLAGS   "-m32 -DWINVER=0x0501 -D_WIN32_WINNT=0x0501" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-m32 -DWINVER=0x0501 -D_WIN32_WINNT=0x0501" CACHE STRING "" FORCE)

# Optional: link static libgcc/libstdc++
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++" CACHE STRING "" FORCE)

# Find programs on build host
# Search libraries and headers in target sysroot first
# Search paths for cross-tools (ignore host system)
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Prevent CMake from testing the compiler (speeds up config)
# set(CMAKE_C_COMPILER_WORKS 1)
# set(CMAKE_CXX_COMPILER_WORKS 1)
