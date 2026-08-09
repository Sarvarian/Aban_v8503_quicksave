
set(AB_UUID "2c76398e-612f-4bb0-ada6-d2ef8fa68246")  # Project UUID
set(AB_VERSION_DATE 8503)  # v8503e1 Date Version
set(AB_VERSION_EDITION 1)
set(AB_VERSION_MAJOR 0)     # 0.1.0 Semantic Version
set(AB_VERSION_MINOR 1)
set(AB_VERSION_PATCH 0)

add_compile_definitions(
  AB_UUID="${AB_UUID}"
  AB_VERSION_DATE=${AB_VERSION_DATE}
  AB_VERSION_EDITION=${AB_VERSION_EDITION}
  AB_VERSION_MAJOR=${AB_VERSION_MAJOR}
  AB_VERSION_MINOR=${AB_VERSION_MINOR}
  AB_VERSION_PATCH=${AB_VERSION_PATCH}
)

# Optimization Options
option( AB_OPTIMIZE  "Optimization Enable."                  ON  )
option( AB_SANITIZE  "Sanitizer Enable."                     OFF )
option( AB_DEBUG     "Debug Enable."                         OFF )

# SDL Version Selector
set(AB_SDL_ENUM "1" "2" "3" "auto")
set(AB_SDL "auto" CACHE STRING "SDL Version: ${AB_SDL_ENUM}")
set_property(CACHE AB_SDL PROPERTY STRINGS ${AB_SDL_ENUM})

# SDL Directory Selector
set(AB_SDL_LIB_DIRECTORY ""
  CACHE STRING
  "Keep this empty to use system library.
   Should be a relative path to a subdirectory inside this project.
   Also, remember to set AB_SDL to the version number."
)

option(AB_SDL_STATIC  "Link to SDL-static:" OFF)
option(AB_CONCUR  "Enable concurrency and threading modules." ON)
option(AB_VULKAN  "Include Vulkan Backend" ON)
