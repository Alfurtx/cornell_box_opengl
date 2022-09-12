@echo off

SETLOCAL

call ".\shell.bat"

REM cl flags
set CLFLAGS=/W3 /Zi /nologo /MD /MP4 /Fecornellbox.exe /WX /EHsc
set CLFLAGS=%CLFLAGS% /wd4005 /wd4305 /wd4267
set CLFLAGS=%CLFLAGS% /Iw:\cornell_box_opengl\libs /Iw:\cornell_box_opengl\libs\glfw\include /Iw:\cornell_box_opengl\libs\glm
set LINKFLAGS=glfw3.lib opengl32.lib shell32.lib gdi32.lib user32.lib kernel32.lib /link
set LINKFLAGS=%LINKFLAGS% /LIBPATH:w:\cornell_box_opengl\libs\glfw\lib-vc2022

set CFILES=

REM Create build directory if it doesnt exist already
IF NOT EXIST ".\build\" mkdir build

REM Get all .cpp files from code dir as well from GLAD source
REM pushd ".\code"
REM for /R %%c in (*.cpp) do call set CFILES=%%c %%CFILES%%
REM popd

pushd ".\libs\glad"
for /R %%c in (*.c) do call set CFILES=%%c %%CFILES%%
popd

REM Compile
pushd ".\build\"
REM cl %CLFLAGS% %CFILES% %LINKFLAGS%
cl %CLFLAGS% ..\code\cornellbox.cpp %CFILES% %LINKFLAGS%
popd

ENDLOCAL
