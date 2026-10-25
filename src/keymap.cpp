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

#include "keymap.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "util.hpp"

using json = nlohmann::json;

Keymap::Keymap(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr <<
            util::warning("Failed to open keymap " + path + ", falling back to default keybindings.");
    } else {
        json data = json::parse(file, nullptr, true, true);

        keymaps["copy"]      = data.value("copy", keymaps["copy"]);
        keymaps["paste"]     = data.value("paste", keymaps["paste"]);
        keymaps["zoomIn"]    = data.value("zoomIn", keymaps["zoomIn"]);
        keymaps["zoomOut"]   = data.value("zoomOut", keymaps["zoomOut"]);
        keymaps["resetZoom"] = data.value("resetZoom", keymaps["resetZoom"]);
    }
}
