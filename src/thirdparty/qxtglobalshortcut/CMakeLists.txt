INCLUDE_DIRECTORIES(.)

set(SOURCE_FILE
        qxtglobal.cpp
        qxtglobal.h
        qxtglobalshortcut.cpp
        qxtglobalshortcut.h
        qxtglobalshortcut_p.h)

set(SPECIFIC_FILES)
if (APPLE)
    list(APPEND SPECIFIC_FILES
            "qxtglobalshortcut_mac.cpp")
endif(APPLE)

add_library(qxtglobalshortcut STATIC
        ${SOURCE_FILE}
        ${SPECIFIC_FILES}
        )
target_link_libraries(qxtglobalshortcut Qt5::Core Qt5::Gui ${PLATFORM_SPECIFIC_LIBS})