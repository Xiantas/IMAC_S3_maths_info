#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"
#include "files.hpp"
#include "random.hpp"
#include "solverExact.hpp"


int main(int argc, char **argv) {

    //Setup du système de fichier
    fs::setAbsExePath(argv[0]);

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
    Eigen::Vector<double, 6> conic = solverExact(vp);
    viewer.push_conic(conic, 0,0,200);

    // render
    viewer.display(); // on terminal
    // generate the output file (to open with your web browser)
    viewer.render("output.html", fs::htmlTemplatePath());

    return 0;
}
