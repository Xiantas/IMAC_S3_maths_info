#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

std::cout << std::endl << "std::mt19937" << std::endl;
std::mt19937 generator(seed);

std::cout << std::endl << "uniform int distribution (1,6)" << std::endl;
std::uniform_int_distribution<double> uniformIntDistribution(-10,10);
std::cout << std::endl;

Eigen::VectorXd randomPt(){
    srand(time(NULL));

    double x = rand() % -10 + 10;
    double y = rand() % -10 + 10;
}