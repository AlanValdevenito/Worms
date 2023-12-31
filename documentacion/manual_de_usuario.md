# Manual de usuario

## 1. Instalacion

### 1.1 Clonacion del repositorio

A continuacion se listan los pasos a seguir:
1. Abrir la terminal.
2. Utilizar el siguiente comando: 

```
$ git clone https://github.com/AlanValdevenito/Worms
```

Nota: Para compilar y ejecutar el proyecto se debera usar la rama main.

### 1.2 Instalacion y compilacion

Este proceso consiste en instalar las dependencias necesarias y en la compilacion del proyecto. Esto se
encuentra automatizado mediante un script cuyo uso se detalla a continuacion:
1. Abrir una terminal en el directorio principal del proyecto.
2. Se debera cargar el script: 

```
$ sh install.sh
```

Una vez en ejecucion, el instalador mostrara una serie de mensajes cuyo orden se lista a continuacion:
1. Instalando dependencias.
2. Instalando Worms

## 2 Configuracion

### 2.1 Cambiar la configuracion del juego

Dentro del archivo de configuraciones se podran cambiar los siguientes atributos del juego:

• Cantidad de gusanos.

• Worms:
- Vida.
- Velocidad.
- Vida extra.

• Duracion del turno.

• Segundos adicionales luego de hacer uso de un arma o herramienta.

• Armas: 
- Daño.
- Radio de explosion.
- Municion.

Para cambiar el valor de estos atributos simplemente se debe entrar al archivo de configuraciones, buscar
el atributo que se desee cambiar y cambiarlo.

## 3 Uso del servidor

### 3.1 Ejecucion

En una terminal, dentro del directorio build, ingresar el siguiente comando: 

```
$ ./server 8080
```

### 3.2 Finalizacion

En la misma terminal donde se ejecuto el servidor se debera ingresar la letra ‘q’.

## 4 Uso del cliente

### 4.1 Ejecucion

En una terminal, dentro del directorio build y luego de la ejecucion del servidor, ingresar el siguiente comando: 

```
$ ./client 127.0.0.1 8080
```

Al iniciar el juego se abrira la ventana del menu principal donde tendremos dos opciones:
1. Unirse a una partida
2. Crear una nueva partida

### 4.2 Unirse a una partida

Se debe presionar el boton señalado a continuacion:

![Paso 1](img/menu-pasos/paso1.png)

Se abrira la ventana del menu de eleccion de partidas. Se debera clickear la partida deseada:

![Paso 2](img/menu-pasos/paso2.png)

Para unirse a la partida se debe presionar el boton ’Elegir partida’ esperar a que TODOS los jugadores se conecten:

![Paso 3](img/menu-pasos/paso3.png)

### 4.3 Crear una nueva partida

Se debe presionar el boton señalado a continuacion:

![Paso 4](img/menu-pasos/paso4.png)

Se abrira la ventana del menu de creacion de partidas y se deberan completar los campos:

![Paso 5](img/menu-pasos/paso-5.png)

Para crear la partida se debe presionar el boton 'Crear partida’ y esperar a que TODOS los jugadores se conecten:

![Paso 6](img/menu-pasos/paso-6.png)

## 4.2 Jugabilidad

A continuacion se listan las teclas utilizadas en el juego.

• FLECHA ARRIBA: Redireccionar la mira (aumenta el angulo).

• FLECHA ABAJO: Redireccionar la mira (decrementa el angulo).

• FLECHA DERECHA: El gusano se mueve hacia la izquierda.

• FLECHA IZQUIERDA: El gusano se mueve hacia la izquierda.

• ENTER: El gusano da un salto hacia adelante.

• RETROCESO: El gusano da una vuelta hacia atras.

• ESPACIO: Manteniendo presionada esta tecla, la potencia de un disparo se acumula. Si se suelta se produce el disparo.

• C: Manteniendo presionada esta tecla se habilita el movimiento de la camara con el mouse.

• CLICK IZQUIERDO: Si el gusano tiene equipado armas teledirigidas, presionando click izquierdo
sobre la pantalla se determina el punto exacto donde el proyectil deberıa caer o la herramienta
deberıa usarse.

• CLICK DERECHO: Abre el menu de armas. Para cerrarlo se debe volver a presionar click derecho.

• NUMEROS 1-5: Si se presiona alguna de estas teclas, se puede prefijar el tiempo de espera de un
arma seleccionando una cuenta regresiva de 1, 2, 3, 4 o 5 segundos respectivamente.

• F1: El gusano se equipa el Bate de Baseball.

• F2: El gusano se equipa la Granada Verde.

• F3: El gusano se equipa la Bazooka.

• F4: El gusano se equipa la Banana.

• F5: El gusano se equipa la Granada Santa.

• F6: El gusano se equipa la Dinamita.

• F7: El gusano se equipa la Teletransportacion.

• F8: El gusano se equipa el Ataque Aereo.

• F9: El gusano se equipa la Granada Roja.

• F10: El gusano se equipa el Mortero.

## 4.3 Cheats

A continuacion se listan las teclas utilizadas en el juego para activar y desactivar los cheats.

• V: Vida infinita.

• T: Turno infinito.

• M: Municion infinita.

Nota: Presionando nuevamente estas teclas se desactivan los cheats.

# 5 Tests
Para correr los test unitarios del protocolo de comunicacion se deben realizar los siguientes pasos:

En una terminal ingresar el siguiente comando: 

1. Dirigirse a la carpeta build 

```
$ cd build

```
2. Dirigirse a la carpet gtest
```
$ cd gtest

```

3. Ejecutar el archivo de test
```
$ ./my_test 

```

> Se espera que una vez realizado el ultimo comando en la terminal, se encuentre un resultado como:

![SALIDA TESTs](img/salida_esperada_test.png)

A la izquierda se pueden observar que el test se ejecuto `RUN` y si su salida fue exitosa `OK`.
Luego de "Global test enviroment tear-down" se observa la cantudad de test realiados y debajo cuantos de ellos tuvieron resultado exitoso.
A su vez si el resultado de alguno no es exitoso el color no seria verde sino que rojo.
