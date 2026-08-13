#pragma once
#include "LevelData.hpp"
#include <vector>
#include <string>

std::vector<LevelData> loadAllLvl(const std::string& path);
std::size_t resumeLevel(const std::string& path);
void writeLevel(const std::string& path, std::size_t level);