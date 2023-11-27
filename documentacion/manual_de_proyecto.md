# Organizacion semanal

Semana a semana nos fuimos organizando con el objetivo de ir llevando al dia los objetivos
propuestos por la catedra tal cual los marcaba en la documentacion.

### Semana 1
* Pruebas de concepto de SDL y Box2D
### Semana 2
* Inicio del armado del protocolo de comunicacion.
* Armado de la estructura cliente-servidor, colas de entrada y salida, hilos de enviado y recepcion.
* Implementación de la estructura cliente-servidor para 1 partida.
* Implementacion de envios, colisiones y renderizacion de vigas.
* Implementacion de envios, colisiones y renderizacion de un gusano o mas.
* Implementacion de envios, colisiones y renderizacion de movimiento de un gusano o mas.
### Semana 3
* Implementacion de multiples partidas.
* Conectar multiples clientes a una misma partida.
* Manejo de turnos de gusanos.
* Implementacion basica del menu de partidas.
* Implementacion de golpe de gusano con bate.
* Creacion de equipos por cliente.
* Implementacion de mover gusano en vigas con inclinacion.
### Semana 4
* Implementacion del salto de los gusanos.
* Ejecucion de mas de una partida en simultaneo.
* Implementacion de la camara en la vista.
* Implementacion de temporizador.
* Implementacion ataque con granada Verde.
* Implementacion ataque con granada Santa.
* Implementacion ataque con granada Banana.
* Implementacion ataque con Dinamita.
* Implementacion ataque con Bazooka.
* Implementacion de test automatizados para la comunicacion.
* Cambio de turno con lapso de tiempo luego de ataque.
### Semana 5
* Implementacion de la herramienta teletransportacion.
* Implementacion de salto hacia atras.
* Refactorizacion de comunicacion de enviado de Proyectiles ( enviado de multiples proyectiles).
* Implementacion de Ataque aereo.
* Implementacion de Mortero.
* Implementacion de Granada Roja.
* Arreglo de vista de animacion en ambos clientes al ejecutar ataque.
* Boceto MANUAL DE USUARIO.
* Creacion de instalador.
### Semana 6
* Correcciones en el Ataque Aereo.
* Implementacion de fragmentos de Granada Roja y Mortero.
* Cambio de renderizacion del agua.
* Agregado de pantallas de victoria y derrota.
* Implementacion completa de Menu de partidas.
* Renderizacion de salto para atras. 
* Implementacion de muerte al caer al vacio.
* Implementacion de vista de temporizador de las granadas.
* Boceto Manual de Proyecto.
* Diagramas de estructura del proyecto.
* Implementacion de visualizacion de vida total por equipo.
### Semana 7


# Reparticion de tareas
El proyecto fue dividido en tres categorias: 
* Vista
* Logica del juego y fisicas
* Comunicacion y ... 

El alumno responsable en llevar a cabo la logica del juego y parte fisica fue Mateo Julian Rico. En particular
se encargo de:

* Implementar la logica de interpretacion de acciones del juego del lado del servidor.
* Ejecutar las fisicas de cada accion del juego segun corresponda.
* Utilizacion de Box2D para la parte fisica.

El alumno responsable en llevar a cabo la logica de la Comunicacion y .... fue Federico Solari Vazquez. En
particular se encargo de:

* Implementar los protocolos del comunicacion del servidor.
* Implementar los protocolos del comunicacion del cliente.
* Implementar la logica de armado de multiples partidas.
* Implementar la estructura de el cliente y el servidor (colas, threads...).
* Implementar los cierres ordenados al terminar la partida o cuando hay un error.
* Hacer diagrama de estructura del proyecto.
* Implementacion de test automaticos de la comunicacion haciendo mocks de socket.

El alumno responsable en llevar a cabo la logica de la Vista fue Alan Valdevinito. En
particular se encargo de:

* Implementar la vista del juego mediante SDL
* Implementar el menu de seleccion de partidas mediante SDL y QT


# Herramientas utilizadas
* Google Test
* Box2D
* SDL
* QT
* Visual studio code
* Live Share (en vscode)
## Documentacion requerida para utilizacion de las herramientas
* Google test: https://github.com/google/googletest
* Box2D: https://box2d.org/documentation/ https://www.iforce2d.net/b2dtut/
* SLD:
* QT:


# Documentacion adicional
* Link a tablero de tickets: https://github.com/users/AlanValdevenito/projects/1

# Informacion Adicional

### Cuales fueron los puntos más problemáticos? 
* Cambio de enviado de un proyectil a multiples proyectiles.
* Cierres ordenados de partidas.
* Ensamble de google test con el proyecto

### Pudieron llegar con todo?
* to be contiue...

### Hay errores conocidos? 
* Utilizacion de sleep para enviado y recepcion correcta de mensajes de cierre. 

### Si volvieran hacer el proyecto, que cambiarían (a nivel código o a nivel organizacional).
* No cambiariamos nada, creemos que nos origanizamos bien, se puede ver reflejado en el tablero relizida en GitHub.
* Hizo un buen slicing de los featureas a tratar de modo tal que trabajabamos de a un feature y este era relativamente corto.