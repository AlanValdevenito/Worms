> Los protocolos de cada elemento recibido estaran ordenados segun el orden de llegada esperado, tanto para el cliente como para el servidor. Es decir, si se esperan dos uints de 8 bits se detallaria de la siguiente manera:
>* se recibe un uint de 8 bits que que representa la entero1.
>* se recibe un uint de 8 bits que que representa la entero2.

# Protocolo Cliente

## Recibir

### Id de cliente
* se recibe un entero sin signo de 8 bits que representa el numero de id con el que sera identificado el cliente en el servidor.

### Ganador
* se recibe un entero sin signo de 8 bits que representa el numero de id del cliente que gano la partida.

### Lista de Partidas
* Se recibe un entero sin signo de 8 bits la cantidad de partidas enviadas ( la longitud de la lista).
* Se recibe una secuencia de enteros sin signo de 8 bits donde cada entero representa el id de la partida.

### Vigas
* Se recibe un entero sin signo de 8 bits la cantidad de vigas enviadas ( la longitud de la lista).
##### Viga
* Se recibe un entero sin signo de 16 bits que representa la posicion en x de la viga.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y de la viga.
* Se recibe un entero sin signo de 16 bits que representa el ancho de la viga.
* Se recibe un entero sin signo de 16 bits que representa alto de la viga.
* Se recibe un entero sin signo de 16 bits que representa angulo de inclinacion de la viga.

### Gusanos
* Se recibe un entero sin signo de 8 bits que representa la cantidad de gusanos que hay en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa de que gusano es el turno, se indica mediante el id del gusano.
* Se recibe un entero sin signo de 8 bits que representa un flag el cual si es 1 indica que luego de los gusanos llegara un proyectil, si es 0 no llegara nada.

##### Gusano
* Se recibe un entero sin signo de 8 bits que representa el id del gusano.
* Se recibe un entero sin signo de 16 bits que representa la posicion en x del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en y del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa la vida del gusano en un momento determinado de la partida 
* Se recibe un entero sin signo de 8 bits que representa el color del gusano.  
* Se recibe un entero sin signo de 8 bits que representa el estado del gusano en un momento determinado de la partida. 
* Se recibe un entero sin signo de 8 bits que representa el arma seleccionada por el gusano, si no selecciona ninguna es 0 
* Se recibe un entero sin signo de 8 bits que representa la direccion del gusano mientras se mueve. 
* Se recibe un entero sin signo de 8 bits que representa el angulo del gusano para simular el vuelo al ser golpeado.


### Proyectiles
* Se recibe un entero sin signo de 8 bits que representa la cantida de proyectiles que se enviaron.
* Se recibe un entero sin signo de 8 bits que representa el codigo del proyectil que se envio.
##### Codigos
>* Bazooka = 16
>* Granada Verde = 17
>* Granada Banana = 18
>* Granada Santa = 19
>* Granada Roja = 20
>* Dinamita = 21
>* Ataque aereo = 22
>* Mortero = 23
>* Fragmento = 24

>**Segun sea el codigo recibido se recibiran:**

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

## Enviar

### Movimiento hacia derecha
>codigo = 10
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo del movimiento a derecha. 

### Movimiento hacia izquierda
>codigo = 11
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo del movimiento a izquierda.

### Saltar
>codigo = 12
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo del movimiento a izquierda.
* Se envia un entero sin signo de 8 bits que representa la direccion en la que es efectuada el salto, **salto a derecha = 1**, **salto a izquierda = 0**.

### Nueva Partida
>codigo = 5
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo de la peticion de creacion de una nueva partida. 
* Se envia un entero sin signo de 8 bits que representa la cantidad de jugadores requerida para la partida.

### Partida seleccionada
>codigo = 6
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo la seleccion de una partida. 
* Se envia un entero sin signo de 8 bits que representa la partida disponible seleccionada. 

### Finalizar Partida
>codigo = 4
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa la finalizacion de la partida de el cliente. 

### Ataque con Bate de beisball
>codigo = 14
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo  el ataque con el bate. 
* Se envia un entero sin signo de 8 bits que representa el angulo con el que se lanzara el disparo con el bate.

### Ataque con Bazooka
>codigo = 16
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo representa el ataque con una bazooka. 
* Se envia un entero sin signo de 8 bits que representa la potencia con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el angulo con el que es lanzado el proyectil.

### Ataque con Mortero
>codigo = 23
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo representa el ataque con una bazooka. 
* Se envia un entero sin signo de 8 bits que representa la potencia con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el angulo con el que es lanzado el proyectil.

### Ataque con Granadas (verde, banana, santa, roja)
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo  lanzamiento de el tipo de granada. 
> Dependiendo el tipo de granada el codigo sera:
> Granada Verde ------> codigo = 17
> Granada Banana ------> codigo = 18
> Granada Santa ------> codigo = 19
> Granada Roja ------> codigo = 20
* Se envia un entero sin signo de 8 bits que representa la potencia con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el angulo con el que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el tiempo seleccionado que debe transcurrir hasta que explote la granada.


### Ataque con dinamita
>codigo = 21
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo de ataque con una dinamita. 
* Se envia un entero sin signo de 8 bits que representa el tiempo seleccionado que debe transcurrir hasta que explote la dinamita.

### Teletransportacion
>codigo = 15
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo  de la teletransportacion. 
* Se envia un entero sin signo de 16 bits que representa la posicion en x a la que se debe teletransportar el gusano.
* Se envia un entero sin signo de 16 bits que representa la posicion en y a la que se debe teletransportar el gusano.

### Ataque Aereo
>codigo = 22
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo  de el ataque aereo.
* Se envia un entero sin signo de 16 bits que representa la posicion en x de donde debe caer el ataque aereo.
* Se envia un entero sin signo de 16 bits que representa la posicion en y de donde debe caer el ataque aereo.

### Equipar arma
>codigo = 13
* Se envia un entero sin signo de 8 bits que representa el id del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el codigo  de que el gusano se va a equipar un arma. 
* Se envia un entero sin signo de 8 bits que representa el arma a equipar.
> Dependiendo el numero, se equipara un arma u otra:

> 0 => Bazooka

> 1 => Mortero

> 2 => Granada Verde

> 3 => Granada Roja

> 4 => Granada Banana

> 5 => Granada Santa

> 6 => Dinamita

> 7 => Bate de Beisball

> 8 => Ataque Aereo

> 9 => Teletransportacion
