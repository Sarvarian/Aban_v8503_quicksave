#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

#include "Main.hpp"
#include "Memory.hpp"
#include "Sdl.hpp"

class Engine : public virtual IEngine {
public:
  ESysStatus preSdlInit(int, char**);
  ESysStatus initSdl(int, char**);
  ESysStatus initEngine(int, char**);
  ESysStatus eventSdl(const SDL_Event*);
  ESysStatus stepEngine();
  void       shutEngine();
  void       shutSdl();

protected:
  SdlWindow window_;
  struct DebugData* db_;
  struct Bootstrapper* boot_;
  struct Step* current_;
  struct Step* next_;

  Engine();

public:
  static Engine def();

};

struct Step {
public:
  u8 just_continue : 1;
  u8 calculate_delta_time : 1;
  u8 window_check : 1;
  u8 window_undef : 1;
  u8 window_def : 1;
  u8 _pad03_ : 1;
  u8 _pad02_ : 1;
  u8 _pad01_ : 1;
  u8 _pad00_[mmBufferSize(0) - 1];
};
staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_BUFFER0)


#endif /* AB_ENGINE_HPP */
