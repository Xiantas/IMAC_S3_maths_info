#include "Geogebra_conics.hpp"
#include "random.hpp"


Eigen::VectorXd randomPt(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> uniformDoubleDistribution(-10.0,10.0);

    Eigen::VectorXd ptR(2);

    double n1 = uniformDoubleDistribution(generator);
    double n2 = uniformDoubleDistribution(generator);

    ptR << n1,n2;

    return ptR;
}