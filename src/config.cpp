// Copyright (C) 2026  Tr43212

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "config.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include "util.hpp"

using json = nlohmann::json;

Config::Config(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr <<
            util::warning("Failed to open config " + path + ", falling back to default config.");
    } else {
        json data = json::parse(file, nullptr, true, true);

        font             = data.value("font", font);
        font_size        = data.value("fontSize", font_size);
        color_scheme_dir = util::expand_user(data.value("colorSchemeDir", color_scheme_dir));
        color_scheme     = data.value("colorScheme", color_scheme);
        opacity          = data.value("backgroundOpacity", opacity);
        shell            = data.value("shell", shell);
        cursor_shape     = data.value("cursorShape", cursor_shape);
        scroll_bar_pos   = data.value("scrollBarPosition", scroll_bar_pos);
        size_hint        = data.value("terminalTypeHint", size_hint);
    }

    if (!util::isDir(color_scheme_dir)) {
        std::cerr <<
            util::warning("Color scheme directory doesn't exists (or is a file): " + color_scheme_dir);
    }

    if (opacity < 0.0 || opacity > 1.0) {
        std::cerr <<
            util::warning("Invalid background opacity '" + std::to_string(opacity) + "', falling back to 1.");
        opacity = 1.0;
    }

    if (!util::isExecutable(shell)) {
        std::cerr <<
            util::warning("Non-executable shell '" + shell + "', falling back to bash.");
        // qtermwidget auto falls back to bash
    }

    if (
        cursor_shape != "block" &&
        cursor_shape != "ibeam" &&
        cursor_shape != "underline"
    ) {
        std::cerr <<
            util::warning("Unknown cursor type '" + cursor_shape + "', falling back to block.");
        cursor_shape = "block";
    }

    if (
        scroll_bar_pos != "no" &&
        scroll_bar_pos != "left" &&
        scroll_bar_pos != "right"
    ) {
        std::cerr <<
            util::warning("Unknown scroll bar position '" + scroll_bar_pos + "', falling back to right.");
        scroll_bar_pos = "right";
    }
}
