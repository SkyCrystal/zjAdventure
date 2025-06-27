#pragma once
static int generator_index = 0;

inline int GetNextIndex() {
  return ++generator_index;
}

inline void ResetIndex() {
  generator_index = 0;
}
