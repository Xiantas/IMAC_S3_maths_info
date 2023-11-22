#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"
#include "path_management.hpp"
#include "random.hpp"

#include "path_management.hpp"


int main(int argc, char **argv) {
    // The viewer will open a file whose path is writen in hard (bad!!).
    // So you should either launch your program from the fine directory
    // or change the path to this file.

    ConicViewer viewer;

    // viewer options
    viewer.set_background_color(250, 250, 255);
    viewer.show_axis(true);
    viewer.show_grid(false);
    viewer.show_value(false);
    viewer.show_label(true);

    // draw points
    int n=5;
    
    /*Eigen::VectorXd pt1(2), pt2(2), pt3(2), pt4(2);
    pt1 <<  1.5,  2.0;
    pt2 <<  3.0,  1.0;
    pt3 << -2.0, -1.0;
    std::cout << "test random" << std::endl;
    pt4 = randomPt();
    std::cout << pt4 << std::endl;*/

    std::vector<Eigen::VectorXd> vp(n,Eigen::VectorXd::Zero(2));

    for(int i = 0;i<n;i++){
        vp[i] = randomPt();
    }

    for(int i = 0;i<n;i++){
        std::cout << "pt num : " << i << std::endl;
        std::cout << vp[i] << std::endl;
        viewer.push_point(vp[i], "p", 200,0,0);
    }

    // viewer.push_point(pt1, "p1", 200,0,0);
    // viewer.push_point(pt2, "p2", 200,0,0);
    // viewer.push_point(pt3, 200,0,0);

    // draw line
    // viewer.push_line(pt1, pt2-pt1,  200,200,0);

    // draw conic
    Eigen::VectorXd conic(6);
    conic << -1.4, -0.3, -1, -0.6, 0.0, 0.8;
    viewer.push_conic(conic, 0,0,200);

    // render
    viewer.display(); // on terminal
    // generate the output file (to open with your web browser)
    viewer.render("output.html", fs::htmlTemplatePath(argv[0]));

    return 0;
}
