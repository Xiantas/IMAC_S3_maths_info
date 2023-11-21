module;
//#include <path_management.hpp>

#include <filesystem>
#include <iostream>

export module fs;

namespace fs {

export std::filesystem::path htmlTemplatePath(const char *relExePath) {
    std::filesystem::path absExePath(std::filesystem::absolute(relExePath));

    std::filesystem::path htmlPath = absExePath.parent_path()/"geogebra_conics_template.html";

    std::cout << htmlPath << '\n';
    if (std::filesystem::exists(htmlPath)) {
        return htmlPath;
    }

    htmlPath = absExePath.parent_path().parent_path()/"data/geogebra_conics_template.html";

    std::cout << htmlPath << '\n';
    if (std::filesystem::exists(htmlPath)) {
        return htmlPath;
    }

    htmlPath = absExePath.parent_path().parent_path()/"geogebra_conics_template.html";

    std::cout << htmlPath << '\n';
    return htmlPath;
}

}
