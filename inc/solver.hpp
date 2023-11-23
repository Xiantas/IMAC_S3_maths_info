#pragma once
#include <Eigen/Dense>


Eigen::Vector<double, 6> solvePoints(std::vector<Eigen::Vector3d> &point);

Eigen::Vector<double,6> solveTangents(std::vector<Eigen::Vector3d> &droites);
