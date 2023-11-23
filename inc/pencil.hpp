#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <vector>

std::vector<Eigen::Vector<double, 6> > generatePencil(
    const Eigen::Vector<double, 6> &c1,
    const Eigen::Vector<double, 6> &c2);
