# SKATRAK-Playground #
Pequeño programa que consiste en varios juegos típicos de mesa o
clásicos del PC. Incluirá multijugador para algunos de ellos.

## Licencia ##
Este juego estará bajo la licencia **LGPL** (GNU Lesser General Public
License). Leer más [aquí](http://www.gnu.org/licenses/lgpl.html).

## Posibles juegos ##
- 3 en raya
- Conecta 4 (HECHO)
- Hundir la flota
- Pong
- Encontrar las parejas
- Snake
- Comecocos

## Autor/es ##
Hasta el momento todo el código ha sido escrito por mí.
De todas formas quien quiera participar en el proyecto, ya sea aportando
**código**, haciendo de **beta-tester** o haciendo el **diseño gráfico**
del programa y los minijuegos bienvenido sea. Toda ayuda será reflejada
aquí, por supuesto.

## Contacto ##
Para contactar conmigo, [este](mailto:theSkatrak@gmail.com) es mi correo
electrónico.

Para los que quieran estar al día, este es el blog del proyecto, donde
intentaré ir actualizando cada semana los cambios importantes que haya
realizado en el proyecto: <http://skatrakplayground.wordpress.com/>.

## Construcción del proyecto ##
Para **compilar** el proyecto, dependiendo de la plataforma habrá que
hacer una cosa u otra.

### Linux ###
Para compilar en **Linux**, los pasos a seguir son:

- Instalar CMake y g++ si no lo están. Para comprobarlo escribir en una
terminal:

    g++ --version
    cmake --version
- Instalar las librerías de **desarrollo** de [SDL][linkSDL],
[SDL_image][linkSDLimage], [SDL_mixer][linkSDLmixer] y
[SDL_ttf][linkSDLttf].
- Abrir una terminal
- Escribir en la terminal:

      cd ruta/hasta/build
      cmake ../project
      make
- Si la compilación se hace satisfactoriamente, el ejecutable estará en
*build/bin*

Para generar un archivo de proyecto de **Code::Blocks** en lugar de un
**Makefile**, en lugar de hacer `cmake ../project`, hay que hacer
`cmake ../project -G "CodeBlocks"`.

### Windows ###
He preparado varias maneras de compilar en **Windows**. Sólo he podido
probar estos métodos en **Windows 7** (x64). Si encuentran algún
**problema** al compilar en otros sistemas operativos Windows háganmelo
saber.

#### CMD ###
Para esto debes **descargar** e **instalar** antes [MinGW](http://downloads.sourceforge.net/project/mingw/Installer/mingw-get-inst/mingw-get-inst-20120426/mingw-get-inst-20120426.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fmingw%2Ffiles%2FInstaller%2Fmingw-get-inst%2F&ts=1353678569&use_mirror=ignum).
Luego vas a la carpeta *project* y abres el archivo
*script compilador windows.bat*. Te preguntará por el directorio *bin*
de tu instalación de **MinGW**. Lo introduces y pulsas "Enter".
Por defecto, la ruta de esta carpeta es *C:\\MinGW\\bin*. Si has
instalado MinGW en esta carpeta, tan sólo tienes que pulsar "Enter" sin
especificar ruta. El proyecto se **compilará** y si no hay errores el
ejecutable se encontrará en *build\\bin*.

#### wx-DevC++ ####
Este método requiere haber instalado previamente el programa
(disponible [aquí](http://downloads.sourceforge.net/project/wxdsgn/wxDev-C%2B%2B/Version%207/wxdevcpp_7.4.2_full_setup.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fwxdsgn%2Ffiles%2FwxDev-C%252B%252B%2FVersion%25207%2F&ts=1353681832&use_mirror=heanet)).
Lo único que hay que hacer es **abrir** el archivo
*project\\SKATRAK Playground.dev* y utilizar la opción de **compilar**
del programa. El ejecutable estará situado en *build\\bin*.

#### Visual Studio ####
Para los que dispongan de este programa, también está el archivo de
proyecto en *project\\SKATRAK Playground.vcxproj* en el que tan sólo
hay que **compilar** y el ejecutable aparece en *build\\bin*.

## Ejecución del juego ##
Una vez obtenido el **ejecutable** del juego, ya sea por una
**compilación propia** o por **descarga**, para ejecutarlo es necesario
obtener las **librerías de ejecución** (Runtime Libraries) de **SDL**.

En **Windows**, sólo hay que descargar los comprimidos siguientes:
[Enlace 1](http://www.libsdl.org/release/SDL-1.2.15-win32.zip),
[Enlace 2](http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12-win32.zip),
[Enlace 3](http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-1.2.12-win32.zip),
[Enlace 4](http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11-win32.zip).
Luego **descomprimir** estos archivos y por último copiar los .dll
en la carpeta *build\\bin* del proyecto.

En **Linux** hay que descargar las librerías de [SDL][linkSDL], [SDL_image][linkSDLimage], [SDL_mixer][linkSDLmixer] y [SDL_ttf][linkSDLttf]
o mediante los comandos (probados en Ubuntu 12.10):

    sudo apt-get install libsdl1.2debian
    sudo apt-get install libsdl-image1.2
    sudo apt-get install libsdl-mixer1.2
    sudo apt-get install libsdl-ttf2.0

[linkSDL]: http://www.libsdl.org/download-1.2.php
[linkSDLimage]: http://www.libsdl.org/projects/SDL_image/
[linkSDLmixer]: http://www.libsdl.org/projects/SDL_mixer/
[linkSDLttf]: http://www.libsdl.org/projects/SDL_ttf/
