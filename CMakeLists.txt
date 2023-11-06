# Establecemos la version minima de CMake para compilar el proyecto.
# Se requiere CMake version 3.8 o superior, y si la version no coincide, se generara un error fatal.
cmake_minimum_required(VERSION 3.8)

# Establece el nombre del proyecto. 
# En este caso, el proyecto se llama "Worms" y se especifica que se utilizara el lenguaje C++ para compilarlo.
project(Worms LANGUAGES CXX)

# Define opciones que se pueden configurar al generar el proyecto con CMake.
option(math "Usar funciones de math.h" ON) # Define una opción llamada "math" que se establece en "ON" de forma predeterminada. Esto se utilizará más adelante para determinar si se deben usar funciones de math.h.
option(threads "Usar threads" ON) # Define una opción llamada "threads" que se establece en "ON" de forma predeterminada. Esto se utilizará para determinar si se deben usar threads.
option(static "Compilar estáticamente" OFF) # Define una opción llamada "static" que se establece en "OFF" de forma predeterminada. Esto se utilizará para determinar si se debe compilar estáticamente.
option(wrapsocks "Simular pérdida de bytes en sockets" ON) # Define una opción llamada "wrapsocks" que se establece en "ON" de forma predeterminada. Esto se utilizará para simular pérdida de bytes en sockets.

# Establece variables en el proyecto.
# Establecen las versiones de los estándares de C y C++ que se utilizarán.
set(CSTD c17)
set(CXXSTD c++17)

if (math)
    set(LINK_LIBS ${LINK_LIBS} m)
endif()

if (threads)
    set(LINK_LIBS ${LINK_LIBS} pthread)
endif()

if (static)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

if (wrapsocks)
    add_definitions(-Dwrapsocks=1)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--wrap=send -Wl,--wrap=recv")
endif()

# Establecen las banderas del compilador para el lenguaje C y C++ respectivamente. 
# Esto incluye opciones de advertencia, depuración y otros ajustes.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")


# Agrega directorios a la lista de directorios en los que el compilador buscará archivos de encabezado. 
include_directories(common/Dtos)
include_directories(common)
include_directories(client)
include_directories(client/vista)
include_directories(client/vista/data)
include_directories(server)

# ...
add_subdirectory(gtest)

# Se busca y se incluye la biblioteca SDL2pp.
# ESta biblioteca es un conjunto de encabezados C++ para SDL2 que facilita su uso.
# La opcion "REQUIRED" indica que es necesario encontrar la biblioteca; de lo contrario, se generara un error si no se encuentra.
find_package(Qt5Widgets REQUIRED)
find_package(SDL2pp REQUIRED)
find_package(box2d REQUIRED)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS client/vista/mainwindow.ui) # Generamos encabezados de UI a partir del archivo de diseño de la interfaz grafica (.ui).

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)

# Agregamos una definicion de preprocesador al proyecto. DEfinimos la macro llamada "DATA_PATH" que apunta
# al directorio "data" en el directorio fuente del proyecto.
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/client/vista/data")
# Incluimos los directorios de encabezado necesarios.
# EN este caso, incluimos los directorios de encabezado de SDL2pp, que se definen en "SDL2PP_INCLUDE_DIRS"
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR}) # Para Qt

# Se utilizan para buscar archivos y almacenarlos en variables. 
# Se buscan archivos con extensiones .cpp y .h en los directorios common, client y server, y se almacenan en las variables correspondientes.
file(GLOB COMMON_SOURCES common/*.cpp *.$(extension))
file(GLOB COMMON_HEADERS common/*.h)

file(GLOB DTO_SOURCES common/Dtos/*.cpp *.$(extension))
file(GLOB DTO_HEADERS common/Dtos/*.h)

file(GLOB CLIENT_SOURCES client/*.cpp *.$(extension))
file(GLOB CLIENT_HEADERS client/*.h)
file(GLOB CLIENT_SOURCES_VISTA client/vista/*.cpp *.$(extension))
file(GLOB CLIENT_HEADERS_VISTA client/vista/*.h)

file(GLOB SERVER_SOURCES server/*.cpp *.$(extension))
file(GLOB SERVER_HEADERS server/*.h)

# Define los ejecutables que se compilarán. 
# Se utilizan las variables que contienen las listas de archivos .cpp y .h en los directorios common, client y server para definir los objetivos.
add_executable(client ${CLIENT_SOURCES_VISTA} ${CLIENT_HEADERS_VISTA} ${DTO_HEADERS} ${COMMON_HEADERS} ${CLIENT_HEADERS} ${DTO_SOURCES} ${COMMON_SOURCES} ${CLIENT_SOURCES} ${UIS_HEADERS} )
add_executable(server ${DTO_HEADERS} ${COMMON_HEADERS} ${SERVER_HEADERS} ${DTO_SOURCES} ${COMMON_SOURCES} ${SERVER_SOURCES})

# Enlaza las bibliotecas a los ejecutables. En este caso, se enlazan las bibliotecas definidas en LINK_LIBS.
target_link_libraries(client ${LINK_LIBS} SDL2pp::SDL2pp Qt5::Widgets Qt5::Core)
target_link_libraries(server ${LINK_LIBS} box2d)
