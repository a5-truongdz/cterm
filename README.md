# cterm
A lightweight terminal emulator.

# Dependencies
- CMake >= 3.21.
- Qt6.
- QTermWidget - https://github.com/lxqt/qtermwidget.

# Build
```sh
cmake --preset Release
cmake --build --preet Release

# For debug build
cmake --preset Debug
cmake --build --preset Debug
```
Compiled binary located at `output/Release/` or `output/Debug/`.

# Credits
- LXQt for QTermWidget.
- Niels Lohmann for nlohmann/json - https://github.com/nlohmann/json.
- Henry Schreiner for CLI11 - https://github.com/cliutils/cli11.

---
*Contributions are welcome.*
