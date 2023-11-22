#include "Faiseau.hpp"
#include <cmath>
#include <vector>


std::vector<Eigen::Vector<double, 6> > generateFaiseau(Eigen::Vector<double, 6> c1,Eigen::Vector<double, 6> c2){
    double pi = M_PI;

    std::vector< Eigen::Vector<double, 6> > faiseauRes;

    for(double t=0.0;t<pi;t+=pi/10){
        faiseauRes.push_back(cos(t)*c1+sin(t)*c2); 
    }

    return faiseauRes;
}