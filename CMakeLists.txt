cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Określenie wersji builda (Debug domyślnie)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Ustawienie ścieżki do SFML w /usr/local
set(CMAKE_PREFIX_PATH "/usr/local")
link_directories("/usr/local/lib")

# Znalezienie SFML (obsługa debug i release)
find_package(SFML 2.6.1 COMPONENTS system window graphics audio network REQUIRED)

# Jeśli kompilujemy w trybie Debug, użyjemy wersji "-d"
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_LIBS sfml-graphics-d sfml-window-d sfml-system-d sfml-audio-d sfml-network-d)
else()
    set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif()

# Kopiowanie zasobów
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})

# Tworzenie pliku wykonywalnego
add_executable(main 
    src/main.cpp 
    src/program.cpp 
    src/bodyFunction.cpp 
    src/levelSelection.cpp 
    src/carSelection.cpp 
    src/mainMenu.cpp 
    src/level.cpp 
    src/level1.cpp 
    src/level2.cpp 
    src/level3.cpp 
    src/player.cpp 
    src/raport.cpp 
    src/buttons/textButton.cpp
)

# Ustawienie wersji standardu C++
target_compile_features(main PRIVATE cxx_std_17)

# Linkowanie SFML
target_link_libraries(main PRIVATE ${SFML_LIBS})
