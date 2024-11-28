cmake_minimum_required(VERSION 3.30)
project(drone_tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES src/main.cpp
        src/Simulation.cpp
        src/Packet.cpp
        src/modules/Battery.cpp
        src/modules/Rotor.cpp
        src/Distribution.cpp
        src/drones/SimpleDrone.cpp)
set(HEADERS include/Simulation.h
        include/Packet.h
        include/Drone.h
        include/DroneLink.h
        include/KalmanFilter.h
        include/modules/Battery.h
        include/modules/Module.h
        include/modules/Rotor.h
        include/Distribution.h
        include/drones/SimpleDrone.h)

find_package(Bullet CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

add_executable(drone_tool ${SOURCES} ${HEADERS})

target_include_directories(drone_tool PRIVATE include)

target_link_libraries(drone_tool PRIVATE ${BULLET_LIBRARIES})
target_link_libraries(drone_tool PRIVATE sfml-system sfml-graphics sfml-window)
target_link_libraries(drone_tool PRIVATE imgui::imgui)
target_link_libraries(drone_tool PRIVATE ImGui-SFML::ImGui-SFML)


