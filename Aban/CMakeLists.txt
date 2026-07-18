
add_executable(Aban)

target_sources(Aban PRIVATE
  Engine.cpp
)

target_link_libraries(Aban PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Zero>")


