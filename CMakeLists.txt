cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Określenie wersji builda (Debug domyślnie)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#ustawienie sciezki (nie dotykac)
set(SFML_ROOT "C:/SFML/SFML-2.6.1")
set(CMAKE_PREFIX_PATH "${SFML_ROOT}")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Znalezienie SFML
find_package(SFML 2.6.1 COMPONENTS system window graphics audio network REQUIRED)

# Jeśli kompilujemy w trybie Debug, użyjemy wersji "-d"
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_LIBS sfml-graphics-d sfml-window-d sfml-system-d sfml-audio-d sfml-network-d)
else()
    set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif()

set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")

file(COPY "${RESOURCES_DIR}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


include_directories(${CMAKE_SOURCE_DIR}/src/perf)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

# Tworzenie pliku wykonywalnego
add_executable(main 
    src/main.cpp 
    src/program.cpp 

    src/perf/raport.cpp
    src/perf/speedTest.cpp
    src/perf/memTracker.cpp

    src/utils/util.cpp

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

add_compile_definitions(HITBOXTEST)
add_compile_definitions(SPEEDTEST)
add_compile_definitions(MEMTRACKER)

if(NOT MSVC)
	target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
endif()

# Ustawienie wersji standardu C++
target_compile_features(main PRIVATE cxx_std_17)

# Linkowanie SFML
target_link_libraries(main PRIVATE ${SFML_LIBS})