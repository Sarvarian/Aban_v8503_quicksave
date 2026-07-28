cmake_minimum_required(VERSION 3.28)
project(Aban VERSION 0.1.0 LANGUAGES C CXX)

# Optimization Options
option( AB_OPTIMIZE  "Optimization Enable."                  OFF )
option( AB_SANITIZE  "Sanitizer Enable."                     OFF )
option( AB_DEBUG     "Debug Enable."                         ON  )

# Target OS Selector
set(AB_OS_ENUM "linux" "win32")
set(AB_OS "linux" CACHE STRING "Target Operating System: ${AB_OS_ENUM}")
set_property(CACHE AB_OS PROPERTY STRINGS ${AB_OS_ENUM})

# SDL Version Selector
set(AB_SDL_ENUM "2" "3")
set(AB_SDL "2" CACHE STRING "SDL Version: ${AB_SDL_ENUM}")
set_property(CACHE AB_SDL PROPERTY STRINGS ${AB_SDL_ENUM})

# SDL Directory Selector
set(AB_SDL_LIB_DIRECTORY
  TYPE STRING
  HELP "Keep this empty to use system library.
        Should be a relative path to a subdirectory inside this project."
  VALUE ""
)


if (NOT AB_SDL_LIB_DIRECTORY)
  add_subdirectory(${AB_SDL_LIB_DIRECTORY})
elseif (AB_SDL STREQUAL "2")
  find_package(SDL2 REQUIRED)
elseif (AB_SDL STREQUAL "3")
  find_package(SDL3 REQUIRED)
endif ()

# Set Fixed C Standard
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED)
set(CMAKE_C_EXTENSIONS OFF)

# Set Fixed C++ Standard
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

# Load Modules
add_subdirectory(Zero)
add_subdirectory(Engine)

# Build The Final Executable
add_executable(Aban)
target_link_libraries(Aban PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Zero>")
target_link_libraries(Aban PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Engine>")
