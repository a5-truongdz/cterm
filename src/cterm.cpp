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
#include <functional>

#include <Qt>
#include <QDir>
#include <QFont>
#include <QAction>
#include <QKeySequence>
#include <qtermwidget.h>

#include "util.hpp"
#include "config.hpp"
#include "keymap.hpp"

CTerm::CTerm(const Config &config, const Keymap &keymap, std::string &workingDir)
    : fontName(&config.font),
      defaultFontSize(config.fontSize),
      currentFontSize(config.fontSize) {
    workingDir = util::expandUser(workingDir);
    if (!util::isDir(workingDir)) {
        std::cerr <<
            util::warning("Specified working directory doesn't exists (or is a file)"
                          ", falling back to '.' (current directory).");
        workingDir = ".";
    }

    setWindowTitle("-");
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800, 600);

    terminal = new QTermWidget(0, this);
    QFont font(util::qstr(config.font), config.fontSize);

    // cursor shape
    QTermWidget::KeyboardCursorShape cursorShape;
    if (config.cursorShape == "ibeam") {
        cursorShape = QTermWidget::KeyboardCursorShape::IBeamCursor;
    } else if (config.cursorShape == "underline") {
        cursorShape = QTermWidget::KeyboardCursorShape::UnderlineCursor;
    } else {
        cursorShape = QTermWidget::KeyboardCursorShape::BlockCursor;
    }

    // scroll bar pos
    QTermWidget::ScrollBarPosition scrollBar;
    if (config.scrollBarPos == "no") {
        scrollBar = QTermWidget::ScrollBarPosition::NoScrollBar;
    } else if (config.scrollBarPos == "left") {
        scrollBar = QTermWidget::ScrollBarPosition::ScrollBarLeft;
    } else {
        scrollBar = QTermWidget::ScrollBarPosition::ScrollBarRight;
    }

    // appearance
    terminal->setTerminalFont(font);
    terminal->addCustomColorSchemeDir(util::qstr(config.colorSchemeDir));
    terminal->setColorScheme(util::qstr(config.colorScheme));
    terminal->setTerminalOpacity(config.opacity);
    terminal->setKeyboardCursorShape(cursorShape);
    terminal->setScrollBarPosition(scrollBar);
    terminal->setTerminalSizeHint(config.sizeHint);
    terminal->setWorkingDirectory(util::qstr(workingDir));

    // keymaps
    bindKey(keymap.keymaps.at("copy"), [this] { terminal->copyClipboard(); });
    bindKey(keymap.keymaps.at("paste"), [this] { terminal->pasteClipboard(); });
    bindKey(keymap.keymaps.at("zoomIn"), [this] { zoomIn(); });
    bindKey(keymap.keymaps.at("zoomOut"), [this] { zoomOut(); });
    bindKey(keymap.keymaps.at("resetZoom"), [this] { resetZoom(); });

    // hooks
    connect(terminal, &QTermWidget::finished, this, &QMainWindow::close);
    connect(terminal, &QTermWidget::titleChanged, this, &CTerm::updateTitle);

    // shell
    terminal->setShellProgram(util::qstr(config.shell));
    terminal->startShellProgram();

    setCentralWidget(terminal);
}

void CTerm::updateTitle() {
    setWindowTitle(terminal->title());
}

void CTerm::zoomIn() {
    ++currentFontSize;
    QFont font(util::qstr(*fontName), currentFontSize );
    terminal->setTerminalFont(font);
}

void CTerm::zoomOut() {
    if (currentFontSize <= 0) {
        return;
    }

    --currentFontSize;
    QFont font(util::qstr(*fontName), currentFontSize + 1);
    terminal->setTerminalFont(font);
}

void CTerm::resetZoom() {
    QFont font(util::qstr(*fontName), defaultFontSize);
    terminal->setTerminalFont(font);
}

void CTerm::bindKey(const std::string &key, const std::function<void()> &callback) {
    QAction *action = new QAction(this);
    action->setShortcut(QKeySequence(util::qstr(key)));
    action->setShortcutContext(Qt::ShortcutContext::WindowShortcut);
    connect(action, &QAction::triggered, this, callback);
    addAction(action);
}
