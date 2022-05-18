INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

file(GLOB_RECURSE varia "varia/*.h" "varia/*.cpp")
file(GLOB_RECURSE spi "spi/*.h" "spi/*.cpp")
file(GLOB_RECURSE helpers "helpers/*.h" "helpers/*.cpp")
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../..)
add_library(log4qt SHARED
        ${headers}
        ${sources}
        ${varia}
        ${spi}
        ${helpers}
        )

target_link_libraries(log4qt Qt5::Core Qt5::Gui ${PLATFORM_SPECIFIC_LIBS})