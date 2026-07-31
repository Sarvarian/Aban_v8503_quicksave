#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

#include "Main.hpp"
#include "Sdl.hpp"
#include "Step.hpp"

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
  Step* current_;
  Step* next_;

  Engine();

public:
  static Engine def();

};


#endif /* AB_ENGINE_HPP */
