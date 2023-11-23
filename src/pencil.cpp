#include "pencil.hpp"

#include <cmath>
#include <vector>


std::vector<Eigen::Vector<double, 6> > generatePencil(Eigen::Vector<double, 6> c1,Eigen::Vector<double, 6> c2){
    double pi = M_PI;

    std::vector< Eigen::Vector<double, 6> > pencilRes;

    for(double t=0.0;t<pi;t+=pi/10){
        pencilRes.push_back(cos(t)*c1+sin(t)*c2); 
    }

    return pencilRes;
}
