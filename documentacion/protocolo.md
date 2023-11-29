> Los protocolos de cada elemento recibido estaran ordenados segun el orden de llegada esperado, tanto para el cliente como para el servidor. Es decir, si se esperan dos uints de 8 bits se detallaria de la siguiente manera:
>* se recibe un uint de 8 bits que que representa la entero1.
>* se recibe un uint de 8 bits que que representa la entero2.

# Protocolo Cliente

## Recibir

### Id de cliente
* Se recibe un entero sin signo de 8 bits que representa el numero de **id** con el que sera identificado el cliente en el servidor.

### Ganador
* Se recibe un entero sin signo de 8 bits que representa el numero de **id** del cliente que gano la partida.

### Lista de Partidas
* Se recibe un entero sin signo de 8 bits la **cantidad de partidas** enviadas ( la longitud de la lista).
* Se recibe una secuencia de enteros sin signo de 8 bits donde cada entero representa el **id** de la partida.

### Vigas
* Se recibe un entero sin signo de 8 bits la **cantidad de vigas** enviadas ( la longitud de la lista).
##### Viga
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de la viga.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de la viga.
* Se recibe un entero sin signo de 16 bits que representa el **ancho** de la viga.
* Se recibe un entero sin signo de 16 bits que representa **alto** de la viga.
* Se recibe un entero sin signo de 16 bits que representa **angulo** de inclinacion de la viga.

### Gusanos
* Se recibe un entero sin signo de 8 bits que representa la **cantidad de gusanos** que hay en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa de que gusano es el **turno**, se indica mediante el id del gusano.
* Se recibe un entero sin signo de 8 bits que representa un **flag** el cual si es 1 indica que luego de los gusanos llegara un proyectil, si es 0 no llegara nada.

##### Gusano
* Se recibe un entero sin signo de 8 bits que representa el **id** del gusano.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** del gusano en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa la **vida** del gusano en un momento determinado de la partida 
* Se recibe un entero sin signo de 8 bits que representa el **color** del gusano.  
* Se recibe un entero sin signo de 8 bits que representa el **estado** del gusano en un momento determinado de la partida. 
* Se recibe un entero sin signo de 8 bits que representa el **arma** seleccionada por el gusano, si no selecciona ninguna es 0 
* Se recibe un entero sin signo de 8 bits que representa la **direccion** del gusano mientras se mueve. 
* Se recibe un entero sin signo de 8 bits que representa el **angulo** del gusano para simular el vuelo al ser golpeado.


### Proyectiles
* Se recibe un entero sin signo de 8 bits que representa la **cantida de proyectiles** que se enviaron.
* Se recibe un entero sin signo de 8 bits que representa el **codigo** del proyectil que se envio.
##### Codigos
> Bazooka = **16**

> Granada Verde = **17**

> Granada Banana = **18**

> Granada Santa = **19**

> Granada Roja = **20**

> Dinamita = **21**

> Ataque aereo = **22**

> Mortero = **23**

> Fragmento = **24**

>**Segun sea el codigo recibido se recibiran:**

###### Granadas (Verde, Banana, Santa, Roja)
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de la granada en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de la granada en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** de la granada.
* Se recibe un entero sin signo de 8 bits que representa si la granada **exploto(1)** o no **(0)**.
* Se recibe un entero sin signo de 8 bits que representa el **tiempo restante** para que la granada explote.

###### Dinamita
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de la dinamita en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de la dinamita en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa si la dinamita **exploto(1)** o no **(0)**.
* Se recibe un entero sin signo de 8 bits que representa el **tiempo restante** para que la dinamita explote.

###### Bazooka
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de la del proyectil de la bazooka en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de la del proyectil de la bazooka en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** del proyectil de la bazooka.
* Se recibe un entero sin signo de 8 bits que representa el **direccion** del proyectil de la bazooka.
* Se recibe un entero sin signo de 8 bits que representa si el proyectil de la bazooka **exploto(1)** o no **(0)**.
###### Mortero
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de la del proyectil del mortero en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de la del proyectil del mortero en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** del proyectil del mortero.
* Se recibe un entero sin signo de 8 bits que representa el **direccion** del proyectil del mortero.
* Se recibe un entero sin signo de 8 bits que representa si el proyectil del mortero **exploto(1)** o no **(0)**.
###### Ataque aereo
* Se recibe un entero sin signo de 8 bits que representa el **id** del misil perteneciente al ataque aereo.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de del misil del ataque aereo en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de del misil del ataque aereo en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa si el misil del ataque aereo **exploto(1)** o no **(0)**.
###### Fragmento
* Se recibe un entero sin signo de 8 bits que representa el **id** del fragmento.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** de del fragmento en un momento determinado de la partida.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** de del fragmento en un momento determinado de la partida.
* Se recibe un entero sin signo de 8 bits que representa el el **angulo** del fragmento.
* Se recibe un entero sin signo de 8 bits que representa si el fragmento **exploto(1)** o no **(0)**.

## Enviar

### Movimiento hacia derecha
>codigo = 10
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** del movimiento a derecha. 

### Movimiento hacia izquierda
>codigo = 11
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** del movimiento a izquierda.

### Saltar
>codigo = 12
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** del movimiento a izquierda.
* Se envia un entero sin signo de 8 bits que representa la direccion en la que es efectuada el salto, **salto a derecha = 1**, **salto a izquierda = 0**.

### Nueva Partida
>codigo = 5
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** de la peticion de creacion de una nueva partida. 
* Se envia un entero sin signo de 8 bits que representa la cantidad de jugadores requerida para la partida.

### Partida seleccionada
>codigo = 6
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** la seleccion de una partida. 
* Se envia un entero sin signo de 8 bits que representa la partida disponible seleccionada. 

### Finalizar Partida
>codigo = 4
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa la **finalizacion** de la partida de el cliente. 

### Ataque con Bate de beisbol
>codigo = 14
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo**  el ataque con el bate. 
* Se envia un entero sin signo de 8 bits que representa el angulo con el que se lanzara el disparo con el bate.

### Ataque con Bazooka
>codigo = 16
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** representa el ataque con una bazooka. 
* Se envia un entero sin signo de 8 bits que representa la potencia con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el **angulo** con el que es lanzado el proyectil.

### Ataque con Mortero
>codigo = 23
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** representa el ataque con una bazooka. 
* Se envia un entero sin signo de 8 bits que representa la potencia con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el **angulo** con el que es lanzado el proyectil.

### Ataque con Granadas (verde, banana, santa, roja)
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo**  lanzamiento de el tipo de granada. 
> Dependiendo el tipo de granada el codigo sera:

> **Granada Verde** => codigo = **17**

> **Granada Banana** => codigo = **18**

> **Granada Santa** => codigo = **19**

> **Granada Roja** => codigo = **20**

* Se envia un entero sin signo de 8 bits que representa la **potencia** con la que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el **angulo** con el que es lanzado el proyectil.
* Se envia un entero sin signo de 8 bits que representa el **tiempo** seleccionado que debe transcurrir hasta que explote la granada.


### Ataque con dinamita
>codigo = 21
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo** de ataque con una dinamita. 
* Se envia un entero sin signo de 8 bits que representa el **tiempo** seleccionado que debe transcurrir hasta que explote la dinamita.

### Teletransportacion
>codigo = 15
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo**  de la teletransportacion. 
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** a la que se debe teletransportar el gusano.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** a la que se debe teletransportar el gusano.

### Ataque Aereo
>codigo = 22
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo**  de el ataque aereo.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de donde debe caer el ataque aereo.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de donde debe caer el ataque aereo.

### Equipar arma
>codigo = 13
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente que esta enviando el mensaje.
* Se envia un entero sin signo de 8 bits que representa el **codigo**  de que el gusano se va a equipar un arma. 
* Se envia un entero sin signo de 8 bits que representa el **arma** a equipar.
> Dependiendo el numero, se equipara un arma u otra:

> **0** => Bazooka

> **1** => Mortero

> **2** => Granada Verde

> **3** => Granada Roja

> **4** => Granada Banana

> **5** => Granada Santa

> **6** => Dinamita

> **7** => Bate de Beisbol

> **8** => Ataque Aereo

> **9** => Teletransportacion



# Protocolo Servidor

## Recibir
* Se recibe un entero sin signo de 8 bit que representa el **id** del cliente que esta enviando el mensaje
* Se recibe un entero de 8 bits sin signo que representa el **codigo** de la accion requerida por el usuario
> Segun el numero indicado en el codigo se recibiran distintos parametros. A continuacion se detallara el codigo con el cual se interpretara cada accion y cuales son los siguientes elementos a recibir.


### Partida seleccionada
> Codigo **6** 
* Se recibe un entero sin signo de 8 bits que representa el **id** de la partida seleccionada.

### Mover a derecha
> Codigo **10** 
> No es necesario recibir mas informacion


### Mover a izquierda
> Codigo **11** 
> No es necesario recibir mas informacion


### Ataque con bate de beisbol
> Codigo **14** 
* Se recibe un entero sin signo de 8 bits que representa el **angulo** con el que se efectuara el golpe.


### Finalizar partida
> Codigo **4** 
> No es necesario recibir mas informacion

### Salto
> Codigo **12** 
* Se recibe un entero sin signo de 8 bits que representa la **direccion** con la que se efectuara el salto.


### Nueva Partida
> Codigo **5** 
* Se recibe un entero sin signo de 8 bits que representa la **cantidad de jugadores** que debe tener la nueva partida.
* Se recibe un entero sin digno de 8 bits que representa el **mapa** seleccionado para la partida.

### Ataque con Bazooka
> Codigo **16** 
* Se recibe un entero sin signo de 8 bits que representa la **potencia** con la que se efectuara el lanzamiento del proyectil de la bazooka.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** con el que se efectuara el lanzamiento del proyectil de la bazooka.


### Ataque con Granadas (Verde, Banana, Santa, Roja)
> Codigo **17** Verde
> Codigo **18** Banana
> Codigo **19** Santa
> Codigo **20** Roja
* Se recibe un entero sin signo de 8 bits que representa la **potencia** con la que se efectuara el lanzamiento de la granada.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** con el que se efectuara el lanzamiento de la granada.
* Se recibe un entero sin signo de 8 bits que representa el **tiempo** que debe transcurrir hasta explotar la granada.


### Ataque con Dinamita
> Codigo **21** 
* Se recibe un entero sin signo de 8 bits que representa el **tiempo** que debe transcurrir hasta explotar la dinamita.


### Ataque con Mortero
> Codigo **23** 
* Se recibe un entero sin signo de 8 bits que representa la **potencia** con la que se efectuara el lanzamiento del proyectil del mortero.
* Se recibe un entero sin signo de 8 bits que representa el **angulo** con el que se efectuara el lanzamiento del proyectil del mortero.


### Ataque Aereo
> Codigo **22** 
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** a donde desea lanzar el ataque.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** a donde desea lanzar el ataque.


### Teletrasportar
> Codigo **15** 
* Se recibe un entero sin signo de 16 bits que representa la posicion en **x** a donde desea teletransportarse.
* Se recibe un entero sin signo de 16 bits que representa la posicion en **y** a donde desea teletransportarse.


### Equipar Arma
> Codigo **13**
* Se recibe un entero sin signo de 8 bits que representa el **arma** que solicita ser equipada por el cliente.


## Enviar

### ID
> Codigo **1**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.
* Se envia un entero sin signo de 8 bits que representa el id del cliente con el cual se lo identifica.

### Vigas
> Codigo **7**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.
* Se envia un entero de sin signo de 8 bits que representa la cantidad de vigas que se envian.
#### Viga
* Se envia un entero sin signo de 8 bits que representa el ancho de la viga.
* Se envia un entero sin signo de 8 bits que representa el alto de la viga.
* Se envia un entero sin signo de 8 bits que representa el angulo de inclinacion que tiene la viga.


### Gusanos
> Codigo **9**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar
* Se envia un entero sin signo de 8 bits que representa la cantidad de gusanos que hay en la partida
* Se envia un entero sin signo de 8 bits que representa el id del gusano del cual es el **turno actualmente**.
* Se envia un entero sin signo de 8 bits que representa un flag que indica si hay un proyectil **flag=1** en partida o si no hay **flag=0**. 
#### Gusano
* Se envia un entero sin signo de 8 bits que representa el id del gusano.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** del gusano en un momento determinado de la partida.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** del gusano en un momento determinado de la partida.
* Se envia un entero sin signo de 8 bits que representa el porcentaje de vida del gusano en un determinado momento de la partida.
* Se envia un entero sin signo de 8 bits que representa el color de equipo al cual pertenece el gusano.
* Se envia un entero sin signo de 8 bits que representa el estado actual del gusano.
* Se envia un entero sin signo de 8 bits que representa arma que tiene seleccionada el gusano.
* Se envia un entero sin signo de 8 bits que representa la direccion del gusano para saber para que lado "mira".
* Se envia un entero sin signo de 8 bits que representa el angulo del gusano para simular el vuelo ante un impacto.


### Partidas Disponibles
> Codigo **6**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.
* Se envia un entero sin signo de 8 bits que representa la **cantidad de partidas** disponibles enviadas.
* Se envia un entero sin signo de 8 bits que representa el **id** de la partida disponible.
> Por cada partida disponible se repite el ultimo paso. Es decir que si hay 2 partidas disponibles el flujo seria:
> 1. Enviar codigo de elemento
> 2. Enviar cantidad de partidas
> 3. Enviar id de partida 1
> 4. Enviar id de partida 2

### Inicio de Partida
> Codigo **2**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.


### Finalizacion de Partida
> Codigo **4**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.


### Ganador
> Codigo **3**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del elemento a enviar.
* Se envia un entero sin signo de 8 bits que representa el **id** del cliente ganador.


### Proyectiles
> Codigo **25**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** de enviado de una serie de proyectiles.
* Se envia un entero sin signo de 8 bits que representa la **cantidad de proyectiles** a enviar.
> A continuacion se detallan, con cada tipo de proyectil, el codigo correspondiente

#### Granadas (Verde, Banana, Santa, Roja)
> Codigo **17** Verde 
> Codigo **18** Banana
> Codigo **19** Santa
> Codigo **20** Roja

* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de la granada en un determinado momento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de la granada en un determinado momento.
* Se envia un entero sin signo de 8 bits que representa el angulo de la granada para simular el movimiento durante la trayectoria.
* Se envia un entero sin signo de 8 bits que repesenta si la granada exploto **exploto=1** o si no exploto **exploto = 0**.
* Se envia un entero sin signo de 8 bits que representa el **tiempo** restante para que la granada explote.

#### Bazooka
> Codigo **16**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de el proyectil de bazooka en un determinado momento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de el proyectil de bazooka en un determinado momento.
* Se envia un entero sin signo de 8 bits que representa el **angulo** del proyectil de bazooka para simular el movimiento durante la trayectoria.
* Se envia un entero sin signo de 8 bits que representa la **direccion** del proyectil de bazooka.
* Se envia un entero sin signo de 8 bits que repesenta si el proyectil de bazooka exploto **exploto=1** o si no exploto **exploto = 0**.

#### Dinamita
> Codigo **21**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 8 bits que repesenta si la dinamita exploto **exploto=1** o si no exploto **exploto = 0**.
* Se envia un entero sin signo de 8 bits que representa el **tiempo** restante para que la dinamita explote.

#### Mortero
> Codigo **23**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de el proyectil de mortero en un determinado momento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de el proyectil de mortero en un determinado momento.
* Se envia un entero sin signo de 8 bits que representa el **angulo** del proyectil de mortero para simular el movimiento durante la trayectoria.
* Se envia un entero sin signo de 8 bits que representa la **direccion** del proyectil de mortero.
* Se envia un entero sin signo de 8 bits que repesenta si el proyectil de mortero exploto **exploto=1** o si no exploto **exploto = 0**.



#### Ataque Aereo
> Codigo **22**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 8 bits que representa el **id** del misil del ataque aereo.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de misil en un determinado momento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de misil en un determinado momento.
* Se envia un entero sin signo de 8 bits que repesenta si el misil exploto **exploto=1** o si no exploto **exploto = 0**.

#### Fragmento
> Codigo **24**  
* Se envia un entero sin signo de 8 bits que representa el **codigo** del proyectil que esta siendo enviado.
* Se envia un entero sin signo de 8 bits que representa el **id** del fragmento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **x** de el fragmento en un determinado momento.
* Se envia un entero sin signo de 16 bits que representa la posicion en **y** de el fragmento en un determinado momento.
* Se envia un entero sin signo de 8 bits que representa el **angulo** del fragmento para simular el movimiento durante la trayectoria.
* Se envia un entero sin signo de 8 bits que repesenta si el fragmento exploto **exploto=1** o si no exploto **exploto = 0**.
