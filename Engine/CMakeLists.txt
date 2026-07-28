
add_library(Engine)

target_sources(Engine PRIVATE
  Engine.cpp
  Engine.hpp
)

target_link_libraries(Engine PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Zero>")


