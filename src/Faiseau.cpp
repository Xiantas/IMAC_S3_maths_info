#include "Faiseau.hpp"
#include <cmath>


vector<Eigen::Vector6d> generateFaiseau(Eigen::Vector<double, 6> c1,Eigen::Vector<double, 6> c2){
    double pi = M_PI;

    for(double t=0.0;t<pi;t+=pi/10){
        cos(t)*c1+sin(t)*c2;
    }
}