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
set OUTPUT="..\bin\windows\SKATRAK Playground.exe"

rem Listado de módulos objeto
set OBJECTS_GEN="%OBJDIR%\system.o" "%OBJDIR%\main.o" "%OBJDIR%\music.o" "%OBJDIR%\image.o" "%OBJDIR%\timekeeper.o" "%OBJDIR%\font.o" "%OBJDIR%\inifile.o" "%OBJDIR%\sfx.o" "%OBJDIR%\str_operations.o" "%OBJDIR%\menu.o" "%OBJDIR%\mainMenu.o" "%OBJDIR%\messagebox.o"
set OBJECTS_C4="%OBJDIR%\mainConecta4.o" "%OBJDIR%\tablero.o" "%OBJDIR%\gameConecta4.o" "%OBJDIR%\messagesConecta4.o"
set OBJECTS_SNK="%OBJDIR%\mainSnake.o" "%OBJDIR%\snakePiece.o" "%OBJDIR%\snake.o" "%OBJDIR%\gameSnake.o" "%OBJDIR%\snakeMap.o"

rem Compilamos los módulos objeto por separado
echo Compilando modulos objeto...
for /R %%i in (%SRCDIR%\*.cpp) do (call :compile "%%~nxi" %SRCDIR%)
for /R %%i in (%SRCDIR%\conecta4\*.cpp) do (call :compile "%%~nxi" %SRCDIR%\conecta4)
for /R %%i in (%SRCDIR%\snake\*.cpp) do (call :compile "%%~nxi" %SRCDIR%\snake)

rem Juntamos todos los módulos objeto en un solo ejecutable.
echo Compilando ejecutable...
"%gpp%\g++.exe" -s -O2 -o %OUTPUT% %OBJECTS_GEN% %OBJECTS_C4% %OBJECTS_SNK% %LIBS%
if %errorlevel% neq 0 set error=true

rem Decimos que la compilación ha acabado y pausamos el programa para que el usuario pueda leer los fallos en el caso de que los haya.
echo Compilacion finalizada.
if "%error%"=="true" (echo Han habido errores en la compilacion.) else (echo La compilacion se ha realizado satisfactoriamente.)
pause>nul
exit

:compile
set filename=%~n1.o
echo Compilando "%filename%"...
"%gpp%\g++.exe" %CFLAGS% -o "%OBJDIR%\%filename%" "%~2\%~1"
if %errorlevel% neq 0 set error=true
