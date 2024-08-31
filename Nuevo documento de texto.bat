@echo off
REM Configurar el entorno virtual para Visual Studio

REM Establecer rutas específicas para cl, cmake y ninja
set CL_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.41.34120\bin\Hostx64\x64"
set CMAKE_PATH="C:\Program Files\CMake\bin"
set NINJA_PATH="C:\path\to\ninja\bin"

REM Modificar el PATH para que solo incluya las rutas necesarias
set PATH=%CL_PATH%;%CMAKE_PATH%;%NINJA_PATH%;%PATH%

REM Llamar a vcvarsall.bat para configurar las variables de entorno de Visual Studio
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

REM Activar el Developer Command Prompt para Visual Studio con las nuevas variables de entorno
start "" cmd.exe /k
