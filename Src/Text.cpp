#include "Text.hpp"

#include <cstdio>
#include <cstring>

void Text::FormatDouble82::format(const double value) {
  memset(buffer, 0,sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%.2f", value);
}