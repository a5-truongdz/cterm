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

        font           = data.value("font", font);
        fontSize       = data.value("fontSize", fontSize);
        colorSchemeDir = util::expandUser(data.value("colorSchemeDir", colorSchemeDir));
        colorScheme    = data.value("colorScheme", colorScheme);
        opacity        = data.value("backgroundOpacity", opacity);
        shell          = data.value("shell", shell);
        cursorShape    = data.value("cursorShape", cursorShape);
        scrollBarPos   = data.value("scrollBarPosition", scrollBarPos);
        sizeHint       = data.value("terminalTypeHint", sizeHint);
        titleFormat    = data.value("windowTitleFormat", titleFormat);
        titleFrequency = data.value("titleUpdateFrequency", titleFrequency);

        if (fontSize <= 0) {
            std::cerr <<
                util::warning("Invalid font size '" + std::to_string(fontSize) +"', falling back to 12.");
            fontSize = 12;
        }

        if (!util::isDir(colorSchemeDir)) {
            std::cerr <<
                util::warning("Color scheme directory doesn't exists (or is a file): " + colorSchemeDir);
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
            cursorShape != "block" &&
            cursorShape != "ibeam" &&
            cursorShape != "underline"
        ) {
            std::cerr <<
                util::warning("Unknown cursor type '" + cursorShape + "', falling back to block.");
            cursorShape = "block";
        }

        if (
            scrollBarPos != "no" &&
            scrollBarPos != "left" &&
            scrollBarPos != "right"
        ) {
            std::cerr <<
                util::warning("Unknown scroll bar position '" + scrollBarPos + "', falling back to right.");
            scrollBarPos = "right";
        }

        if (titleFrequency < 0) {
            std::cerr <<
                util::warning("Invalid title update frequency '" + std::to_string(titleFrequency) + "', falling back to 500ms.");
            titleFrequency = 500;
        }
    }
}
