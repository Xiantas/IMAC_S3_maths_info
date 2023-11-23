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

Eigen::Vector<double,6> solverTangentes(std::vector<Eigen::Vector3d> &droites){
    Eigen::Vector<double, 6> coniqueInv = solverExact(droites);

    Eigen::Matrix3d C;

    C << 
        coniqueInv(0), coniqueInv(1)/2, coniqueInv(3)/2,
        coniqueInv(1)/2, coniqueInv(2), coniqueInv(4)/2,
        coniqueInv(3)/2, coniqueInv(4)/2, coniqueInv(5);

    C = C.inverse().eval();

    Eigen::Vector<double, 6> conique;
    conique << 
        C(0,0),
        C(0,1)*2,
        C(1,1),
        C(0,2)*2,
        C(1,2)*2,
        C(2,2);

    return conique;
}
