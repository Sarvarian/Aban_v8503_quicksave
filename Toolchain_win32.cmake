
# Toolchain for cross-compiling to Windows XP (32-bit MinGW)
set(CMAKE_SYSTEM_NAME Windows)

# Cross compiler executables (adjust if using MXE prefix)
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_AR i686-w64-mingw32-gcc-ar)
set(CMAKE_RANLIB i686-w64-mingw32-gcc-ranlib)
set(CMAKE_STRIP i686-w64-mingw32-strip)
set(CMAKE_LINKER i686-w64-mingw32-ld)
set(CMAKE_RC_COMPILER  i686-w64-mingw32-windres)

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

