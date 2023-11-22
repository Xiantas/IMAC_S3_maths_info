#pragma once

#include <filesystem>
#include <vector>

#include <Eigen/Dense>

namespace fs {

using Path = std::filesystem::path;

void setAbsExePath(const Path &exePath);

Path htmlTemplatePath();

std::vector<Eigen::Vector3d> loadVectorsFile(const Path &path);

}
