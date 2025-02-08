cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dodanie find_package dla SFML z wersją 2.6.1
find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system)
find_package(Freetype REQUIRED) #To moze bedzie trzeba wywalic


# Utworzenie pliku wykonywalnego
add_executable(main src/main.cpp)

# Ustawienie wymaganych wersji kompilatora
target_compile_features(main PRIVATE cxx_std_17)

# Linkowanie z biblioteką SFML
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)
