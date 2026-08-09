cmake_minimum_required(VERSION 2.8...3.31)
# project(Aban VERSION 0.1.0 LANGUAGES C CXX)
project(Aban)

enable_language(C)
enable_language(CXX)

include(Set_Options.cmake)

find_package(PkgConfig REQUIRED)

include(Found_SDL.cmake)
message(STATUS "Detected SDL version: ${AB_SDL}")

add_subdirectory(Lib/glad)

include(Found_Vulkan.cmake)

# Set Fixed C Standard
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED)
set(CMAKE_C_EXTENSIONS OFF)

# Set Fixed C++ Standard
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build The Aban Binary
add_executable(ab
  Src/Journal.cpp
  Src/Journal.hpp
  Src/Main.hpp
  Src/Main.cpp
  Src/Memory.cpp
  Src/Memory.hpp
)

include(Link_SDL.cmake)

target_link_libraries(ab PRIVATE glad)

if (AB_VULKAN)
  target_link_libraries(ab PRIVATE volk)
endif()

if (NOT CMAKE_VERSION VERSION_LESS 3.16)
  target_precompile_headers(ab PRIVATE ${PROJECT_SOURCE_DIR}/Src/Main.hpp)
endif ()

target_compile_options(ab PUBLIC
  -Wall -Wextra -Wformat -Wshadow -Wundef -Wdeprecated
  -Wmaybe-uninitialized -Wstrict-overflow=5 -Wdouble-promotion
  # -Walloc-zero -Walloca -Wuse-after-free=3
  -pedantic
  -Wunused -Wno-comment -Wno-variadic-macros
  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
  -fno-exceptions -fno-rtti
)

if(AB_SANITIZE)
  target_compile_options(ab PUBLIC
    -fsanitize=address,leak,bounds,object-size,alignment,undefined
  )
  target_link_options(ab PUBLIC -fsanitize=address,leak,bounds,object-size,alignment,undefined)
endif()

if(AB_OPTIMIZE)
  if ( (NOT CMAKE_VERSION VERSION_LESS 3.16) AND (NOT AB_OS STREQUAL "win32") )
    set(CMAKE_UNITY_BUILD ON)
    set_target_properties(ab PROPERTIES UNITY_BUILD ON)
  endif ()
  if (NOT CMAKE_VERSION VERSION_LESS 3.9)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT supported OUTPUT error)
    set_property(TARGET ab PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif ()
  target_compile_options(ab PUBLIC
    -ffast-math -flto -Ofast
  )
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -flto")
else()
  target_compile_options(ab PUBLIC
    -O0 -ffast-math
  )
endif()

if (AB_OPTIMIZE)
  target_compile_definitions(ab PUBLIC AB_OPTIMIZE=1)
else ()
  target_compile_definitions(ab PUBLIC AB_OPTIMIZE=0)
endif ()

if (AB_SANITIZE)
  target_compile_definitions(ab PUBLIC AB_SANITIZE=1)
else ()
  target_compile_definitions(ab PUBLIC AB_SANITIZE=0)
endif ()

if (AB_DEBUG)
  target_compile_definitions(ab PUBLIC AB_DEBUG=1)
else ()
  target_compile_definitions(ab PUBLIC AB_DEBUG=0)
endif ()

if (AB_CONCUR)
  target_compile_definitions(ab PUBLIC AB_CONCUR=1)
else ()
  target_compile_definitions(ab PUBLIC AB_CONCUR=0)
endif ()

if (AB_VULKAN)
  target_compile_definitions(ab PUBLIC AB_VULKAN=1)
else ()
  target_compile_definitions(ab PUBLIC AB_VULKAN=0)
endif ()
