#pragma once
static int index = 0;

inline int GetNextIndex() {
  return ++index;
}

inline void ResetIndex() {
  index = 0;
}
