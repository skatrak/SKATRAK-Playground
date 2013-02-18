CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(SKATRAK-Playground)

# Rutas de los archivos
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../include")
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
SET(SOURCE_PATH "${PROJECT_SOURCE_DIR}/../src")

# Argumentos para el compilador
ADD_DEFINITIONS(-O2 -Wall)

# Encontrar SDL
FIND_PACKAGE(SDL REQUIRED)
IF (SDL_FOUND)
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})
	SET (LINK_LIBS ${LINK_LIBS} ${SDL_LIBRARY})
ELSE (SDL_FOUND)
	MESSAGE(FATAL_ERROR "Es necesario instalar las librerías SDL antes de poder generar el proyecto")
ENDIF (SDL_FOUND)

FIND_PACKAGE(SDL_image REQUIRED)
IF (SDLIMAGE_FOUND)
	INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIRS})
	SET (LINK_LIBS ${LINK_LIBS} ${SDLIMAGE_LIBRARY})
ELSE (SDLIMAGE_FOUND)
	MESSAGE(FATAL_ERROR "Es necesario instalar la librería SDL_image antes de poder generar el proyecto")
ENDIF (SDLIMAGE_FOUND)

FIND_PACKAGE(SDL_mixer REQUIRED)
IF (SDLMIXER_FOUND)
	INCLUDE_DIRECTORIES(${SDLMIXER_INCLUDE_DIRS})
	SET (LINK_LIBS ${LINK_LIBS} ${SDLMIXER_LIBRARY})
ELSE (SDLMIXER_FOUND)
	MESSAGE(FATAL_ERROR "Es necesario instalar la librería SDL_mixer antes de poder generar el proyecto")
ENDIF (SDLMIXER_FOUND)

FIND_PACKAGE(SDL_ttf REQUIRED)
IF (SDLTTF_FOUND)
	INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIRS})
	SET (LINK_LIBS ${LINK_LIBS} ${SDLTTF_LIBRARY})
ELSE (SDLTTF_FOUND)
	MESSAGE(FATAL_ERROR "Es necesario instalar la librería SDL_ttf antes de poder generar el proyecto")
ENDIF (SDLTTF_FOUND)

# Compilar el proyecto
ADD_EXECUTABLE(SKATRAK-Playground
	${SOURCE_PATH}/font.cpp
	${SOURCE_PATH}/image.cpp
	${SOURCE_PATH}/inifile.cpp
	${SOURCE_PATH}/main.cpp
	${SOURCE_PATH}/mainMenu.cpp
	${SOURCE_PATH}/menu.cpp
	${SOURCE_PATH}/messagebox.cpp
	${SOURCE_PATH}/music.cpp
	${SOURCE_PATH}/sfx.cpp
	${SOURCE_PATH}/str_operations.cpp
	${SOURCE_PATH}/system.cpp
	${SOURCE_PATH}/timekeeper.cpp
	${SOURCE_PATH}/conecta4/gameConecta4.cpp
	${SOURCE_PATH}/conecta4/mainConecta4.cpp
	${SOURCE_PATH}/conecta4/messagesConecta4.cpp
	${SOURCE_PATH}/conecta4/tablero.cpp
	${SOURCE_PATH}/snake/gameSnake.cpp
	${SOURCE_PATH}/snake/mainSnake.cpp
	${SOURCE_PATH}/snake/snake.cpp
	${SOURCE_PATH}/snake/snakeMap.cpp
	${SOURCE_PATH}/snake/snakePiece.cpp)
TARGET_LINK_LIBRARIES(SKATRAK-Playground ${LINK_LIBS})
