INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../..)
add_library(skin SHARED
        ${headers}
        ${sources}
        )

target_link_libraries(skin Qt5::Core Qt5::Gui Qt5::Svg Qt5::Widgets utils ${PLATFORM_SPECIFIC_LIBS})