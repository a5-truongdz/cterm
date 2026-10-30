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

#pragma once

#include <string>

struct Config {
    std::string font = "monospace";
    int fontSize = 12;
    std::string colorSchemeDir = "/usr/share/qtermwidget6/color-schemes";
    std::string colorScheme = "Breeze";
    double opacity = 1.0;
    std::string shell = "/bin/bash";
    std::string cursorShape = "block";
    std::string scrollBarPos = "right";
    bool sizeHint = true;
    std::string titleFormat = "$t";
    int titleFrequency = 500;

    explicit Config(const std::string &path);
};
