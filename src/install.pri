win32 
{
  INSTALL_BINS             = $$INSTALL_PREFIX/$$INSTALL_APP_DIR
  INSTALL_LIBS             = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/$$INSTALL_LIB_DIR
  INSTALL_PLUGINS          = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/$$INSTALL_LIB_DIR/ui_plugins
  INSTALL_RESOURCES        = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/$$INSTALL_RES_DIR/resources
  INSTALL_DOCUMENTS        = $$INSTALL_PREFIX/$$INSTALL_APP_DIR
  INSTALL_TRANSLATIONS     = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/$$INSTALL_RES_DIR/translations
}
else:macx
{
  INSTALL_BINS             = $$INSTALL_PREFIX
  INSTALL_LIBS             = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/Contents/$$INSTALL_LIB_DIR
  INSTALL_PLUGINS          = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/Contents/PlugIns
  INSTALL_RESOURCES        = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/Contents/$$INSTALL_RES_DIR
  INSTALL_DOCUMENTS        = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/Contents/$$INSTALL_RES_DIR
  INSTALL_TRANSLATIONS     = $$INSTALL_PREFIX/$$INSTALL_APP_DIR/Contents/$$INSTALL_RES_DIR/translations

    bundle_target.files += $$PWD/../bin/resources/themes
    bundle_target.files += $$PWD/../bin/resources/translations
    bundle_target.files += $$PWD/../bin/resources/skin
    bundle_target.files += $$PWD/../bin/resources/animation
    bundle_target.files += $$PWD/../bin/ui_plugins
    bundle_target.files += $$PWD/../bin/resources/log4qt.conf
    bundle_target.files += $$PWD/../bin/resources/qt.conf
    bundle_target.files += $$PWD/../bin/resources/folder.ico
    bundle_target.files += $$PWD/../bin/resources/folder.icns
    bundle_target.path = Contents/Resources
    QMAKE_BUNDLE_DATA += bundle_target

    bundle_plugin.files += $$LIBSDESTDIR/libskin.dylib
    bundle_plugin.files += $$LIBSDESTDIR/libbfdownload.dylib
    bundle_plugin.files += $$LIBSDESTDIR/liblog4qt.dylib
    bundle_plugin.files += $$LIBSDESTDIR/libtraceEvent.dylib
    bundle_plugin.files += $$LIBSDESTDIR/libbfcommon.dylib
    bundle_plugin.files += $$LIBSDESTDIR/libinterfaces_plugin.dylib
    bundle_plugin.files += $$PWD/../bin/appConfig.json
    bundle_plugin.files += $$PWD/../dependency/openssl_r/osx-x64/libssl.1.0.0.dylib
    bundle_plugin.files += $$PWD/../dependency/openssl_r/osx-x64/libcrypto.1.0.0.dylib
    bundle_plugin.files += $$PWD/../dependency/ui_sdk/osx-x64/LogServer.dylib
    bundle_plugin.files += $$PWD/../dependency/base_platform_sdk/osx-x64/Jnz.dylib
    bundle_plugin.files += $$PWD/../dependency/base_platform_sdk/osx-x64/Jnz
    bundle_plugin.path = Contents/MacOS
    QMAKE_BUNDLE_DATA += bundle_plugin
}

