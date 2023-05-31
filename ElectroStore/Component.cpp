#include "Component.h"

std::string Videocard::get_description() {
	std::string res = "Videocard: " + this->name;
	if (video_mem) res += ", video memory: " + std::to_string(video_mem) + "GB";
	return res;
}

std::string CPU::get_description() {
	std::string res = "CPU: " + this->name + ", clock rate: " + std::to_string(clock_rate) + "MHz";
	return res;
}