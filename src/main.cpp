#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"
#include "files.hpp"
#include "random.hpp"


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

    std::vector<Eigen::Vector3d> vp(5, Eigen::Vector3d());

    for(int i = 0; i<vp.size(); i++) {
        vp[i] = randomPt();
    }

    for(int i = 0; i<vp.size(); i++) {
        std::cout << "pt num : " << i << std::endl;
        std::cout << vp[i] << std::endl;
        viewer.push_point(vp[i], "p", 200,0,0);
    }


    // draw conic
    Eigen::Vector<double, 6> conic;
    conic << -1.4, -0.3, -1, -0.6, 0.0, 0.8;
    viewer.push_conic(conic, 0,0,200);

    // render
    viewer.display(); // on terminal
    // generate the output file (to open with your web browser)
    viewer.render("output.html", fs::htmlTemplatePath(argv[0]));

    return 0;
}
