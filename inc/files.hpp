#pragma once

#include <filesystem>
#include <vector>

#include <Eigen/Dense>

namespace fs {

typedef std::filesystem::path path;

path htmlTemplatePath(const path &exeRelPath);

std::vector<Eigen::Vector3d> loadVectorsFile();

}
