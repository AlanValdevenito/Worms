Los protocolos de cada elemento recibido estaran ordenados segun el orden de llegada esperado, tanto para el cliente como para el servidor. Es decir, si se esperan dos uints de 8 bits se detallaria de la siguiente manera:
* se recibe un uint de 8 bits que que representa la entero1
* se recibe un uint de 8 bits que que representa la entero2

# Protocolo Cliente

## Recibir

### Id de cliente
* se recibe un entero sin signo de 8 bits que representa el numero de id con el que sera identificado el cliente en el servidor.

### Ganador
* se recibe un entero sin signo de 8 bits que representa el numero de id del cliente que gano la partida.

### Lista de Partidas
* Se recibe un entero sin signo de 8 bits la cantidad de partidas enviadas ( la longitud de la lista)
* Se recibe una secuencia de enteros sin signo de 8 bits donde cada entero representa el id de la partida

### Vigas
* Se recibe un entero sin signo de 8 bits la cantidad de vigas enviadas ( la longitud de la lista)
##### Viga
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la viga
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la viga
* Se recibe un entero sin signo de 16 bits que representa el ancho de la viga
* Se recibe un entero sin signo de 16 bits que representa alto de la viga 
* Se recibe un entero sin signo de 16 bits que representa angulo de inclinacion de la viga 

### Gusanos
* Se recibe un entero sin signo de 8 bits que representa la cantidad de gusanos que hay en un momento determinado de la partida
* Se recibe un entero sin signo de 8 bits que representa de que gusano es el turno, se indica mediante el id del gusano
* Se recibe un entero sin signo de 8 bits que representa un flag el cual si es 1 indica que luego de los gusanos llegara un proyectil, si es 0 no llegara nada.
##### Gusano
* Se recibe un entero sin signo de 8 bits que representa el id del gusano.
* Se recibe un entero sin signo de 16 bits que representa la posicion en x del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa la vida del gusano en un momento determinado de la partida 
* Se recibe un entero sin signo de 8 bits que representa el color del gusano  
* Se recibe un entero sin signo de 8 bits que representa el estado del gusano en un momento determinado de la partida 
* Se recibe un entero sin signo de 8 bits que representa el arma seleccionada por el gusano, si no selecciona ninguna es 0 
* Se recibe un entero sin signo de 8 bits que representa la direccion del gusano mientras se mueve. 
* Se recibe un entero sin signo de 8 bits que representa el angulo del gusano para simular el vuelo al ser golpeado.


### Proyectiles
* Se recibe un entero sin signo de 8 bits que representa la cantida de proyectiles que se enviaron
* Se recibe un entero sin signo de 8 bits que representa el codigo del proyectil que se envio
##### Codigos
* Granada Verde = 12
* Granada Roja = 20
* Granada Santa = 15
* Granada Banana = 14
* Dinamita =
* Bazooka = 13
* Ataque aereo =
* Fragmento =
* Mortero =

Segun sea el codigo recibido se recibiran:
###### Granadas (Verde, Banana, Santa, Roja)
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la granada en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la granada en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el angulo de la granada.
* Se recibe un entero sin signo de 8 bits que representa si la granada exploto(1) o no(0).
* Se recibe un entero sin signo de 8 bits que representa el tiempo restante para que la granada explote.
###### Dinamita
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la dinamita en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la dinamita en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa si la dinamita exploto(1) o no(0).
* Se recibe un entero sin signo de 8 bits que representa el tiempo restante para que la dinamita explote.
###### Bazooka
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la del proyectil de la bazooka en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la del proyectil de la bazooka en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el angulo del proyectil de la bazooka.
* Se recibe un entero sin signo de 8 bits que representa el direccion del proyectil de la bazooka.
* Se recibe un entero sin signo de 8 bits que 
* Se recibe un entero sin signo de 8 bits que representa si el proyectil de la bazooka exploto(1) o no(0).
###### Mortero
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la del proyectil del mortero en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la del proyectil del mortero en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el angulo del proyectil del mortero.
* Se recibe un entero sin signo de 8 bits que representa el direccion del proyectil del mortero.
* Se recibe un entero sin signo de 8 bits que 
* Se recibe un entero sin signo de 8 bits que representa si el proyectil del mortero exploto(1) o no(0).
###### Ataque aereo
* Se recibe un entero sin signo de 8 bits que representa el id del misil perteneciente al ataque aereo.
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de del misil del ataque aereo en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de del misil del ataque aereo en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa si el misil del ataque aereo exploto(1) o no(0).
###### Fragmento
* Se recibe un entero sin signo de 8 bits que representa el id del fragmento.
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de del fragmento en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de del fragmento en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el el angulo del fragmento.
* Se recibe un entero sin signo de 8 bits que representa si el fragmento exploto(1) o no(0).



###
###
