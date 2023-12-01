# Documentación técnica

El proyecto está compuesto por 3 partes: la interfaz de usuario, el protocolo y el servidor, cada una de las cuales a su vez está compuesta por más partes.

## Diagrama general

<img src='img/diagrama_general.jpg?raw=true'>

## DTOs

Los DTOs son un conjunto de clases de las cuales todas heredan de DTO. Este tipo de objeto es utilizado para contener los distintos mensajes/acciones que envia el cliente hacia el servidor o el servidor hacia el cliente. 

## Interfaz de usuario

### Menu

#### Menu principal

#### Menu de partidas

#### Menu de creacion de partidas

### Partida

Es la encargada de manejar la interfaz grafica de una partida. Se encarga de:

- Manejar los eventos.
- Actualizar.
- Renderizar.

En esta clase podemos encontrar un game loop cuya implementacion se basa en un loop a rate constante con drop de frames.

Se comunica con el servidor usando al cliente como intermediario. Basicamente lo que hace es pushear en una de las queue del cliente _(send_queue)_ pedidos que este le envia al servidor y popea de la otra queue del cliente _(recv_queue)_ lo que el servidor le mande.

#### Worm

Es la encargada de guardar el estado de un Worm y utilizar dicho estado para renderizar. Actualiza su estado con aquello que el servidor le envie a la clase Partida. Por ejemplo:

- Posicion.
- Vida.
- Direccion.
- Estado.

Mediante la actualizacion del estado se le cambia la animacion a renderizar. Los estados posibles son:

- Quieto.
- Moviendose.
- Cayendo.
- Saltando adelante.
- Saltando atras.
- Equipando arma.
- Golpeado.
- Muerto.

#### Arma

#### Camara

## Protocolo

## Servidor

El servidor se encarga de iniciar un hilo aceptador que aceptara a los clientes. Esperando una 'q' como instruccion de cierre forzoso de todos los clientes, partidas, aceptador y del mismo.

### Aceptador

Se encarga de aceptar a todos los clientes mientras el servidor este abierto. Cada vez que recibe un nuevo cliente lo envia al lobby del juego.

### Lobby

Es el encargado de recibir los nuevos clientes e instanciarlos con su propia cola, de modo tal de poder entablar una conversacion. Luego le envia al cliente las partidas disponibles para unirse, esperando una respuesta del cliente. Puede recibir el id de la partida seleccionada por el cliente o puede recibir una peticion de creacion de nueva partida. En ambos casos el cliente es agregado a la partida y luego se pierde referencia a el.
Cada nueva partida creada es agregada a una lista, y cada vez que llega un nuevo cliente se eliminan las partidas que ya han terminado.
En caso de que el servidor sea cerrado antes que se haya unido a una partida se lo libera.
Una vez que el servidor cierra el lobby se encarga de liberar a todas las partidas creadas.

### Partida

Es la encargada de recibir a los clientes, enviarle una referencia de su cola de salida al broadcaster, cambiarle su cola de entrada por una cola comun a todos los clientes de la partida y añadirlos a una lista.
Una vez que la cantidad de clientes en partida es la indicada al momento de la creacion, la partida comienza, es decir se le envian los mapas a los clientes, los gusanos en sus posiciones iniciales y inicial el game loop.
Cuando la partida termina, se liberan los clientes y la referencia a sus colas.
Cuando el servidor cierra se fuerza el mismo cierre con la diferencia que ahora se debe detener el game loop.

### Game

Es la clase encargada de manejar la lógica del juego, gestionar los turnos de los jugadores, determinar si la partida finalizó, etc. `Game` recibe eventos de los jugadores a través de una Queue, los cuales ejecuta y posteriormente actualiza el estado del juego para enviárselo a los clientes para que puedan renderizarlo. Utiliza las siguientes clases

#### Player

Esta clase contiene la información de un jugador como por ejemplo su id, si está vivo o no, una lista con los gusanos que controla, etc. Cuando un `Player` es elegido como el siguiente en el ciclo de turnos, el `Player` debe determinar cuál es el siguiente gusano a ser elegido.

#### World

La clase `World` se encarga de simular la física de las entidades del juego como los gusanos y los proyectiles, para lo cual utiliza una instancia de `b2World` de Box2D. Se encarga de instanciar los gusanos y las vigas, las cuales varían según el escenario seleccionado. Dentro del game loop se llama al método `step()` de `World`, el cual avanza el mundo un lapso de tiempo determinado.

##### Worm

La clase `Worm` representa un gusano dentro del juego. Posee métodos para moverse, saltar, conocer su posición, estado, vida, etc. Posee una referencia a un cuerpo de Box2D que se usa para poder simular los movimientos.

##### Proyectiles

La clase `Game` tiene, por cada proyectil existente en el juego, una clase que representa cada uno de ellos. Estos proyectiles están modelados con Box2D. Los proyectiles tienen 2 formas de explotar:

- Por cuenta regresiva: incluye a las clases `GreenGrenade`, `Banana`, `RedGrenade`, `HolyGrenade`, `Dynamite`.
- Por colisión: incluye a las clases `BazookaRocket`, `MorteroRocket`, `AirStrikeRocket`, `RedGrenadeFragment`.

Para que un proyectil explote se debe llamar al método `explode()`, el cual se encarga de aplicarles a los gusanos una fuerza y un daño inversamente proporcional a la distancia entre los gusanos y el epicentro de la explosión.

##### Beam

La clase Beam representa una viga dentro del juego. No tiene comportamiento pero su constructor provee una interfaz para poder crear una viga fácilmente, permitiendo elegir la posición, el tipo de viga y la inclinación.
