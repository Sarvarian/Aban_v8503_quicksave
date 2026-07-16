cmake_minimum_required(VERSION 3.28)
project(Aban VERSION 0.1.0 LANGUAGES C CXX)

option( AB_OS        "Operating system"                      OFF )
option( AB_PROFILE   "'advanced' or 'retro'"                 OFF )
option( AB_OPTIMIZE  "Optimization Enable."                  OFF )
option( AB_SANITIZE  "Sanitizer Enable."                     OFF )
option( AB_DEBUG     "Debug Enable."                         ON  )

add_subdirectory(Lib/sdl2)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Zero)
add_subdirectory(Aban)
