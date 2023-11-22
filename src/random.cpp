#include "Geogebra_conics.hpp"
#include "random.hpp"

#include <random>
#include <chrono>

double generateRandom() {
    static std::mt19937 generator(
        std::chrono::system_clock::now().time_since_epoch().count()
    );
    static std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    return distribution(generator);
}

Eigen::Vector3d randomPt(){
    Eigen::Vector3d point;

    double n1 = generateRandom();
    double n2 = generateRandom();

    point << n1,n2,1;

    return point;
}

Eigen::Vector3d randomLine(){
    Eigen::Vector3d line;

    double n1 = generateRandom();
    double n2 = generateRandom();
    double n3 = generateRandom();

    line << n1,n2,n3;

    return line;
}