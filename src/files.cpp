#include "files.hpp"

#include <filesystem>
#include <iostream>
#include <vector>
#include <optional>

#include <Eigen/Dense>

namespace fs {
Path ABS_EXE_PATH;

void setAbsExePath(const Path &exePath) {
    ABS_EXE_PATH = std::filesystem::canonical(exePath);
}

std::optional<Path> findPath(Path fileName) {
    Path testPath = ABS_EXE_PATH.parent_path()/fileName;

    if (std::filesystem::exists(testPath)) {
        return testPath;
    }

    testPath = ABS_EXE_PATH.parent_path().parent_path()/fileName;

    if (std::filesystem::exists(testPath)) {
        return testPath;
    }

    testPath = ABS_EXE_PATH.parent_path().parent_path()/"data"/fileName;

    if (std::filesystem::exists(testPath)) {
        return testPath;
    }

    return {};

}

Path htmlTemplatePath() {
    Path file = "geogebra_conics_template.html";

    std::optional<Path> htmlPath = findPath(file);
    if (!htmlPath.has_value()) {
        throw std::filesystem::filesystem_error("File \"" + file.u8string() + "\" not found.", std::error_code());
    }

    return htmlPath.value();
}

std::vector<Eigen::Vector3d> loadVectorsFile(const Path &path) {
    std::optional<Path> fileOpt = findPath(path);
    if (!htmlPath.has_value()) {
        throw std::filesystem::filesystem_error("File \"" + file.u8string() + "\" not found.", std::error_code());
    }

    Path filePath = fileOpt.value();

	//open the file
	std::ifstream fileContent;
	fileContent.open(filename, std::ios::in | std::ios::binary);
	if(!fileContent.is_open()){
		throw std::filesystem::filesystem_error("Could not open \"" +  filePath.u8string() + "\"", std::error_code();
	}

	size_t vectorsNumber;
	myfile >> vectorsNumber;
    std::vector<Eigen::Vector3d> res(vectorsNumber);

	for(size_t i=0; i<vectorSize; ++i) {
		myfile >> res[i](0);
		myfile >> res[i](1);
		myfile >> res[i](2);
    }

	myfile.close();

    return res;
}

}
