#pragma once
#include<vector>
#include<string>

namespace core {
  struct Configuration {
    int mode;
    int buffLen;
    bool useZRot;
    bool useColor;
    bool useSound;
    bool useSpaceBg;
    int idleColor;
    int blinkColor;
    int blinkTime;
    int interval;
  };

  Configuration parse_configuration(const std::vector<std::string>& args) {
    Configuration cfg { 0, 1, false, false, false, false, 0, 0, 1, 1};
    for (const std::string& s : args) {
      if (s == "-dm") {
	cfg.mode = 0;
      } else if (s == "-sm") {
	cfg.mode = 1;
      } else if (s == "-z") {
	cfg.useZRot = true;
      } else if (s == "-c") {
	cfg.useColor = true;
      } else if (s == "-s") {
	cfg.useSound = true;
      } else if (s == "-bg") {
	cfg.useSpaceBg = true;
      } else {
	if (s.rfind("-n=", 0) == 0) {
	  cfg.buffLen = std::stoi(s.substr(3));
	} else if (s.rfind("-it=", 0) == 0) {
	  cfg.interval = std::stoi(s.substr(4));
	} else if (s.rfind("-bt=", 0) == 0) {
	  cfg.blinkTime = std::stoi(s.substr(4));
	} else if (s.rfind("-ic=", 0) == 0) {
	  cfg.idleColor = std::stoi(s.substr(4));
	} else if (s.rfind("-bc=", 0) == 0) {
	  cfg.blinkColor = std::stoi(s.substr(4));
	}
      }
    }
    return cfg;
  }
}
