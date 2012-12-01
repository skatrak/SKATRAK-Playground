@echo off

rem SCRIPT COMPILADOR PARA WINDOWS
rem ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

rem Preguntamos al usuario la dirección del compilador GNU
set /p gpp="Introduce la ruta completa o relativa al directorio donde se encuentra g++ (Por defecto 'C:\MinGW\bin'): "

rem Comprobamos que la respuesta no esté vacía
if "%gpp%" equ "" echo Para compilar, debes descargar primero MinGW e indicar aqui la ruta de su carpeta bin. && pause>nul && exit

rem esta variable comprobará si hay algún error en el proceso de compilado.
set error=false

rem Argumentos para compilar y enlazar los códigos objeto. -mwindows para que no aparezca una consola.
set CFLAGS=-Wall -c -I"..\include"
set LIBS=-L"..\lib\windows" -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf
set OBJECTS="..\bin\windows\obj\main.o" "..\bin\windows\obj\music.o" "..\bin\windows\obj\system.o" "..\bin\windows\obj\image.o" "..\bin\windows\obj\timekeeper.o" "..\bin\windows\obj\font.o" "..\bin\windows\obj\inifile.o" "..\bin\windows\obj\sfx.o" "..\bin\windows\obj\str_operations.o" "..\bin\windows\obj\mainMenu.o"
set OUTPUT="..\bin\windows\SKATRAK Playground.exe"

rem Compilamos los módulos objeto por separado
echo Compilando modulos objeto...
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\main.o" "..\src\main.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\music.o" "..\src\music.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\system.o" "..\src\system.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\image.o" "..\src\image.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\timekeeper.o" "..\src\timekeeper.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\font.o" "..\src\font.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\inifile.o" "..\src\inifile.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\sfx.o" "..\src\sfx.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\str_operations.o" "..\src\str_operations.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\mainMenu.o" "..\src\mainMenu.cpp"
if %errorlevel% neq 0 set error=true

rem Juntamos todos los módulos objeto en un solo ejecutable.
echo Compilando ejecutable...
"%gpp%\g++.exe" -O2 -o %OUTPUT% %OBJECTS% %LIBS%
if %errorlevel% neq 0 set error=true

rem Decimos que la compilación ha acabado y pausamos el programa para que el usuario pueda leer los fallos en el caso de que los haya.
echo Compilacion finalizada.
if "%error%"=="true" (echo Han habido errores en la compilacion.) else (echo La compilacion se ha realizado satisfactoriamente.)
pause>nul
