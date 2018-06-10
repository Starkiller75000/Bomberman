cmake_minimum_required(VERSION 3.0)
project(bomberman)

if (UNIX)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -lGL -lXxf86vm")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/lib")
endif()

if (WIN32)
set(CMAKE_CXX_FLAGS "-EHsc -lGL -lXxf86vm")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/lib")
endif()

include_directories(include)

file(
        GLOB
        SRCS
        src/*.cpp
)

if (UNIX)
find_package(X11)

install(FILES librairies/libIrrKlang.so librairies/libIrrlicht.a
        librairies/ikpFlac.so librairies/ikpMP3.so DESTINATION /usr/lib)

install(DIRECTORY librairies/irrlicht/include librairies/irrKlang/include/ DESTINATION /usr/include)
endif()

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.. )

add_executable(bomberman ${SRCS} ${HEADERS})
if (UNIX)
  target_link_libraries(bomberman libIrrlicht.a libIrrKlang.so ${X11_LIBRARIES})
endif()
