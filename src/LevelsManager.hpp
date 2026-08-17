#pragma once
#include "LevelData.hpp"
#include <vector>
#include <string>

std::vector<LevelData> loadAllLvl(const std::string& path);
unsigned resumeLevel(const std::string& path);
void writeLevel(const std::string& path, unsigned level);