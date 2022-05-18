@echo off
set output_path=%~1
set qt_path=%~2
set vc_install=%~3

@rem plugin
mkdir %output_path%\ui_plugins

@rem translations
mkdir %output_path%\Resources\translations\zh_CN
xcopy /y /s .\..\..\src\translations\zh_CN\*.qm %output_path%\Resources\translations\zh_CN\

mkdir %output_path%\Resources
copy /y .\..\..\resource\config\log4qt.conf %output_path%\Resources
copy /y .\..\..\resource\config\appConfig.json %output_path%

mkdir %output_path%\Resources\themes\default
xcopy /y /s .\..\..\resource\qss\*.css %output_path%\Resources\themes\default

xcopy /y /s .\..\..\dependency\ui_sdk\win-x64-msvc\bin\*.dll %output_path%

xcopy /y /s .\..\..\dependency\billfish_sdk\sdk\win-x64-msvc\bin\*.*  %output_path%
xcopy /y /s .\..\..\dependency\sqlite3_r\win-x64-msvc\bin\*.dll %output_path%
xcopy /y /s .\..\..\dependency\base_platform_sdk\win-x64-msvc\bin\*.dll %output_path%
xcopy /y /s .\..\..\dependency\base_platform_sdk\win-x64-msvc\bin\*.exe %output_path%
mkdir %output_path%\x86
xcopy /y /s .\..\..\dependency\base_platform_sdk\win-x86-msvc\bin\*.exe %output_path%\x86
xcopy /y /s .\..\..\dependency\base_platform_sdk\win-x86-msvc\bin\*.dll %output_path%\x86

del /s /q %output_path%\ffmpeg64.exe
del /s /q %output_path%\libMediaCam64.dll

copy /y .\..\..\dependency\billfish_sdk\sdk\win-x86-msvc\bin\ssleay32.dll %output_path%\x86\
copy /y .\..\..\dependency\billfish_sdk\sdk\win-x86-msvc\bin\libeay32.dll %output_path%\x86\

copy /y .\..\..\dependency\7z_r\win-x64-msvc\bin\7za.exe %output_path%

copy /y .\..\..\resource\config\qt.conf %output_path%
@REM \mediainfo_r
xcopy /y /s .\..\..\dependency\mediainfo_r\win-x64-msvc\bin\*.dll %output_path%



::create skin folder and copy skin source to skin folder
mkdir %output_path%\Resources\skin
xcopy /y /s .\..\..\resource\skin    %output_path%\Resources\skin
copy /y .\..\..\resource\library_icon\folder.icns  %output_path%\Resources
copy /y .\..\..\resource\library_icon\folder.ico  %output_path%\Resources
copy /y .\..\..\resource\wizard\wizard_win.zip  %output_path%\Resources\wizard.zip

mkdir %output_path%\Resources\animation
xcopy /y /s .\..\..\resource\animation    %output_path%\Resources\animation

@rem deploy qt framwork
call "%vc_install%Auxiliary\Build\vcvars64.bat"
"%qt_path%\bin\windeployqt.exe" %output_path%\Billfish.exe

@REM @rem del vc_redist from qt
del /s /q %output_path%\vc_redist.x64.exe
