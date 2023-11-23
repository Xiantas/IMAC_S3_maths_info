#include <iostream>

#include "Entry.hpp"
#include "Geogebra_conics.hpp"
#include "Directory.hpp"


ConicViewer::ConicViewer() {}

ConicViewer::~ConicViewer() {}

void ConicViewer::display() const {
    for(const auto& e : entries)
        e.display();
}


void ConicViewer::removeNameDoublons(){

    // for each entry, find if there is multiple occurences of the same name
    auto e = entries.begin();
    while(e != entries.end()){

        // check all the remaining entries
        int count = 2;
        auto e2 = e;
        ++e2;
        while(e2 != entries.end()){
            if((*e)._objectName == (*e2)._objectName){
                (*e2)._objectName += std::to_string(count);
                ++count;
            }
            ++e2;
        }
        ++e;
    }
}



void ConicViewer::render(const std::string &filename, const std::string &templatePath) {
    std::cout << "in render\n";
    // open the template file
    std::string data = readFile(templatePath);

    // remove name doublons
    removeNameDoublons();

    // build output commands
    std::string commands = "";



    // options
    if(m_show_axis) commands += "   api.evalCommand(\"ShowAxes(true)\");\n";
    else            commands += "   api.evalCommand(\"ShowAxes(false)\");\n";

    if(m_show_grid) commands += "   api.evalCommand(\"ShowGrid(true)\");\n";
    else            commands += "   api.evalCommand(\"ShowGrid(false)\");\n";

    commands += "   api.evalCommand(\"CenterView((0, 0))\");\n";

    // https://wiki.geogebra.org/en/SetBackgroundColor_Command
    commands += "   api.evalCommand(\"SetBackgroundColor(" + std::to_string(m_background_color[0]) + ","
                                                           + std::to_string(m_background_color[1]) + ","
                                                           + std::to_string(m_background_color[2])
                                                           + ")\");\n";

    std::cout << "Before for loop\n";
    // for each entry, extract the command
    for(const auto& e : entries){

        // equation
        e.display();
        commands += "   api.evalCommand(\"";
        commands += (e._objectName == "") ? "" : e._objectName + " : ";
        commands +=  e.m_equation + "\");\n";

        // color
        if(e.m_color[0] != -1)
            commands += "   api.evalCommand(\"SetColor(" + e._objectName + ", "
                                + std::to_string(e.m_color[0]/255.0) + ", "
                                + std::to_string(e.m_color[1]/255.0) + ", "
                                + std::to_string(e.m_color[2]/255.0) + ")\");\n";

        // show labels and values
        // show value (0=Name, 1=Name + Value, 2=Value)
        if( (e.m_show_label == true) && (e.m_show_value == true)  ){
            commands += "   api.evalCommand(\"ShowLabel(" + e._objectName + ", true)\");\n";
            commands += "   api.evalCommand(\"SetLabelMode(" + e._objectName + ", 1)\");\n";
        }
        if( (e.m_show_label == true) && (e.m_show_value == false)  ){
            commands += "   api.evalCommand(\"ShowLabel(" + e._objectName + ", true)\");\n";
            commands += "   api.evalCommand(\"SetLabelMode(" + e._objectName + ", 0)\");\n";
        }
        if( (e.m_show_label == false) && (e.m_show_value == true)  ){
            commands += "   api.evalCommand(\"ShowLabel(" + e._objectName + ", true)\");\n";
            commands += "   api.evalCommand(\"SetLabelMode(" + e._objectName + ", 2)\");\n";
        }
        if( (e.m_show_label == false) && (e.m_show_value == false)  ){
            commands += "   api.evalCommand(\"ShowLabel(" + e._objectName + ", false)\");\n";
        }
    }

    // substitute command on template file
    substitute(data,"__GARAMON_INSTER_DATA_FLAG__", commands);

    // save file
    writeFile(data, filename);
}


// https://wiki.geogebra.org/en/Point_Command
int ConicViewer::push_point(const Eigen::Vector3d &pt, std::string objectName, const unsigned int &red, const unsigned int &green, const unsigned int &blue) {
    if (pt(2) == 0.0) {
        return EXIT_SUCCESS;
    }
    // remove space in the name
    objectName.erase(std::remove(objectName.begin(), objectName.end(), ' '), objectName.end());

    // final equation
    std::string equation;

    equation = " Point({" + std::to_string(pt[0]/pt[2]) + "," + std::to_string(pt[1]/pt[2]) + "})";

    // put a default name
    if(objectName == "")
        objectName = "pt";

    // push the entry
    entries.push_back(Entry(equation, objectName, red, green, blue, m_show_label, m_show_value));

    // finish
    return EXIT_SUCCESS;
}

// https://wiki.geogebra.org/en/Line_Command
int ConicViewer::push_line(const Eigen::Vector3d &pt, const Eigen::Vector2d &dir, std::string objectName, const unsigned int &red, const unsigned int &green, const unsigned int &blue) {
    // remove space in the name
    objectName.erase(std::remove(objectName.begin(), objectName.end(), ' '), objectName.end());

    // final equation
    std::string equation;

    equation = " Line((" + std::to_string(pt[0]) + "," + std::to_string(pt[1]) +  "), Vector((" + std::to_string(dir[0]) + "," + std::to_string(dir[1]) + ")))";

    // put a default name
    if(objectName == "")
        objectName = "l";

    // push the entry
    entries.push_back(Entry(equation, objectName, red, green, blue, m_show_label, m_show_value));

    // finish
    return EXIT_SUCCESS;
}


// https://wiki.geogebra.org/en/Line_Command
int ConicViewer::push_direction(const Eigen::Vector2d &direction, std::string objectName, const unsigned int &red, const unsigned int &green, const unsigned int &blue) {
    // remove space in the name
    objectName.erase(std::remove(objectName.begin(), objectName.end(), ' '), objectName.end());

    // final equation
    std::string equation;

    equation = " Line((0.0,0.0,0.0), Vector((" + std::to_string(direction[0]) + "," + std::to_string(direction[1]) + ")))";

    // put a default name
    if(objectName == "")
        objectName = "l";

    // push the entry
    entries.push_back(Entry(equation, objectName, red, green, blue, m_show_label, m_show_value));

    // finish
    return EXIT_SUCCESS;
}

 // https://wiki.geogebra.org/en/Conic_Command
int ConicViewer::push_conic(const Eigen::Vector<double, 6> &c, std::string objectName, const unsigned int &red, const unsigned int &green, const unsigned int &blue) {
    // remove space in the name
    objectName.erase(std::remove(objectName.begin(), objectName.end(), ' '), objectName.end());

    // final equation
    std::string equation;

    equation = " Conic(" + std::to_string(c[0]) + ","   // x^2
                         + std::to_string(c[2]) + ","   // y^2
                         + std::to_string(c[5]) + ","   // g
                         + std::to_string(c[1]) + ","   // xy
                         + std::to_string(c[3]) + ","   // x
                         + std::to_string(c[4]) + ")";  // y

    // put a default name
    if(objectName == "")
        objectName = "c";

    // push the entry
    entries.push_back(Entry(equation, objectName, red, green, blue, m_show_label, m_show_value));

    // finish
    return EXIT_SUCCESS;
}


