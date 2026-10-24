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

#include "cterm.hpp"

#include <iostream>

#include <Qt>
#include <QDir>
#include <QFont>
#include <qtermwidget.h>

#include "util.hpp"
#include "config.hpp"

CTerm::CTerm(const Config &config, std::string &working_dir) {
    working_dir = util::expand_user(working_dir);
    if (!util::isDir(working_dir)) {
        std::cerr <<
            util::warning("Specified working directory doesn't exists (or is a file)"
                          ", falling back to '.' (current directory).");
        working_dir = ".";
    }

    setWindowTitle("cterm");
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800, 600);

    terminal = new QTermWidget(0, this);

    QFont font(util::qstr(config.font), config.font_size);

    // cursor shape
    QTermWidget::KeyboardCursorShape cursor_shape;
    if (config.cursor_shape == "ibeam") {
        cursor_shape = QTermWidget::KeyboardCursorShape::IBeamCursor;
    } else if (config.cursor_shape == "underline") {
        cursor_shape = QTermWidget::KeyboardCursorShape::UnderlineCursor;
    } else {
        cursor_shape = QTermWidget::KeyboardCursorShape::BlockCursor;
    }

    // scroll bar pos
    QTermWidget::ScrollBarPosition scroll_bar;
    if (config.scroll_bar_pos == "no") {
        scroll_bar = QTermWidget::ScrollBarPosition::NoScrollBar;
    } else if (config.scroll_bar_pos == "left") {
        scroll_bar = QTermWidget::ScrollBarPosition::ScrollBarLeft;
    } else {
        scroll_bar = QTermWidget::ScrollBarPosition::ScrollBarRight;
    }

    // appearance
    terminal->setTerminalFont(font);
    terminal->addCustomColorSchemeDir(util::qstr(config.color_scheme_dir));
    terminal->setColorScheme(util::qstr(config.color_scheme));
    terminal->setTerminalOpacity(config.opacity);
    terminal->setKeyboardCursorShape(cursor_shape);
    terminal->setScrollBarPosition(scroll_bar);
    terminal->setTerminalSizeHint(config.size_hint);
    terminal->setWorkingDirectory(util::qstr(working_dir));

    // shell
    terminal->setShellProgram(util::qstr(config.shell));
    terminal->startShellProgram();

    // hooks
    connect(terminal, &QTermWidget::finished, this, &QMainWindow::close);
    connect(terminal, &QTermWidget::titleChanged, this, &CTerm::updateTitle);

    setCentralWidget(terminal);
}

void CTerm::updateTitle() {
    setWindowTitle(terminal->title());
}
