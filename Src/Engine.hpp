#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

class MainDispatcher {
public:
  static MainDispatcher def();

  ESysStatus preSdlInit(int, char**);
  ESysStatus initSdl(int, char**);
  ESysStatus initEngine(int, char**);
  ESysStatus eventSdl(const SDL_Event&);
  ESysStatus stepEngine();
  void       shutEngine();
  void       shutSdl();

  /* Target milliseconds per step.
     Should be sub second.
     Set to zero for uncapped step frequency.
     To calculate this you can use following formula:
       (millisecond_per_seconds / target_frequency) example: (1000 / 260)
       Also, there is a macro name `MSPS` in `Main.hpp`
       which is a constant for 'millisecond per seconds'.
   */
  u32 target_delta_ms;

  int exit_code;

protected:
  MainDispatcher();

  class Art* art_;
  struct DebugData* db_;
  struct Bootstrapper* boot_;
  struct Step* current_;
  struct Step* next_;
  void calculateDeltaTime(DebugData& db);

};

#endif /* AB_ENGINE_HPP */
