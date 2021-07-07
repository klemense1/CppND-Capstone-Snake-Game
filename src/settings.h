#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
  std::size_t kFramesPerSecond;
  std::size_t kMsPerFrame;
  std::size_t kScreenWidth;
  std::size_t kScreenHeight;
  std::size_t kGridWidth;
  std::size_t kGridHeight;
  int maxLevels;
  int foodPerLevel;
};

#endif