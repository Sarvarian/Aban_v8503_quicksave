
add_library(Zero STATIC)

target_sources(Zero PUBLIC
  Concur.hpp
  Main.hpp
)

target_sources(Zero PRIVATE
  Concur.cpp
)

