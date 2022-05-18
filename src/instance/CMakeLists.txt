INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../)


set(SOURCE_FILE
CAppSingle.cpp
main.cpp
pluginmanager.cpp
mainapplication.cpp
CAppSingle.h
pluginmanager.h
mainapplication.h
        qtsingleapplication/src/qtsingleapplication.cpp
        qtsingleapplication/src/qtsingleapplication.h
        qtsingleapplication/src/qtlocalpeer.h
        qtsingleapplication/src/qtlocalpeer.cpp
        )

INCLUDE_DIRECTORIES(qtsingleapplication/src)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../..)
INCLUDE_DIRECTORIES(../thirdparty)
INCLUDE_DIRECTORIES(../utils)
INCLUDE_DIRECTORIES(../bfskinmodule)
INCLUDE_DIRECTORIES("../../dependency/zlib_r/include")
INCLUDE_DIRECTORIES("../../dependency/ui_sdk/include")
INCLUDE_DIRECTORIES("../../dependency/json_r/include")
INCLUDE_DIRECTORIES("../../dependency/openssl_r/include")
INCLUDE_DIRECTORIES("../../dependency/base_platform_sdk/include")
INCLUDE_DIRECTORIES("../../dependency/billfish_sdk/sdk/include")
INCLUDE_DIRECTORIES("../../dependency/billfish_sdk/sdk/include/libMediaSdk")
INCLUDE_DIRECTORIES("../../dependency/MoyeaBased/include")
INCLUDE_DIRECTORIES("../interfaces")




if (APPLE)
    add_custom_command(
            OUTPUT CopyDylib
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ui_plugins/*.dylib"
            "$<TARGET_FILE_DIR:Billfish>/../Resources/ui_plugins"
    )

    add_custom_command(
            OUTPUT RM_DYLIB
            COMMAND rm -rf
            "$<TARGET_FILE_DIR:Billfish>/../Resources/ui_plugins/*.dylib"
    )

    add_executable(Billfish
            ${SOURCE_FILE}
            RM_DYLIB
            CopyDylib
            )

    SET_TARGET_PROPERTIES(Billfish
            PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/macosx/Info.plist
            )
    add_dependencies(
            Billfish
            basemodule
            bfmediaplayer
            bfright
            bfsetting
            bigimgpreview
            datacenter
            importtask
            mainwidget
            netserver
            tagmanager
            treemodule
            viewmanager
    )
    target_link_directories(Billfish PUBLIC
            "../../dependency/ATAnalytics/PLCrashReporter"
            "../../dependency/openssl_r/osx-x64"
            "../../dependency/sqlite3_r/osx-x64"
            "../../dependency/iconv_r/osx-x64"
            "/usr/lib"
            "../../dependency/zlib_r/osx-x64"
            "../../dependency/billfish_sdk/sdk/osx-x64"
            )

    target_link_libraries(Billfish Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets Qt5::Xml log4qt utils skin bfdownload  bfcommon ${PLATFORM_SPECIFIC_LIBS}
            "${CMAKE_CURRENT_SOURCE_DIR}/../../dependency/ui_sdk/osx-x64/libCommon.a"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../dependency/ui_sdk/osx-x64/LogServer.dylib"
            icuuc.54
            icui18n.54
            icudata.54
            iconv.2.4.0
            z
            CrashReporter-MacOSX-Static
            crypto
            ssl
            sqlite3
            traceEvent
            )

    add_custom_command(TARGET Billfish
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change  @rpath/libskin.dylib @executable_path/libskin.dylib
            $<TARGET_FILE:Billfish>)

    add_custom_command(TARGET Billfish
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change  @rpath/libbfdownload.dylib @executable_path/libbfdownload.dylib
            $<TARGET_FILE:Billfish>)

    add_custom_command(TARGET Billfish
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change  @rpath/libbfcommon.dylib @executable_path/libbfcommon.dylib
            $<TARGET_FILE:Billfish>)

    add_custom_command(TARGET Billfish
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change  @rpath/liblog4qt.dylib @executable_path/liblog4qt.dylib
            $<TARGET_FILE:Billfish>)

    add_custom_command(TARGET Billfish
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change  @rpath/libtraceEvent.dylib @executable_path/libtraceEvent.dylib
            $<TARGET_FILE:Billfish>)

    add_custom_command(TARGET Billfish POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources"
            "$<TARGET_FILE_DIR:Billfish>/../Resources"
            )

    add_custom_command(TARGET Billfish POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/*.dylib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../dependency/openssl_r/osx-x64/libssl.1.0.0.dylib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../dependency/openssl_r/osx-x64/libcrypto.1.0.0.dylib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../dependency/ui_sdk/osx-x64/LogServer.dylib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../dependency/base_platform_sdk/osx-x64/Jnz.dylib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../dependency/base_platform_sdk/osx-x64/Jnz"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../../bin/appConfig.json"
            "$<TARGET_FILE_DIR:Billfish>/../MacOS"
            )

    add_custom_command(TARGET Billfish POST_BUILD
            COMMAND chmod 777
            "$<TARGET_FILE_DIR:Billfish>/../MacOS/Jnz"
            )

    #    add_custom_command(TARGET Billfish POST_BUILD
    #            COMMAND ${CMAKE_COMMAND} -E copy
    #            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ui_plugins/*.dylib"
    #            "$<TARGET_FILE_DIR:Billfish>/../Resources/ui_plugins"
    #            )


endif (APPLE)


