#pragma once

#ifndef AB_VIDEO_DEVICE_HPP
#define AB_VIDEO_DEVICE_HPP

class Video {
public:
  static Video* def();

  /** \return Always returns null */
  Video* undef();

private:
  Video();

};

#endif /* AB_VIDEO_DEVICE_HPP */
