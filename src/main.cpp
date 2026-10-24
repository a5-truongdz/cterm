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

#include <CLI/CLI.hpp>

#include <QApplication>

#include "util.hpp"
#include "cterm.hpp"
#include "config.hpp"

int main(int argc, char **argv) {
    CLI::App cli{"A lightweight terminal emulator.", "cterm"};
    cli.set_version_flag("-v,--version",
        "cterm " PROJECT_VERSION "\n"
        "\n"
        "  cterm  Copyright (C) 2026  Tr43212\n"
        "  This program comes with ABSOLUTELY NO WARRANTY.\n"
        "  This is free software, and you are welcome to redistribute it,\n"
        "  under certain conditions."
    );

    std::string config_path = "~/.config/cterm/config.jsonc";
    cli.add_option(
        "-c,--config",
        config_path,
        "Path to configuration file."
    )->capture_default_str();

    std::string working_dir = ".";
    cli.add_option(
        "-d,--directory",
        working_dir,
        "Specify working directory."
    )->capture_default_str();

    CLI11_PARSE(cli, argc, argv);

    QApplication app(argc, argv);

    Config config(util::expand_user(config_path));
    CTerm cterm(config, working_dir);

    cterm.show();
    return app.exec();
}
