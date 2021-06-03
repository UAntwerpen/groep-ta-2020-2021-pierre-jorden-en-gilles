cmake_minimum_required(VERSION 3.17)
project(TA_TO)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#=====================================================
# TODO: Change directory QT for windows/mac/linux
# Uncomment correct directory, and comment other directories
#=====================================================

#=====================================================
#Linux (tested in classroom):
#=====================================================
#For other linux variants locate local installation directory Qt5.
#For example on ubuntu search for installation directory using
#>>dpkg --listfiles qtbase5-dev
#Then find path witch contains "lib" and "cmake" and "Qt5Core")
#=====================================================
#set(Qt5Core_DIR "/home/kerstens/Qt/5.15.2/gcc_64/lib/cmake/Qt5Core")
#set(Qt5Widgets_DIR "/home/kerstens/Qt/5.15.2/gcc_64/lib/cmake/Qt5Widgets")
#set(Qt5Gui_DIR "/home/kerstens/Qt/5.15.2/gcc_64/lib/cmake/Qt5Gui")
#set(Qt5Charts_DIR "/home/kerstens/Qt/5.15.2/gcc_64/lib/cmake/Qt5Charts")

#=====================================================
# Mac
#=====================================================
#set(Qt5Core_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Core")
#set(Qt5Widgets_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Widgets")
#set(Qt5Gui_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Gui")

#=====================================================
# Windows
#=====================================================
set(Qt5Core_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Core")
set(Qt5Widgets_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Widgets")
set(Qt5Gui_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Gui")
set(Qt5Charts_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Charts")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(CMAKE_CXX_STANDARD 14)

qt5_wrap_ui(ui_files virussettings.ui simulationsettings.ui statusscreen.ui graph.ui)

add_executable(TA_TO main.cpp Cell.cpp Cell.h System.cpp System.h Virus.cpp Virus.h board.h board.cpp
        virussettings.h virussettings.cpp simulationsettings.h simulationsettings.cpp
        statusscreen.h statusscreen.cpp graph.h graph.cpp ${ui_files})
qt5_use_modules(TA_TO Core Widgets Gui Charts )
