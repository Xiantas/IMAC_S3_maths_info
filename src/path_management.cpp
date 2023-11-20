#include <path_management.hpp>

std::filesystem::path pathmanagement::htmlTemplatePath(const char *relExePath) {
    std::filesystem::path absExePath(std::filesystem::absolute(relExePath));

    std::filesystem::path htmlPath = absExePath.parent_path().parent_path()/"data/geogebra_conics_template.html";

    return htmlPath;
}
