#ifndef PARAM_H
#define PARAM_H

namespace param {
struct Settings {
  int kFramesPerSecond;
  int kMsPerFrame;
  int kScreenWidth;
  int kScreenHeight;
  int kGridWidth;
  int kGridHeight;
  int maxLevels;
  int foodPerLevel;
};
} // namespace param
#endif