
find_package(PkgConfig REQUIRED)

# Find SDL Package
if (AB_SDL_LIB_DIRECTORY)
  add_subdirectory(${AB_SDL_LIB_DIRECTORY})

elseif (AB_SDL STREQUAL "auto")
  # Try SDL3 first
  pkg_check_modules(SDL3 QUIET sdl3)
  if(SDL3_FOUND)
    set(AB_SDL 3)

  else()
    # Fall back to SDL2
    pkg_check_modules(SDL2 QUIET sdl2)
    if(SDL2_FOUND)
      set(AB_SDL 2)

    else()
      # Finally try SDL1
      pkg_check_modules(SDL QUIET sdl)
      if(SDL_FOUND)
        set(AB_SDL 1)

      else()
        message(FATAL_ERROR "Could not find SDL3, SDL2, or SDL.")
      endif()
    endif()
  endif()

elseif (AB_SDL STREQUAL "1")
  pkg_check_modules(SDL REQUIRED sdl)

elseif (AB_SDL STREQUAL "2")
  pkg_check_modules(SDL2 REQUIRED sdl2)

elseif (AB_SDL STREQUAL "3")
  pkg_check_modules(SDL3 REQUIRED sdl3)

endif()
