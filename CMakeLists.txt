cmake_minimum_required(VERSION 3.23)
project(war VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(client
    main.cpp
    src/Client.cpp
)

qt_add_executable(tcpServer
    main.cpp
    src/TcpServer.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(tcpServer PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

qt_add_qml_module(tcpServer
    URI war
    VERSION 1.0
    QML_FILES qml/tcpServer.qml
)

qt_add_qml_module(client
    URI war
    VERSION 1.0
    QML_FILES qml/client.qml
)

target_link_libraries(tcpServer PRIVATE Qt6::Quick)
target_link_libraries(client PRIVATE Qt6::Quick)

