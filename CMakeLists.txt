cmake_minimum_required(VERSION 3.23)
project(war VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
    src/NetworkManager.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI war
    VERSION 1.0
    QML_FILES qml/main.qml
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick)

