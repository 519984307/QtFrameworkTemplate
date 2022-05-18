INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../..)
add_library(minizip STATIC
        crypt.h
        ioapi.c
        ioapi.h
        unzip.c
        unzip.h
        zip.c
        zip.h
        )
target_link_libraries(minizip)