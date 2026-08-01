#pragma once

#ifndef AB_INPUT_EVENT_PORT_HPP
#define AB_INPUT_EVENT_PORT_HPP


void ReceiveSdlInputEvent(const union SDL_Event& event, class EventReceiver& receiver);


class EventReceiver {
public:
  static EventReceiver def();

private:
  EventReceiver();

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
