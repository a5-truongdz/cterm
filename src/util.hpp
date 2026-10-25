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
#include <cstdlib>
#include <filesystem>

#include <QString>

#include <pwd.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace util {

inline std::string expandUser(const std::string &path) {
    // case 1: path empty or not starts with ~
    if (path.empty() || path[0] != '~') {
        return path;
    }

    // find next / after pos 0
    // treat end of string as separator of not found
    std::string::size_type i = path.find('/', 1);
    if (i == std::string::npos) {
        i = path.size();
    }

    std::string userHome = "";

    if (i == 1) {
        // case 2: path starts with or is ~
        const char *home = std::getenv("HOME");
        if (home != nullptr) {
            userHome = home;
        } else {
            // fallback to passwd just in case
            struct passwd *pw = getpwuid(getuid());
            if (pw == nullptr) {
                // cant find home, unchanged path
                return path;
            }

            if (pw->pw_dir) {
                userHome = pw->pw_dir;
            }
        }
    } else {
        // case 3: path starts with or is ~username
        std::string name = path.substr(1, i - 1);
        struct passwd *pw = getpwnam(name.c_str());

        if (pw == nullptr) {
            // same as above
            return path;
        }

        if (pw->pw_dir) {
            userHome = pw->pw_dir;
        }
    }

    // remove trailing /
    while (!userHome.empty() && userHome.back() == '/') {
        userHome.pop_back();
    }

    return userHome + path.substr(i);
}

inline QString qstr(const std::string &s) {
    return QString::fromStdString(s);
}

inline bool isDir(const std::string &path) {
    fs::path fsPath = path;
    return fs::is_directory(fsPath);
}

inline bool isExecutable(const std::string &path) {
    // directories aint executable
    fs::path fsPath = path;
    if (!fs::exists(fsPath) || isDir(path)) {
        return false;
    }

    fs::perms perms = fs::status(path).permissions();
    return (perms & (fs::perms::owner_exec |
                     fs::perms::group_exec |
                     fs::perms::others_exec)) != fs::perms::none;
}

inline std::string warning(const std::string &msg) {
    return "Warning: " + msg + "\n";
}

} // namespace util
