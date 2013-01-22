@echo off

rem SCRIPT COMPILADOR PARA WINDOWS
rem ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

rem Preguntamos al usuario la direcci�n del compilador GNU
set /p gpp="Introduce la ruta completa o relativa al directorio donde se encuentra g++ (Por defecto 'C:\MinGW\bin'): "

rem Si la respuesta est� vac�a ponemos la ruta por defecto
if "%gpp%" equ "" set gpp=C:\MinGW\bin

rem Comprobamos que el compilador est� en esa ruta
if not exist "%gpp%\g++.exe" echo No se encuentra g++.exe en %gpp%. Recuerda que hay que instalar MinGW para poder compilar usando este m�todo. && pause>nul && exit

rem esta variable comprobar� si hay alg�n error en el proceso de compilado.
set error=false

rem Argumentos para compilar y enlazar los c�digos objeto. -mwindows para que no aparezca una consola.
set CFLAGS=-Wall -c -I"..\include"
set LIBS=-L"..\lib\windows" -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf
set OBJECTS="..\bin\windows\obj\main.o" "..\bin\windows\obj\music.o" "..\bin\windows\obj\system.o" "..\bin\windows\obj\image.o" "..\bin\windows\obj\timekeeper.o" "..\bin\windows\obj\font.o" "..\bin\windows\obj\inifile.o" "..\bin\windows\obj\sfx.o" "..\bin\windows\obj\str_operations.o" "..\bin\windows\obj\menu.o" "..\bin\windows\obj\mainMenu.o" "..\bin\windows\obj\messagebox.o" "..\bin\windows\obj\tablero.o" "..\bin\windows\obj\mainConecta4.o" "..\bin\windows\obj\Game_Conecta4.o" "..\bin\windows\obj\messagesConecta4.o"
set OUTPUT="..\bin\windows\SKATRAK Playground.exe"

rem Compilamos los m�dulos objeto por separado
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
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\menu.o" "..\src\menu.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\mainMenu.o" "..\src\mainMenu.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\messagebox.o" "..\src\messagebox.cpp"
if %errorlevel% neq 0 set error=true
rem Conecta 4
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\tablero.o" "..\src\conecta4\tablero.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\mainConecta4.o" "..\src\conecta4\mainConecta4.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\Game_Conecta4.o" "..\src\conecta4\Game_Conecta4.cpp"
if %errorlevel% neq 0 set error=true
"%gpp%\g++.exe" %CFLAGS% -o "..\bin\windows\obj\messagesConecta4.o" "..\src\conecta4\messagesConecta4.cpp"
if %errorlevel% neq 0 set error=true

rem Juntamos todos los m�dulos objeto en un solo ejecutable.
echo Compilando ejecutable...
"%gpp%\g++.exe" -s -O2 -o %OUTPUT% %OBJECTS% %LIBS%
if %errorlevel% neq 0 set error=true

rem Decimos que la compilaci�n ha acabado y pausamos el programa para que el usuario pueda leer los fallos en el caso de que los haya.
echo Compilacion finalizada.
if "%error%"=="true" (echo Han habido errores en la compilacion.) else (echo La compilacion se ha realizado satisfactoriamente.)
pause>nul
