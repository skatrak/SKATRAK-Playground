# SKATRAK-Playground #

Pequeño programa que consiste en varios juegos típicos de mesa o clásicos del PC. Incluirá multijugador para algunos de ellos.

## Licencia ##
Este juego estará bajo la licencia **LGPL** (GNU Lesser General Public License). Leer más [aquí](http://www.gnu.org/licenses/lgpl.html).

## Posibles juegos ##
- 3 en raya
- Conecta 4
- Hundir la flota
- Pong
- Encontrar las parejas
- Snake
- Comecocos

## Autor/es ##
Hasta el momento todo el código ha sido escrito por mí.
De todas formas quien quiera participar en el proyecto, ya sea aportando **código**, haciendo de **beta-tester** o haciendo el **diseño gráfico** del programa y los minijuegos bienvenido sea. Toda ayuda será reflejada aquí, por supuesto.

## Contacto ##
Para contactar conmigo, [este](mailto:theSkatrak@gmail.com) es mi correo electrónico.

Para los que quieran estar al día, este es el blog del proyecto, donde intentaré ir actualizando cada semana los cambios importantes que haya realizado en el proyecto: <http://skatrakplayground.wordpress.com/>.

## Construcción del proyecto ##
El juego estará siempre con la última versión compilada la mayor parte del tiempo, pero puede ser que por falta de tiempo a veces el código fuente esté más actualizado que el ejecutable. También puede ser que hagas modificaciones en el código y desees probar el resultado. Para eso pongo este apartado.

### Linux ###
Aclaro que los sistemas operativos que he utilizado y que he comprobado que funcionan son **Ubuntu 10.04** (x86) y **Ubuntu 12.04** (x64). Avisen si tienen algún problema en otros sistemas operativos para intentar solucionarlos.

Compilar en Linux es muy fácil. Sólo situarse con la terminal en la carpeta *project* y hacer:

    make

Y ya está. Si no hubieron errores el ejecutable estará en *bin/linux*.

### Windows ###
He preparado varias maneras de compilar en **Windows**. Al igual que con **Linux** sólo he podido probar estos métodos con algunos sistemas operativos; en este caso **Windows 7** (x64). Igualmente, si encuentran algún **problema** al compilar en otros sistemas operativos Windows háganmelo saber.

#### CMD ###
Para esto debes **descargar** e **instalar** antes [MinGW](http://downloads.sourceforge.net/project/mingw/Installer/mingw-get-inst/mingw-get-inst-20120426/mingw-get-inst-20120426.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fmingw%2Ffiles%2FInstaller%2Fmingw-get-inst%2F&ts=1353678569&use_mirror=ignum). Luego vas a la carpeta *project* y abres el archivo *"script compilador windows.bat"*. Te preguntará por el directorio *bin* de tu instalación de **MinGW**. Lo introduces y pulsas "Enter". Por defecto, la ruta de esta carpeta es *"C:\MinGW\bin"*. El proyecto se compilará y si no hay errores el ejecutable se encontrará en *bin\windows*.

#### wx-DevC++ ####
Este método requiere haber instalado previamente el programa (disponible [aquí](http://downloads.sourceforge.net/project/wxdsgn/wxDev-C%2B%2B/Version%207/wxdevcpp_7.4.2_full_setup.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fwxdsgn%2Ffiles%2FwxDev-C%252B%252B%2FVersion%25207%2F&ts=1353681832&use_mirror=heanet)). Lo único que hay que hacer es **abrir** el archivo *"project\SKATRAK Playground.dev"* y utilizar la opción de **compilar** del programa. El ejecutable estará situado por supuesto en *"bin\windows"*.

#### Visual Studio ####
Para los que dispongan de este programa, también está el archivo de proyecto en *"project\SKATRAK Playground.vcxproj"* en el que tan sólo hay que **compilar** y el ejecutable aparece en *"bin\windows"*.

La ventaja de los proyectos de **wx-DevC++** y **Visual Studio** es que estos programas incluyen una **IDE** y ya tienen todos los archivos del proyecto incluidos, así que es más fácil explorarlo desde ahí. Para Linux aún no tengo ningún proyecto de programa de este estilo, aunque tengo previsto agregar uno de **Code::Blocks** en breve.