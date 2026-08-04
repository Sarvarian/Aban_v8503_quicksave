#pragma once

#ifndef AB_TEXT_HPP
#define AB_TEXT_HPP

namespace Text {

/** The first number in the name, 8, is size of buffer (null included).
 *  The second number in the name, 2, is the decimal digit limit. */
class FormatDouble82 {
public:
  char buffer[8];
  void format(const double value);
};


}

#endif /* AB_TEXT_HPP */
