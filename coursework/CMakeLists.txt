cmake_minimum_required(VERSION 4.4)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)           
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Находим Google Test
find_package(GTest REQUIRED)
include(GoogleTest)


# Указываем пути к заголовочным файлам
include_directories(
    ${GTEST_INCLUDE_DIRS}
    /opt/homebrew/Cellar/googletest/1.16.0  
    /usr/local/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/container 
    # ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    # ${CMAKE_CURRENT_SOURCE_DIR}/iterator
    # ${CMAKE_CURRENT_SOURCE_DIR}/reverse_iterator
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# file(GLOB CONTAINER "container/*.cpp")
# file(GLOB TESTS "tests/*.cpp")


# Если нужно добавить тесты
# add_executable(app.exe ${SOURCES} ${TESTS} ${CONTAINER})
# target_link_libraries(app.exe GTest::GTest GTest::Main)
