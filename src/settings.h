#ifndef SETTINGS_H
#define SETTINGS_H

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
}
#endif