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
#include <functional>

#include <QFont>
#include <QTimer>
#include <QMainWindow>
#include <qtermwidget.h>

#include "config.hpp"
#include "keymap.hpp"

class CTerm : public QMainWindow {
public:
    explicit CTerm(const Config &config, const Keymap &keymap, std::string &workingDir);

private:
    QTermWidget *terminal;
    const std::string *fontName;
    int defaultFontSize;
    int currentFontSize;
    const std::string *titleFormat;
    QTimer *pidTimer;

    void updateTitle();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void bindKey(const std::string &key, const std::function<void()> &callback);
};
