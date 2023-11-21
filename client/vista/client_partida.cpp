#include "client_partida.h"
#include <unistd.h>

#define TITULO "Worms 2D"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Partida::Partida(Client &cliente) : cliente(cliente), fuente(DATA_PATH "/Vera.ttf", 12), temporizador({60000, 0, 0, 0}), camara(ANCHO_VENTANA, ALTO_VENTANA) {}

int Partida::iniciar()
{
    /******************** INICIAR SDL ********************/

    SDL sdl(SDL_INIT_VIDEO);

    Window window(TITULO,
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  ANCHO_VENTANA, ALTO_VENTANA,
                  SDL_WINDOW_RESIZABLE);

    // Window& SetIcon(const Surface& icon);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    /******************** TEXTURAS Y COLORES ********************/

    inicializar_texturas(renderer);
    inicializar_colores();

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, colores);

    // this->proyectil = new AnimacionProyectil(renderer);

    /******************** GAME LOOP ********************/

    this->temporizador.tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).

    auto t1 = SDL_GetTicks();
    int it = 0;            // Registro del numero de iteraciones
    auto rate = 1000 / 30; // El tiempo entre cada iteracion sera de '1000 / 30' milisegundos. Como 'rate' es igual a '1000 / 30' quiere
                           // decir que la velocidad entre iteraciones sera de 30 veces por segundo

    while (true)
    {
        t1 = SDL_GetTicks(); // Inicializamos 't1' con el tiempo actual en milisegundos

        this->temporizador.tiempoActual = SDL_GetTicks();
        unsigned int tiempoTranscurrido = this->temporizador.tiempoActual - this->temporizador.tiempoInicial;
        this->temporizador.tiempoRestante = this->temporizador.cuentaRegresiva - tiempoTranscurrido;

        if (tiempoTranscurrido > this->temporizador.cuentaRegresiva)
        {
            this->temporizador.tiempoInicial = this->temporizador.tiempoActual;
        }

        if (handleEvents(renderer))
        {
            cliente.kill();
            liberar_memoria();
            return 0;
        }

        if (not actualizar(renderer, it)) {
            std::cout << "Se fue" << std::endl;
            cliente.elOtroSeFue();
            liberar_memoria();
            return 0;
        }

        renderizar(renderer);

        /* IF BEHIND, KEEP WORKING */
        // Buscamos mantener un ritmo constante para ejecutar las funciones 'actualizar' y 'renderizar'
        // a una velocidad especifica 'rate'

        auto t2 = SDL_GetTicks();    // Inicializamos 't2' con el tiempo actual en milisegundos
        int rest = rate - (t2 - t1); // Cantidad de tiempo que debe esperarse
                                     // antes de la proxima iteracion. Al tiempo deseado entre iteraciones le restamos
                                     // la diferencia entre 't2' y 't1' que es el tiempo que se tardo en actualizar y renderizar

        // Si 'rest' es menor a cero quiere decir que nos estamos retrasando en comparacion
        // con el ritmo deseado
        if (rest < 0)
        {
            auto behind = -rest;                // ¿Cuanto tiempo estamos retrasados?
            auto lost = behind - behind % rate; // ¿Cuanto tiempo perdimos?
            t1 += lost;                         // Ajustamos 't1' para ponernos al dia con el tiempo perdido
            it += int(lost / rate);             // Aumentamos 'it' para reflejar las iteraciones que
                                                // se han perdido debido al retraso

            // Si 'rest' es mayor o igual a cero quiere decir que no nos estamos quedando atras
        }
        else
        {
            // std::cout << rest << std::endl;
            SDL_Delay(rest); // Descansamos el valor 'rest' antes de la proxima iteracion para
                             // mantener un ritmo constante
        }

        t1 += rate; // Aumentamos 't1' en 'rate' para programar la proxima iteracion
        it += 1;    // Aumentamos 'it' en 1 para mantener un registro del numero de iteraciones

        // Nota: Si no casteamos a int la variable 'rest' se produce un desbordamiento y rest puede ser igual a '4294967294' lo cual hace
        // 		 que se cuelgue el juego
    }

    return 0;
}

/******************** ALMACENAMIENTO DEL ESTADO INICIAL DEL JUEGO ********************/

void Partida::inicializar_texturas(SDL2pp::Renderer &renderer) {
    this->texturas[0] = new Texture(renderer, Surface(DATA_PATH "/background.png").SetColorKey(true, 0xff));
    this->texturas[1] = new Texture(renderer, Surface(DATA_PATH "/agua.png").SetColorKey(true, 0xff));
    this->texturas[2] = new Texture(renderer, Surface(DATA_PATH "/grdl4.png").SetColorKey(true, 0xff));
}

void Partida::inicializar_colores() {
    this->colores[0] = SDL2pp::Color(255,0,0); // Rojo
    this->colores[1] = SDL2pp::Color(0,0,255); // Azul
    this->colores[2] = SDL2pp::Color(0,255,0); // Verde
    this->colores[3] = SDL2pp::Color(255,255,255); // Blanco
    this->colores[4] = SDL2pp::Color(0,0,0); // Negro
}

void Partida::guardar_vigas()
{
    std::shared_ptr<Dto> dto = cliente.recv_queue.pop();

    // Creamos la variable cantidad porque si incluimos en el for directamente 'dto->cantidad()' no iteraremos todas
    // las vigas ya que estamos haciendo pop y en cada iteracion disminuye la cantidad de elemtentos en la lista
    int cantidad = dto->cantidad();
    for (int i = 0; i < cantidad; i++)
    {
        std::shared_ptr<Viga> viga = std::dynamic_pointer_cast<Vigas>(dto)->popViga(i);
        // std::cout << "Agregando viga" << std::endl;
        this->vigas.push_back(viga);
    }
}

void Partida::guardar_worms(SDL2pp::Renderer &renderer, std::map<int, SDL2pp::Color> &colores)
{
    std::shared_ptr<Gusanos> dto = std::dynamic_pointer_cast<Gusanos>(cliente.recv_queue.pop());
    this->id_gusano_actual = dto->get_gusano_de_turno();

    float altura = renderer.GetOutputHeight();

    // Creamos la variable cantidad porque si incluimos en el for directamente 'dto->cantidad()' no iteraremos todos
    // los worms ya que estamos haciendo pop y en cada iteracion disminuye la cantidad de elemtentos en la lista
    int cantidad = dto->cantidad();
    for (int i = 0; i < cantidad; i++)
    {
        std::shared_ptr<Gusano> gusano = dto->popGusano(i);

        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));

        // std::cout << "Agregando worm" << std::endl;
        this->worms[gusano->get_id()] = new Worm(renderer, colores[(int) gusano->get_color()], metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), nuevoY, (int) gusano->get_vida(), (int) gusano->get_direccion());
    }

    camara.seguirWorm(this->worms[this->id_gusano_actual]->get_x(), this->worms[this->id_gusano_actual]->get_y());

    // delete dto;
}

/******************** HANDLER DE EVENTOS ********************/

bool Partida::handleEvents(SDL2pp::Renderer &renderer)
{
    // Procesamiento de evento
    SDL_Event event;

    // Revisamos si hay algun evento pendiente en la cola de eventos de SDL y, si lo hay, lo almacenamos en la estructura event.
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {

            // Si la ventana se cierra terminamos la ejecucion
            case SDL_QUIT:
                return true;
            
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->camara.setDimensiones(renderer.GetOutputWidth(), renderer.GetOutputHeight());
                }
        }

        // Si se hace click ...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            switch (event.button.button)
            {

            // Si se hace click derecho se muestra el menu de armas
            case SDL_BUTTON_RIGHT:
                break;

            // Si se hace click izquierdo...
            case SDL_BUTTON_LEFT:
                this->x = event.button.x;
                this->y = renderer.GetOutputHeight() - event.button.y;
                break;
            }

            // Si se presiona alguna tecla...
        }
        else if (event.type == SDL_KEYDOWN)
        {

            switch (event.key.keysym.sym)
            {

            // Si se presiona la tecla "Q" o "ESC" terminamos la ejecucion
            case SDLK_ESCAPE:
            case SDLK_q:
                return true;

            // Si se presiona la flecha hacia la derecha el gusano se mueve hacia la derecha
            case SDLK_RIGHT:
                cliente.send_queue.push(std::make_shared<MoverADerecha>(this->cliente.id));
                break;

            // Si se presiona la flecha hacia la izquierda el gusano se mueve hacia la izquierda
            case SDLK_LEFT:
                cliente.send_queue.push(std::make_shared<MoverAIzquierda>(this->cliente.id));
                break;

            // Si se presiona la flecha hacia ariba el gusano direcciona su arma
            case SDLK_UP:
                this->worms[this->id_gusano_actual]->aumentar_angulo();
                break;

            // Si se presiona la flecha hacia abajo el gusano direcciona su arma
            case SDLK_DOWN:
                this->worms[this->id_gusano_actual]->decrementar_angulo();
                break;

            // Si se presiona la tecla de enter el gusano salta hacia adelante
            case SDLK_RETURN:
                
                if (this->worms[this->id_gusano_actual]->get_estado() != APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<Saltar>(this->cliente.id, SALTO_ADELANTE));
                } 
                
                break;

            // Si se presiona la tecla de espacio disparamos o aumentamos la potencia del disparo
            case SDLK_SPACE:
                this->worms[this->id_gusano_actual]->aumentar_potencia();
                break;

            // Si se presiona la tecla de retroceso el gusano salta hacia atras
            case SDLK_BACKSPACE:

                if (this->worms[this->id_gusano_actual]->get_estado() != APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<Saltar>(this->cliente.id, SALTO_ATRAS));
                } 

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_1:
                
                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    this->worms[this->id_gusano_actual]->set_tiempo(1);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_2:
                
                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    this->worms[this->id_gusano_actual]->set_tiempo(2);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_3:
                
                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    this->worms[this->id_gusano_actual]->set_tiempo(3);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_4:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    this->worms[this->id_gusano_actual]->set_tiempo(4);
                }

                break;

            // Si se presiona la tecla de F7 el worm se equipa un arma
            case SDLK_F1:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, BATE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                }

                break;

            // Si se presiona la tecla de F2 el worm se equipa un arma
            case SDLK_F2:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, GRANADA_VERDE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F3:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));

                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, BAZOOKA);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F4:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, BANANA);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F5:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, GRANADA_SANTA);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F6:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, DINAMITA);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F7:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, TELETRANSPORTACION);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F8:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, ATAQUE_AEREO);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F9:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, GRANADA_ROJA);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F10:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, MORTERO));
                
                } else {
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, EQUIPANDO_ARMA, MORTERO);
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, MORTERO));
                }

                break;

            }

        }

        // Si se suelta un click
        else if (event.type == SDL_MOUSEBUTTONUP)
        {

            switch (event.button.button)
            {

            // Si se hace click derecho se muestra el menu de armas
            case SDL_BUTTON_RIGHT:
                std::cout << "Click derecho se suelta: " << std::endl;
                break;

            // Si se hace click izquierdo...
            case SDL_BUTTON_LEFT:
                std::cout << "Click izquierdo se suelta: " << std::endl;
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    enviarAtaque();
                    int tipoDeArma = this->worms[this->id_gusano_actual]->get_tipo_de_arma();
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, tipoDeArma));
                    // this->worms[this->id_gusano_actual]->update_estado(renderer, MOVIENDOSE);
                }

                break;
            }

            // Si se presiona alguna tecla...
        }

        // Si se suelta alguna tecla...
        else if (event.type == SDL_KEYUP)
        {

            switch (event.key.keysym.sym)
            {

            // Si se suelta la flecha hacia la derecha cambiamos el estado del gusano
            case SDLK_RIGHT:
                break;

            // Si se suelta la flecha hacia la izquierda cambiamos el estado del gusano
            case SDLK_LEFT:
                break;

            // Si se suelta la flecha hacia ariba...
            case SDLK_UP:
                // ...
                break;

            // Si se suelta la flecha hacia abajo...
            case SDLK_DOWN:
                // ...
                break;

            // Si se suelta la tecla de enter...
            case SDLK_RETURN:
                // ...
                break;

            // Si se suelta la tecla de espacio...
            case SDLK_SPACE:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    enviarAtaque();
                }
                
                break;

            // Si se suelta la tecla de retroceso...
            case SDLK_BACKSPACE:
                // ...
                break;

            // Si se suelta la tecla del numero 0...
            case SDLK_0:
                // ...
                break;
            }
        }
    }

    return false;
}

void Partida::enviarAtaque() {
    int armaEquipada = this->worms[this->id_gusano_actual]->get_tipo_de_arma();

    if(armaEquipada == BATE) {
        cliente.send_queue.push(std::make_shared<Batear>(this->cliente.id, this->worms[this->id_gusano_actual]->get_angulo()));
    
    } else if (armaEquipada == GRANADA_VERDE) {
        cliente.send_queue.push(std::make_shared<GranadaVerde>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo(), false));
    
    } else if (armaEquipada == BAZOOKA) {
        cliente.send_queue.push(std::make_shared<Bazuka>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(), false));
    
    } else if (armaEquipada == BANANA) {
        cliente.send_queue.push(std::make_shared<GranadaBanana>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo(), false));
    
    } else if (armaEquipada == GRANADA_SANTA) {
        cliente.send_queue.push(std::make_shared<GranadaSanta>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo(), false));
    
    } else if (armaEquipada == DINAMITA) {
        cliente.send_queue.push(std::make_shared<Dinamita>(this->cliente.id, this->worms[this->id_gusano_actual]->get_tiempo(), false));
    
    } else if (armaEquipada == TELETRANSPORTACION) {
        int xCentimetros = metros_a_centimetros(pixeles_a_metros(this->x) + this->camara.getLimiteIzquierdo());
        int yCentimetros = metros_a_centimetros(pixeles_a_metros(this->y) - this->camara.getLimiteSuperior());
        cliente.send_queue.push(std::make_shared<Teletransportar>(this->cliente.id, xCentimetros, yCentimetros));
    
    } else if (armaEquipada == ATAQUE_AEREO) {
        int xCentimetros = metros_a_centimetros(pixeles_a_metros(this->x) + this->camara.getLimiteIzquierdo());
        int yCentimetros = metros_a_centimetros(pixeles_a_metros(this->y) - this->camara.getLimiteSuperior());
        cliente.send_queue.push(std::make_shared<Misil>(this->cliente.id, xCentimetros, yCentimetros, false));
    
    } else if (armaEquipada == GRANADA_ROJA) {
        cliente.send_queue.push(std::make_shared<GranadaRoja>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo(), false));
    
    } else if (armaEquipada == MORTERO) {
        cliente.send_queue.push(std::make_shared<Mortero>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(), false));
    
    } else {
        std::cerr << "El numero recibido no esta asociado a ningun arma\n";
    }
}

/******************** ACTUALIZACION ********************/

bool Partida::actualizar(SDL2pp::Renderer &renderer, int it)
{
    float altura = renderer.GetOutputHeight();
    std::shared_ptr<Dto> dto = cliente.recv_queue.pop();
    
    if(not dto->is_alive())
        return false;

    std::shared_ptr<Gusanos> gusanos  = std::dynamic_pointer_cast<Gusanos>(dto);

    /***** ACTUALIZAMOS EL ID DEL WORM QUE SE PODRA MOVER *****/

    int id_gusano_siguiente = gusanos->get_gusano_de_turno();

    if (this->id_gusano_actual != id_gusano_siguiente) {
        this->worms[this->id_gusano_actual]->desactivar_turno(); // Le aviso al Worm del turno anterior que ya no es mas su turno
        this->id_gusano_actual = id_gusano_siguiente;
        this->worms[this->id_gusano_actual]->activar_turno(); // Le aviso al Worm del turno actual que es su turno
        this->temporizador.tiempoInicial = this->temporizador.tiempoActual;
    }

    /***** ACTUALIZAMOS LA POSICION DE CADA WORM *****/

    int cantidad = gusanos->cantidad();
    for (int i = 0; i < cantidad; i++) {
        std::shared_ptr<Gusano> gusano = gusanos->popGusano(i);

        int nuevoEstado = (int) gusano->get_estado();
        int tipoDeArma = (int) gusano->get_arma();

        if (nuevoEstado == MUERTO) {
            this->worms.erase(gusano->get_id());
            continue;
        }

        float nuevoX = metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos()));
        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        this->worms[gusano->get_id()]->update(it, nuevoX, nuevoY, (int)gusano->get_vida(), (int) gusano->get_direccion());

        if ((this->worms[gusano->get_id()]->get_estado() != nuevoEstado) && (this->worms[gusano->get_id()]->get_estado() != APUNTANDO)) {
            this->worms[gusano->get_id()]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }

        else if ((this->worms[gusano->get_id()]->get_estado() != nuevoEstado) && (tipoDeArma == 10) && (this->worms[gusano->get_id()]->get_estado() == APUNTANDO)) {
            this->worms[gusano->get_id()]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }
    }

    /***** ACTUALIZAMOS LA POSICION DEL PROYECTIL (SI ES QUE HAY) *****/
    
    int flag = (int) gusanos->get_flag_proyectil();

    // std::cout << flag << std::endl;

    if (flag) {
        // std::cout << "\nEntro a recibir proyectiles\n";
        std::shared_ptr<Proyectiles> proyectiles = std::dynamic_pointer_cast<Proyectiles>(cliente.recv_queue.pop());
    
        int cantidad = proyectiles->cantidad();
        // std::cout << "Cantidad de proyectiles: " << cantidad << std::endl;
        for (int i = 0; i < cantidad; i++) {
            std::shared_ptr<Proyectil> proyectil = proyectiles->popProyectil(i);

            // std::cout << "Proyectil: " << (int) proyectil->get_id() << " " << (int) proyectil->get_exploto() << std::endl;
            std::cout << "Worm: " << this->id_gusano_actual << std::endl;

            float nuevoX = metros_a_pixeles(centimetros_a_metros((int)proyectil->x_pos()));
            float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)proyectil->y_pos()));
            this->worms[this->id_gusano_actual]->update_proyectil(renderer, (int) proyectil->get_id(), nuevoX, nuevoY, (int) proyectil->get_angulo(), (int) proyectil->get_direccion(), (int) proyectil->get_exploto());
        }

        // std::cout << "Salgo de recibir proyectiles\n\n" << std::endl;
    }

    /***** ACTUALIZAMOS LA CAMARA PARA QUE SE ENFOQUE EN EL WORM DEL TURNO ACTUAL *****/

    camara.seguirWorm(this->worms[this->id_gusano_actual]->get_x(), this->worms[this->id_gusano_actual]->get_y());
    return true;
}

/******************** RENDERIZADO ********************/

void Partida::renderizar(SDL2pp::Renderer &renderer)
{
    renderer.Clear();

    renderizar_mapa(renderer);
    renderizar_temporizador(renderer);
    renderizar_worms(renderer);

    renderer.Present();
}

void Partida::renderizar_mapa(SDL2pp::Renderer &renderer)
{

    renderer.Copy(*this->texturas[0], NullOpt, NullOpt);
    renderer.Copy(*this->texturas[1], NullOpt, NullOpt);

    float altura = renderer.GetOutputHeight();

    for (int i = 0; i < (int)this->vigas.size(); i++)
    {
        // Debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
        // tienen el (0,0) de los cuerpos en el centro y ademas el (0,0) del mapa se ubica 
        // en la esquina inferior izquierda y no en la esquina superior izquierda como ocurre en SDL
        float x = this->vigas[i]->x_pos();
        float y = this->vigas[i]->y_pos();
        float ancho = this->vigas[i]->return_ancho();
        float alto = this->vigas[i]->return_alto();
        float angulo = -(this->vigas[i]->return_angulo());

        renderer.Copy(
            *this->texturas[2],
            Rect(0, 0, 50, 50),
            Rect(metros_a_pixeles(centimetros_a_metros(x) - this->camara.getLimiteIzquierdo()) - 70, altura - metros_a_pixeles(centimetros_a_metros(y) + this->camara.getLimiteSuperior()) - 10,
            metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
    }
}

void Partida::renderizar_worms(SDL2pp::Renderer &renderer)
{
    for (const auto &elemento : this->worms)
    {
        elemento.second->render(renderer, this->camara, this->camara.getCentroX(), (this->camara.getLimiteIzquierdo() * 24), this->camara.getLimiteSuperior() * 24);
    }
}

void Partida::renderizar_temporizador(SDL2pp::Renderer &renderer)
{
    int altura = renderer.GetOutputHeight();

    Rect borde(5, altura - 42, 65, 36);
    Color blanco(255, 255, 255, 255);
    renderer.SetDrawColor(blanco);
    renderer.FillRect(borde);

    Rect contenedor(7, altura - 40, 61, 32);
    Color negro(0, 0, 0, 255);
    renderer.SetDrawColor(negro);
    renderer.FillRect(contenedor);

    Surface surface = this->fuente.RenderText_Solid(std::to_string((int) (this->temporizador.tiempoRestante * 0.001)), blanco);
    Texture texture(renderer, surface);

    Rect nombre(24, altura - 34, surface.GetWidth() + 5, surface.GetHeight() + 5);
    renderer.Copy(texture, NullOpt, nombre);
}

/******************** CONVERSIONES ********************/

float Partida::metros_a_pixeles(float metros)
{
    return metros * 24;
}

float Partida::centimetros_a_metros(float centimetros)
{
    return centimetros / 100;
}

float Partida::pixeles_a_metros(float pixeles)
{
    return pixeles / 24;
}

float Partida::metros_a_centimetros(float metros)
{
    return metros * 100;
}

/******************** MEMORIA ********************/

void Partida::liberar_memoria()
{

    for (int i = 0; i < (int)this->vigas.size(); i++)
    {
        std::shared_ptr<Viga> viga = this->vigas[i];
        // std::cout << "Eliminando viga" << std::endl;
        // delete viga;
    }

    for (int i = 0; i < (int)this->worms.size(); i++)
    {
        Worm *worm = this->worms[i];
        // std::cout << "Eliminando worm" << std::endl;
        delete worm;
    }
}
