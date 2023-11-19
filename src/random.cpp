#include <iostream>
#include <vector>
#include <ctime>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"

Eigen::VectorXd randomPt(){
    srand(time(NULL));

    double x = rand() % -10 + 10;
    double y = rand() % -10 + 10;
}