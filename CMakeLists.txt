cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Określenie wersji builda (Debug domyślnie)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 🟢 Ustawienie ścieżek do SFML (zmień na swoją lokalizację SFML)
set(SFML_ROOT "D:\\dokumenty\\libraries\\SFML-2.6.1")
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

# Tworzenie pliku wykonywalnego
add_executable(main 
    src/main.cpp 
    src/program.cpp 
    src/bodyFunction.cpp 
    src/levelSelection.cpp 
    src/carSelection.cpp 
    src/mainMenu.cpp 
    src/level.cpp 
    #src/level1.cpp 
    #src/level2.cpp 
    #src/level3.cpp 
    src/player.cpp 
    src/raport.cpp
    src/settings.cpp
    src/settingsData.cpp
    src/buttons.cpp
    src/buttons/button.cpp
    src/buttons/textButton.cpp
    src/buttons/spriteButton.cpp
    src/buttons/howeredSpriteButton.cpp
    src/buttons/RectangleButton.cpp
    src/buttons/slider.cpp
    src/buttons/progressbar.cpp
    src/buttons/textBox.cpp
)

# Ustawienie wersji standardu C++
target_compile_features(main PRIVATE cxx_std_17)

# Linkowanie SFML
target_link_libraries(main PRIVATE ${SFML_LIBS})
