#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "Geogebra_conics.hpp"
#include "random.hpp"
#include "solver.hpp"
#include "pencil.hpp"
#include "Directory.hpp"

void conicResolution(const std::string &templateLoctation);
void pencilGeneration(const std::string &templateLocation);
void tangents(const std::string &templateLocation);

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cerr << "le programme doit être appelé ainsi :\n"
            << "./conic <chemin vers le template html>\n";

        return 0;
    }

    conicResolution(argv[1]);
    pencilGeneration(argv[1]);
    tangents(argv[1]);

    return 0;
}


void conicResolution(const std::string &templateLocation) {
    ConicViewer viewer;

    // viewer options
    viewer.set_background_color(250, 250, 255);
    viewer.show_axis(true);
    viewer.show_grid(false);
    viewer.show_value(false);
    viewer.show_label(true);

    std::vector<Eigen::Vector3d> points(5);

    for(size_t i = 0; i<points.size(); i++) {
        points[i] = randomPoint();
    }

    for(size_t i = 0; i<points.size(); i++) {
        viewer.push_point(points[i], "p", 200,0,0);
    }

    Eigen::Vector<double, 6> conic = solvePoints(points);
    viewer.push_conic(conic, 200,0,0);

    viewer.display();
    viewer.render("conic.html", templateLocation);
}

void pencilGeneration(const std::string &templateLocation) {
    ConicViewer viewer;

    // viewer options
    viewer.set_background_color(250, 250, 255);
    viewer.show_axis(true);
    viewer.show_grid(false);
    viewer.show_value(false);
    viewer.show_label(true);

    std::vector<Eigen::Vector3d> pointsA(5);
    std::vector<Eigen::Vector3d> pointsB(5);

    for(size_t i = 0; i<pointsA.size(); i++) {
        pointsA[i] = randomPoint();
        pointsB[i] = randomPoint();
    }

    for(size_t i = 0; i<pointsA.size(); i++) {
        viewer.push_point(pointsA[i], "p", 200,0,0);
        viewer.push_point(pointsB[i], "p", 200,0,0);
    }

    Eigen::Vector<double, 6> conicA = solvePoints(pointsA);
    Eigen::Vector<double, 6> conicB = solvePoints(pointsB);

    std::vector<Eigen::Vector<double, 6>> pencil = generatePencil(conicA,conicB);

    for(size_t i = 0; i<pencil.size();i++){
        viewer.push_conic(pencil[i], 0,0,200);
    }

    viewer.display();
    viewer.render("pencil.html", templateLocation);
}

void tangents(const std::string &templateLocation) {
    ConicViewer viewer;

    // viewer options
    viewer.set_background_color(250, 250, 255);
    viewer.show_axis(true);
    viewer.show_grid(false);
    viewer.show_value(false);
    viewer.show_label(true);

    std::vector<Eigen::Vector3d> lines(5);
    for(size_t i = 0; i<lines.size(); i++) {
        lines[i] = randomLine();

        Eigen::Vector3d pt;
        pt << -lines[i](2)/lines[i](0), 0, 1;

        Eigen::Vector2d dir;
        dir << lines[i](2)/lines[i](0), -lines[i](2)/lines[i](1);

        viewer.push_line(pt,dir, 0,0,200);
    }

    Eigen::Vector<double, 6> conic = solveTangents(lines);
    viewer.push_conic(conic, 200,0,0);

    viewer.display();
    viewer.render("tangents.html", templateLocation);
}
