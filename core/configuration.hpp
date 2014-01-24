#pragma once
#include<vector>
#include<string>

namespace core {
  struct Configuration {
    int mode;
    int buff_len;
    bool use_z_rot;
    bool use_color;
    bool use_sound;
    bool use_space_bg;
    int idle_color;
    int blink_color;
    int blink_time;
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
	cfg.use_z_rot = true;
      } else if (s == "-c") {
	cfg.use_color = true;
      } else if (s == "-s") {
	cfg.use_sound = true;
      } else if (s == "-bg") {
	cfg.use_space_bg = true;
      } else {
	if (s.rfind("-n=", 0) == 0) {
	  cfg.buff_len = std::stoi(s.substr(3));
	} else if (s.rfind("-it=", 0) == 0) {
	  cfg.interval = std::stoi(s.substr(4));
	} else if (s.rfind("-bt=", 0) == 0) {
	  cfg.blink_time = std::stoi(s.substr(4));
	} else if (s.rfind("-ic=", 0) == 0) {
	  cfg.idle_color = std::stoi(s.substr(4));
	} else if (s.rfind("-bc=", 0) == 0) {
	  cfg.blink_color = std::stoi(s.substr(4));
	}
      }
    }
    return cfg;
  }
}
