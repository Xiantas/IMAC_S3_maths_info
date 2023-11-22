#include "files.hpp"

#include <filesystem>

namespace fs {
Path ABS_EXE_PATH;

void setAbsExePath(fs::Path exePath) {
    ABS_EXE_PATH = std::filesystem::canonical(exePath);
}

Path htmlTemplatePath() {
    Path htmlPath = ABS_EXE_PATH.parent_path()/"geogebra_conics_template.html";

    if (std::filesystem::exists(htmlPath)) {
        return htmlPath;
    }

    htmlPath = ABS_EXE_PATH.parent_path().parent_path()/"data/geogebra_conics_template.html";

    if (std::filesystem::exists(htmlPath)) {
        return htmlPath;
    }

    htmlPath = ABS_EXE_PATH.parent_path().parent_path()/"geogebra_conics_template.html";

    return htmlPath;
}

}

