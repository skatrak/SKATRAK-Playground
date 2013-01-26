@echo off

rem SCRIPT COMPILADOR PARA WINDOWS
rem ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

rem Preguntamos al usuario la dirección del compilador GNU
set /p gpp="Introduce la ruta completa o relativa al directorio donde se encuentra g++ (Por defecto 'C:\MinGW\bin'): "

rem Si la respuesta está vacía ponemos la ruta por defecto
if "%gpp%" equ "" set gpp=C:\MinGW\bin

rem Comprobamos que el compilador está en esa ruta
if not exist "%gpp%\g++.exe" echo No se encuentra g++.exe en %gpp%. Recuerda que hay que instalar MinGW para poder compilar usando este método. && pause>nul && exit

rem esta variable comprobará si hay algún error en el proceso de compilado.
set error=false

rem Argumentos para compilar y enlazar los códigos objeto. -mwindows para que no aparezca una consola.
set CFLAGS=-Wall -c -I"..\include"
set LIBS=-L"..\lib\windows" -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf

rem Directorios importantes
set OBJDIR=..\bin\windows\obj
set SRCDIR=..\src
set OBJECTS_GEN="%OBJDIR%\main.o" "%OBJDIR%\music.o" "%OBJDIR%\system.o" "%OBJDIR%\image.o" "%OBJDIR%\timekeeper.o" "%OBJDIR%\font.o" "%OBJDIR%\inifile.o" "%OBJDIR%\sfx.o" "%OBJDIR%\str_operations.o" "%OBJDIR%\menu.o" "%OBJDIR%\mainMenu.o" "%OBJDIR%\messagebox.o"
set OBJECTS_C4="%OBJDIR%\tablero.o" "%OBJDIR%\mainConecta4.o" "%OBJDIR%\gameConecta4.o" "%OBJDIR%\messagesConecta4.o"
set OUTPUT="..\bin\windows\SKATRAK Playground.exe"

rem Compilamos los módulos objeto por separado
echo Compilando modulos objeto...
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\main.o" "%SRCDIR%\main.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\music.o" "%SRCDIR%\music.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\system.o" "%SRCDIR%\system.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\image.o" "%SRCDIR%\image.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\timekeeper.o" "%SRCDIR%\timekeeper.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\font.o" "%SRCDIR%\font.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\inifile.o" "%SRCDIR%\inifile.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\sfx.o" "%SRCDIR%\sfx.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\str_operations.o" "%SRCDIR%\str_operations.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\menu.o" "%SRCDIR%\menu.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\mainMenu.o" "%SRCDIR%\mainMenu.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\messagebox.o" "%SRCDIR%\messagebox.cpp"
if %errorlevel% neq 0 set error=true
rem Conecta 4
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\tablero.o" "%SRCDIR%\conecta4\tablero.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\mainConecta4.o" "%SRCDIR%\conecta4\mainConecta4.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\gameConecta4.o" "%SRCDIR%\conecta4\gameConecta4.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\messagesConecta4.o" "%SRCDIR%\conecta4\messagesConecta4.cpp"
if %errorlevel% neq 0 set error=true

rem Juntamos todos los módulos objeto en un solo ejecutable.
echo Compilando ejecutable...
"%gpp%\g++.exe" -s -O2 -o %OUTPUT% %OBJECTS_GEN% %OBJECTS_C4% %LIBS%
if %errorlevel% neq 0 set error=true

rem Decimos que la compilación ha acabado y pausamos el programa para que el usuario pueda leer los fallos en el caso de que los haya.
echo Compilacion finalizada.
if "%error%"=="true" (echo Han habido errores en la compilacion.) else (echo La compilacion se ha realizado satisfactoriamente.)
pause>nul
