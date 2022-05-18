INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(../)
set(COMMON_FILE
bfcommon.cpp
update_thread/CUpdateThread.cpp
zip/unzip.c
zip/zip.c
zip/ioapi.c
APP_GLOBAL_CONSTANT.h
bfcommon.h
bfcommon_export.h
update_thread/CUpdateThread.h
zip/unzip.h
zip/zip.h
zip/crypt.h
zip/ioapi.h
        )


set(SPECIFIC_FILES)
if (APPLE)
    INCLUDE_DIRECTORIES(../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK)
    INCLUDE_DIRECTORIES(Platform/MacOs)

    list(APPEND SPECIFIC_FILES
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashDetails.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashManager.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATASystemProfile.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/ATAEventTracker.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/JSONUtil.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/MessageQueueBySqlite.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/NSString+HashCode.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SACommonUtility.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAGzipUtility.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SALogger.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAReachability.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsExceptionHandler.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsSDK.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SSZipArchive.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker/ATALogTracker.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/ATAMidTool.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5_tool.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/cpu_id.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/disk_serialno.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_address.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_appver.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/platform_info.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATANetWorkClient.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/ATARSACryptor.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMBase64.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMDefines.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDK.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDKDefines.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils/ATAnalyticsSDKHelper.h
    ../../dependency/ATAnalytics/UpgradeInfo/UpdateViewModel.h
    ../../dependency/ATAnalytics/UpgradeInfo/NewVersionInfo.h
    ../../dependency/ATAnalytics/Feedback/FeedbackInfo.h
    common_util.h
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5.c
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5_tool.cpp
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/cpu_id.cpp
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/disk_serialno.cpp
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_address.cpp
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/platform_info.cpp
    common_util.cpp
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashDetails.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashManager.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATASystemProfile.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/ATAEventTracker.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/JSONUtil.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/MessageQueueBySqlite.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/NSString+HashCode.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SACommonUtility.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAGzipUtility.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SALogger.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAReachability.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsExceptionHandler.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsSDK.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SSZipArchive.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker/ATALogTracker.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/ATAMidTool.mm
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_appver.mm
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATANetWorkClient.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/ATARSACryptor.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMBase64.m
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDK.m
    ../../dependency/ATAnalytics/UpgradeInfo/UpdateViewModel.mm
    ../../dependency/ATAnalytics/UpgradeInfo/NewVersionInfo.mm
    ../../dependency/ATAnalytics/Feedback/FeedbackInfo.mm
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils/ATAnalyticsSDKHelper.m
    ./macos/EventTracker.h
    ./macos/EventTrackProvider.h
    ./macos/SOFTWARE_ERROR_CODE.h
    ./macos/EventTrackCInterface.h
    ./macos/EventTrackProvider.mm
            )

    set_source_files_properties(
            ${SPECIFIC_FILES}
            PROPERTIES
            COMPILE_FLAGS -fobjc-weak
            COMPILE_FLAGS -fobjc-arc

    )

endif(APPLE)


add_library(bfcommon SHARED
        ${COMMON_FILE}
        ${SPECIFIC_FILES}
        )


INCLUDE_DIRECTORIES("../../dependency/zlib_r/include")
INCLUDE_DIRECTORIES("../../dependency/ui_sdk/include")
INCLUDE_DIRECTORIES("../../dependency/json_r/include")
INCLUDE_DIRECTORIES("../../dependency/openssl_r/include")
INCLUDE_DIRECTORIES("../../dependency/base_platform_sdk/include")
INCLUDE_DIRECTORIES("../../dependency/billfish_sdk/sdk/include")


if (APPLE)



    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/PLCrashReporter/include")

    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/Utils")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAEventTracker/SensorsAnalyticsSDK ")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/Utils")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform")
    INCLUDE_DIRECTORIES("../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool")
    INCLUDE_DIRECTORIES("zip")

    target_link_directories(bfcommon PUBLIC
            "../../dependency/ATAnalytics/PLCrashReporter"
            "../../dependency/openssl_r/osx-x64"
            "../../dependency/sqlite3_r/osx-x64"
            "../../dependency/iconv_r/osx-x64"
            "/usr/lib"
            "../../dependency/zlib_r/osx-x64"
            "../../dependency/billfish_sdk/sdk/osx-x64"
            )

    target_link_libraries(bfcommon Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets ${PLATFORM_SPECIFIC_LIBS}
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
            )
endif (APPLE)

