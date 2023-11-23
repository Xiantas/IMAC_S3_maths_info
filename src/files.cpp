#include "files.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

#include <Eigen/Dense>

namespace fs {

std::filesystem::path ABS_EXE_PATH;

void setAbsExePath(const std::string &exePath) {
    ABS_EXE_PATH = std::filesystem::canonical(exePath);
}

std::string findPath(std::string fileName) {
    std::cout << "In findPath\n";

    std::string testPath = ABS_EXE_PATH.parent_path()/fileName;
    if (std::filesystem::exists(testPath)) {
        return testPath;
    }

    testPath = ABS_EXE_PATH.parent_path().parent_path()/fileName;
    if (std::filesystem::exists(testPath)) {
        return testPath;
    }

    testPath = ABS_EXE_PATH.parent_path().parent_path()/"data"/fileName;
    return testPath;
}

std::string htmlTemplatePath() {
    std::cout << "looking for html\n";
    std::string file = "geogebra_conics_template.html";

    return findPath(file);
}

std::vector<Eigen::Vector3d> loadVectorsFile(const std::string &path) {
    std::string file = findPath(path);

	//open the file
	std::ifstream fileContent(file, std::ios::in | std::ios::binary);
	if(!fileContent.is_open()){
		throw std::filesystem::filesystem_error("Could not open \"" + file + "\"", std::error_code());
	}

	size_t vectorsNumber;
	fileContent >> vectorsNumber;
    std::vector<Eigen::Vector3d> res(vectorsNumber);

	for(size_t i=0; i<vectorsNumber; ++i) {
		fileContent >> res[i](0);
		fileContent >> res[i](1);
		fileContent >> res[i](2);
    }

	fileContent.close();

    return res;
}

}
