#include "solverExact.hpp"
#include <cmath>

Eigen::Vector<double,6> solverExact(std::vector<Eigen::Vector3d> &point) {
    assert(point.size() == 5);
    Eigen::Matrix<double, 5, 6> A;

    for(size_t i = 0; i < 5; ++i){
        A(i, 0) = std::pow(point[i](0), 2);
        A(i, 1) = point[i](0)*point[i](1);
        A(i, 2) = std::pow(point[i](1), 2);
        A(i, 3) = point[i](0)*point[i](2);
        A(i, 4) = point[i](1)*point[i](2);
        A(i, 5) = std::pow(point[i](2), 2);
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A,Eigen::ComputeThinU | Eigen::ComputeFullV );
    Eigen::VectorXd conique = svd.matrixV().rightCols(1);

    return conique;
}