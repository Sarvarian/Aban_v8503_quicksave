
add_library(Zero STATIC)

target_sources(Zero PUBLIC
  Concur.hpp
  Main.hpp
)

target_sources(Zero PRIVATE
  Concur.cpp
  Main.cpp
)

target_include_directories(Zero PUBLIC ${PROJECT_SOURCE_DIR}/Zero)

if(AB_OS STREQUAL "win32")
  target_link_libraries(Zero PUBLIC SDL2main SDL2-static)
else()
  target_link_libraries(Zero PUBLIC SDL2-static)
endif()

target_compile_definitions(Zero PUBLIC AB_OS=${AB_OS})
target_compile_definitions(Zero PUBLIC AB_PROFILE=${AB_PROFILE})
target_compile_definitions(Zero PUBLIC AB_OPTIMIZE=${AB_OPTIMIZE})
target_compile_definitions(Zero PUBLIC AB_SANITIZ=${AB_SANITIZE})
target_compile_definitions(Zero PUBLIC AB_DEBUG=${AB_DEBUG})

if (AB_PROFILE STREQUAL "retro")
  target_compile_definitions(Zero PUBLIC USE_SDL=2)
elseif (AB_PROFILE STREQUAL "advanced")
  target_compile_definitions(Zero PUBLIC USE_SDL=3)
endif()

target_compile_options(Zero PUBLIC
  -Wall -Wextra -Wformat -Walloc-zero -Walloca -Wshadow -Wundef -Wdeprecated
  -Wuse-after-free=3 -Wmaybe-uninitialized -Wstrict-overflow=5 -Wdouble-promotion
  -pedantic
  -Wunused -Wno-comment -Wno-variadic-macros
  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
  -fno-exceptions -fno-rtti
)

if(AB_SANITIZE)
  target_compile_options(Zero PUBLIC
    -fsanitize=address,leak,bounds,object-size,alignment,undefined
  )
  target_link_options(Zero PUBLIC -fsanitize=address,leak,bounds,object-size,alignment,undefined)
  target_compile_definitions(Zero PUBLIC SANITIZE=1)
endif()

if(AB_OPTIMIZE)
  #set_target_properties(Zero PUBLIC UNITY_BUILD ON)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT supported OUTPUT error)
  target_compile_options(Zero PUBLIC
    -ffast-math -flto -Ofast
  )
else()
  target_compile_options(Zero PUBLIC
    -O0 -ffast-math
  )
endif()
