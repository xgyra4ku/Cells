cmake_minimum_required(VERSION 3.5)

project(MyProject)

# Укажите, что требуется C++ компилятор g++
set(CMAKE_CXX_COMPILER "g++")

# Укажите путь для сборки проекта в папку "debug"
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# Установите путь для собранных исполняемых файлов в папку "files"
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/filedd)

# Укажите путь к исходным файлам
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Добавьте исходные файлы вашего проекта
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# Добавьте исполняемый файл
add_executable(MyExecutable ${SOURCES})

# Укажите путь к SFML
set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML)

# Укажите пути для поиска библиотек и заголовочных файлов
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# Добавьте SFML в CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH ${SFML_DIR}/lib/cmake/SFML)

# Найдите пакет SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Подключите SFML библиотеки
target_link_libraries(MyExecutable sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
