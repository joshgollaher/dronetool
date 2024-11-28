cmake_minimum_required(VERSION 3.30)
project(drone_tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES src/main.cpp
        src/Simulation.cpp
        src/Packet.cpp
        src/modules/Battery.cpp
        src/modules/Rotor.cpp
        src/Distribution.cpp)
set(HEADERS include/Simulation.h
        include/Packet.h
        include/Drone.h
        include/DroneLink.h
        include/KalmanFilter.h
        include/modules/Battery.h
        include/modules/Module.h
        include/modules/Rotor.h
        include/Distribution.h)

find_package(Bullet CONFIG REQUIRED)

add_executable(drone_tool ${SOURCES} ${HEADERS})

target_include_directories(drone_tool PUBLIC ${BULLET_INCLUDE_DIRS})
target_include_directories(drone_tool PRIVATE include)

target_link_libraries(drone_tool PUBLIC ${BULLET_LIBRARIES})


