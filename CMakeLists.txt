cmake_minimum_required(VERSION 3.0)
project(bomberman)

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -lGL -lXxf86vm")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/lib")

file(
        GLOB
        SRCS
        src/*.cpp
        indie/src/*.cpp
)

file(
        GLOB
        HEADERS
        include/*.hpp
        indie/inc/*.hpp
)

find_package(X11)

add_executable(bomberman ${SRCS} ${HEADERS})
target_link_libraries(bomberman /usr/lib/libIrrlicht.a /usr/lib/libIrrKlang.so ${X11_LIBRARIES})