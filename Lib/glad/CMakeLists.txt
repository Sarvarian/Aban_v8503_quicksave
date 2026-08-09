cmake_minimum_required(VERSION 2.8...3.31)
project(glad LANGUAGES C)

set(GLAD_SOURCES
  src/egl.c
  src/gl.c
  src/gles1.c
  src/gles2.c
  src/glx.c
)

# Only add WGL on Windows
if(WIN32)
  list(APPEND GLAD_SOURCES src/wgl.c)
endif()

add_library(glad STATIC ${GLAD_SOURCES})

target_include_directories(glad
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Needed on Linux/macOS for the loaders
if(NOT WIN32)
  target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})
endif()

set_target_properties(glad PROPERTIES
  C_STANDARD 99
  C_STANDARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE ON
)