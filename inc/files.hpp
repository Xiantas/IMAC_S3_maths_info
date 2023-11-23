#pragma once

#include <filesystem>
#include <vector>

#include <Eigen/Dense>

namespace fs {

void setAbsExePath(const std::string &exePath);

std::string htmlTemplatePath();

std::vector<Eigen::Vector3d> loadVectorsFile(const std::string &path);

}
