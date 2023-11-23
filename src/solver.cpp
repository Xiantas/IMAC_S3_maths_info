#include "solver.hpp"
#include <cmath>

Eigen::Vector<double,6> solvePoints(std::vector<Eigen::Vector3d> &points) {
    assert(points.size() == 5 && "Le nombre d'éléments en entrée doit être exactement 5 .");
    Eigen::Matrix<double, 5, 6> A;

    for(size_t i = 0; i < 5; ++i){
        A(i, 0) = std::pow(points[i](0), 2);
        A(i, 1) = points[i](0)*points[i](1);
        A(i, 2) = std::pow(points[i](1), 2);
        A(i, 3) = points[i](0)*points[i](2);
        A(i, 4) = points[i](1)*points[i](2);
        A(i, 5) = std::pow(points[i](2), 2);
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A,Eigen::ComputeThinU | Eigen::ComputeFullV);
    Eigen::VectorXd conique = svd.matrixV().rightCols(1);

    return conique;
}

Eigen::Vector<double,6> solveTangents(std::vector<Eigen::Vector3d> &lines){
    Eigen::Vector<double, 6> coniqueInv = solvePoints(lines);

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
