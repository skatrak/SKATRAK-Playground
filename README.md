# SKATRAK-Playground #
Pequeño programa que consiste en varios juegos típicos de mesa o
clásicos del PC. Incluirá multijugador para algunos de ellos. Para la
gestión de los gráficos se apoya en la librería [SDL](http://www.libsdl.org/).

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

## Estructura de directorios ##
- **build**: Directorio donde se realizará la compilación de los ejecutables.
  Es conveniente colocar los .dll de SDL en Windows en un directorio
  *bin* dentro de éste, para poder hacer funcionar el juego.

- **doc**: En este directorio se encuentra el *Doxyfile* que permite generar
  la documentación acerca de las clases que componen el código del
  juego. Para generar la documentación hay que instalar [Doxygen](http://www.stack.nl/~dimitri/doxygen/),
  colocarse con una terminal en este directorio y ejecutar `doxygen`.

- **include**: Directorio donde se encuentran las cabeceras del proyecto.
  Hay un directorio por cada minijuego donde se encuentran las cabeceras
  específicas del mismo. También se encuentra el directorio *SDL*, el
  cual contiene las cabeceras de SDL. El motivo de que esté aquí es
  para poder compilar en Windows el juego, aunque mediante CMake
  también es posible hacerlo.

- **lib**: Directorio con las librerías estáticas de SDL para Windows. Está
  aquí por el mismo motivo que el directorio *include/SDL*.

- **project**: Aquí se encuentran aquellos ficheros que permiten compilar
  el proyecto con facilidad:

  - CMakeLists.txt
  - SKATRAK Playground.vcxproj
  - SKATRAK Playground.dev
  - script compilador windows.bat

- **resources**: Se encuentran aquí todos los recursos (imágenes, fuentes,
  sonidos...) que utiliza el proyecto. Es posible descomentar en el
  fichero *src/main.cpp* la línea `#define _RELEASE_VER` para que el
  ejecutable espere que el directorio *resources* se encuentre en su mismo
  directorio.

- **src**: Directorio con los archivos de código fuente del proyecto. Existe
  también un directorio por cada minijuego donde va la implementación
  de funcionalidades propias de ese minijuego.

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
[SDL\_image][linkSDLimage], [SDL\_mixer][linkSDLmixer] y
[SDL\_ttf][linkSDLttf].
- Abrir una terminal
- Escribir en la terminal:

        cd ruta/hasta/build
        cmake ../project
        make

- Si la compilación se hace satisfactoriamente, el ejecutable estará en
*build/bin*

Para generar un archivo de proyecto de **Code::Blocks** en lugar de un
**Makefile**, en lugar de hacer `cmake ../project`, hay que hacer
`cmake ../project -G "CodeBlocks"`. Si no funciona así, consulta
la ayuda de la versión de **CMake** instalada mediante `cmake --help` para
consultar el nombre del generador para **Code::Blocks**.

### Windows ###
He preparado varias maneras de compilar en **Windows**. Sólo he podido
probar estos métodos en **Windows 7 Home Premium** (x64). Si encuentran
algún **problema** al compilar en otros sistemas operativos Windows háganmelo
saber.

Una vez compilado el ejecutable, en el directorio *build/bin* se deben copiar las
librerías de enlazado dinámico de SDL, que se pueden conseguir en los enlaces
siguientes:
[Enlace 1](http://www.libsdl.org/release/SDL-1.2.15-win32.zip),
[Enlace 2](http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12-win32.zip),
[Enlace 3](http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-1.2.12-win32.zip),
[Enlace 4](http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11-win32.zip).
Se deben **descomprimir** estos archivos y por último copiar los .dll
en la carpeta.

#### CMD ###
Para esto debes **descargar** y **descomprimir** antes
[MinGW](http://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.8.0/32-bit/threads-posix/dwarf/x32-4.8.0-release-posix-dwarf-rev1.7z/download).
Luego vas a la carpeta *project* y abres el archivo
*script compilador windows.bat*. Te preguntará por el directorio *bin*
de tu instalación de **MinGW**. Lo introduces y pulsas "Enter". El proyecto se **compilará** y si no hay errores el
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
### Requisitos ###
- Sistema Operativo: Cualquier S.O. soportado por la librería SDL. Según
  la [página oficial](http://www.libsdl.org/):
  - Linux
  - Windows
  - Windows CE
  - BeOS
  - MacOS
  - Mac OS X
  - FreeBSD
  - NetBSD
  - OpenBSD
  - BSD/OS
  - Solaris
  - IRIX
  - QNX
- Librerías de ejecución de [SDL][linkSDL], [SDL\_image][linkSDLimage],
  [SDL\_mixer][linkSDLmixer] y [SDL\_ttf][linkSDLttf]. Si descargas el juego
  ya compilado para Windows, esto no es necesario ya que las .dll van
  incluidas en el comprimido.

### Descarga ###
He abierto una forja en **SourceForge** donde pondré con cierta regularidad
descargas del juego ya compilado para las plataformas que me sea posible.
La página de descargas se encuentra [aquí](http://sourceforge.net/projects/skatrakpgnd/files/?source=navbar).

### Ejecución ###
Una vez obtenido el ejecutable del juego mediante descarga, si es en **Windows**
se puede ejecutar directamente. En el caso de **Linux** (aún sin descargas disponibles)
sería necesario instalar las librerías de **ejecución** de SDL. En una distribución basada
en **Debian**:

    sudo apt-get install libsdl1.2debian
    sudo apt-get install libsdl-image1.2
    sudo apt-get install libsdl-mixer1.2
    sudo apt-get install libsdl-ttf2.0

En caso de una distribución de **Linux** basada en **RedHat**, los .rpm se podrían
conseguir de la [página oficial de SDL](http://www.libsdl.org/download-1.2.php) y
para las librerías extra (image, mixer y ttf), se pueden encontrar [aquí](http://www.libsdl.org/projects/).

[linkSDL]: http://www.libsdl.org/download-1.2.php
[linkSDLimage]: http://www.libsdl.org/projects/SDL_image/
[linkSDLmixer]: http://www.libsdl.org/projects/SDL_mixer/
[linkSDLttf]: http://www.libsdl.org/projects/SDL_ttf/
