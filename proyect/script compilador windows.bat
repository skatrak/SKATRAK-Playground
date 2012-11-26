@echo off

rem SCRIPT COMPILADOR PARA WINDOWS
rem ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

rem Preguntamos al usuario la dirección del compilador GNU
set /p gpp="Introduce la ruta completa o relativa al directorio donde se encuentra g++: "

rem Comprobamos que la respuesta no esté vacía
if "%gpp%" equ "" echo Para compilar, debes descargar primero MinGW e indicar aqui la ruta de su carpeta bin. && pause>nul && exit

rem esta variable comprobará si hay algún error en el proceso de compilado.
set error=false

rem Compilamos los módulos objeto por separado
echo Compilando modulos objeto...
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\main.o" "..\src\main.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\music.o" "..\src\music.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\system.o" "..\src\system.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\image.o" "..\src\image.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\timekeeper.o" "..\src\timekeeper.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" -c -I"..\include\SDL" -L"..\lib" -o "..\bin\windows\obj\font.o" "..\src\font.cpp"
if %errorlevel% neq 0 set error=true

rem Juntamos todos los módulos objeto en un solo ejecutable. La opción '-mwindows' es para que no se genere una ventana de consola.
echo Compilando ejecutable...
"%gpp%\g++.exe" -O2 -o "..\bin\windows\SKATRAK Playground.exe" "..\bin\windows\obj\main.o" "..\bin\windows\obj\image.o" "..\bin\windows\obj\music.o" "..\bin\windows\obj\system.o" "..\bin\windows\obj\timekeeper.o" "..\bin\windows\obj\font.o" -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf
if %errorlevel% neq 0 set error=true

rem Decimos que la compilación ha acabado y pausamos el programa para que el usuario pueda leer los fallos en el caso de que los haya.
echo Compilacion finalizada.
if "%error%"=="true" (echo Han habido errores en la compilacion.) else (echo La compilacion se ha realizado satisfactoriamente.)
pause>nul