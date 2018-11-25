@echo off
SET "outputDir=.\bin"
SET "log=%outputDir%\build_debug.log"

ECHO Building debug solution...
echo Cleaning directories before compilation..
RMDIR /S /Q %outputDir%
MKDIR %outputDir%
IF EXIST "%log%" DEL /F /Q "%log%"

echo Building project..
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86 1>"%log%" 2>&1
devenv ".\gtc-vc.sln" /Rebuild "GTAVC zDebug" 1>"%log%" 2>&1

echo. 
IF ERRORLEVEL 1 (
   COLOR c
   echo end %date% - %time%
   echo Build failed! Check build_debug.log in %outputDir%
)
echo. 

echo Copying binaries..
copy /Y "%GTA_VC_DIR%\Core_d.asi" %outputDir%

echo Cleaning source files..
devenv ".\gtc-vc.sln" /Clean 1>NUL 2>&1

ECHO Building release solution...
SET "log=%outputDir%\build_release.log"

echo Building project..
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86 1>"%log%" 2>&1
devenv ".\gtc-vc.sln" /Rebuild "GTAVC Release" 1>"%log%" 2>&1

echo. 
IF ERRORLEVEL 1 (
   COLOR c
   echo end %date% - %time%
   echo Build failed! Check build_release.log in %outputDir%
)
echo. 

echo Copying binaries..
copy /Y "%GTA_VC_DIR%\Core.asi" %outputDir%

echo Cleaning source files..
devenv ".\gtc-vc.sln" /Clean 1>NUL 2>&1
pause