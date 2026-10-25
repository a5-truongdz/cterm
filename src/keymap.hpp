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
#include <unordered_map>

struct Keymap {
    std::unordered_map<std::string, std::string> keymaps = {
        {"copy", "Ctrl+Shift+C"},
        {"paste", "Ctrl+Shift+V"},
        {"zoomIn", "Ctrl+="},
        {"zoomOut", "Ctrl+-"},
        {"resetZoom", "Ctrl+0"}
    };

    explicit Keymap(const std::string &path);
};
