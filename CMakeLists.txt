cmake_minimum_required(VERSION 3.27)
project(CMakeSFMLProject LANGUAGES CXX)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROGRAM_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
#set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Limited configurations" FORCE)

# 📌 Ustawienie ścieżek do SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/src/SFML/SFML-2.6.1")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")  # 📌 Wskazujemy SFML_DIR dla find_package
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")

# 📌 Znalezienie SFML (dynamiczne biblioteki)
find_package(SFML 2.6.1 COMPONENTS system window graphics audio network REQUIRED)

# 📌 Kopiowanie plików DLL do katalogu bin
file(GLOB SFML_DLLS "${SFML_ROOT}/bin/*.dll")
file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

include_directories(${CMAKE_SOURCE_DIR}/src/perf)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

# 📌 Tworzenie pliku wykonywalnego
add_executable(main 
    src/main.cpp 
    src/program.cpp 
    src/perf/raport.cpp
    src/perf/speedTest.cpp
    src/perf/memTracker.cpp
    src/utils/util.cpp
    src/utils/musicPlayer.cpp
    src/game/bodyFunction.cpp 
    src/game/levelSelection.cpp 
    src/game/carSelection.cpp 
    src/game/mainMenu.cpp 
    src/game/level.cpp 
    src/game/level1.cpp 
    src/game/level2.cpp 
    src/game/level3.cpp 
    src/game/settings.cpp
    src/game/settingsData.cpp
    src/game/car.cpp
    src/game/cars.cpp
    src/game/bot.cpp
    src/game/player.cpp 
    src/game/gameObjects/collidable.cpp
    src/game/gameObjects/border.cpp
    src/game/gameObjects/circle.cpp
    src/game/gameObjects/rectangle.cpp
    src/game/gameObjects/lapTimer.cpp
    src/game/gameObjects/trap.cpp
    src/game/gameObjects/checkpoint.cpp
    src/game/gameObjects/score.cpp
    src/game/gameObjects/lapCounter.cpp
    src/game/gameObjects/collidable.cpp
    src/game/buttons.cpp
    src/game/buttons/button.cpp
    src/game/buttons/textButton.cpp
    src/game/buttons/spriteButton.cpp
    src/game/buttons/howeredSpriteButton.cpp
    src/game/buttons/RectangleButton.cpp
    src/game/buttons/slider.cpp
    src/game/buttons/progressbar.cpp
    src/game/buttons/textBox.cpp
    src/game/buttons/circleButton.cpp
)

# 📌 🚀 Linkowanie z SFML (dynamiczne)
target_link_libraries(main PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio 
    sfml-network
)

# 📌 Opcje kompilatora
if(NOT MSVC)
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
endif()

# 📌 Ustawienie wersji standardu C++
target_compile_features(main PRIVATE cxx_std_17)
