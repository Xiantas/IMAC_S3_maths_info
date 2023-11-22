#pragma once
#include <Eigen/Dense>


Eigen::Vector<double, 6> solverExact(std::vector<Eigen::Vector3d> &point);

Eigen::Vector<double,6> solverTangentes(std::vector<Eigen::Vector3d> &droites);