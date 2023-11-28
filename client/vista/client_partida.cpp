#include "client_partida.h"
#include <unistd.h>

#define TITULO "Worms 2D"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Partida::Partida(Client &cliente) : cliente(cliente), fuente(DATA_PATH "/Vera.ttf", 18), temporizador({60000, 0, 0, 0}), camara(ANCHO_VENTANA, ALTO_VENTANA) {}

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

    /******************** INICIALIZAR MUSICA AMBIENTE ********************/

    // Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    // Chunk sound(DATA_PATH "/sonidos/musica-ambiente.ogg");

    // sound.SetVolume(SDL_MIX_MAXVOLUME / 8); // Ajustamos el nivel de volumen

    // mixer.FadeInChannel(-1, sound, -1, 0); // Ajustamos la cantidad de loops con el tercer parametro (infinitos)

    /******************** TEXTURAS Y COLORES ********************/

    inicializar_texturas(renderer);
    inicializar_colores();

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, colores);

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
    this->texturas[1] = new Texture(renderer, Surface(DATA_PATH "/blue00.png").SetColorKey(true, 0));
    // this->texturas[1] = new Texture(renderer, Surface(DATA_PATH "/agua.png").SetColorKey(true, 0));
    this->texturas[2] = new Texture(renderer, Surface(DATA_PATH "/grdl4.png").SetColorKey(true, 0xff));
    this->texturas[3] = new Texture(renderer, Surface(DATA_PATH "/grds4.png").SetColorKey(true, 0xff));
}

void Partida::inicializar_colores() {
    this->colores[0] = SDL2pp::Color(255,80,80); // Rojo
    this->colores[1] = SDL2pp::Color(80,80,255); // Azul
    this->colores[2] = SDL2pp::Color(80,255,80); // Verde
    this->colores[3] = SDL2pp::Color(0,255,255); // Celeste
    this->colores[4] = SDL2pp::Color(255,128,192); // Rosa
    this->colores[5] = SDL2pp::Color(255,255,80); // Amarillo
    this->colores[6] = SDL2pp::Color(255,255,255); // Blanco
    this->colores[7] = SDL2pp::Color(0,0,0); // Negro
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

        this->worms[gusano->get_id()] = new Worm(renderer, colores[(int) gusano->get_color()], (int) gusano->get_color(), metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), nuevoY, (int) gusano->get_vida(), (int) gusano->get_direccion());
    }
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

            case SDL_MOUSEMOTION:
                float x = -(event.motion.xrel);
                float y = -(event.motion.yrel);

                if ((x <= 1) && (x >= -1) && (y <= 1) && (y >= -1)) {
                    this->camara.mover(x, y);
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
                this->y = (renderer.GetOutputHeight()) - event.button.y;

                this->camara.setMoverCamara(true);
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
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(1);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_2:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(2);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_3:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(3);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_4:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(4);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_5:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(5);
                }

                break;

            // Si se presiona la tecla de F7 el worm se equipa un arma
            case SDLK_F1:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                }

                break;

            // Si se presiona la tecla de F2 el worm se equipa un arma
            case SDLK_F2:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F3:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));

                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F4:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F5:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F6:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F7:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F8:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F9:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F10:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    // Si le mandamos de nuevo un dto 'EquiparArma' con el mismo numero de arma el servidor le des-equipa el arma al Worm
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, MORTERO));
                
                } else {
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
                break;

            // Si se hace click izquierdo...
            case SDL_BUTTON_LEFT:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    enviarAtaque();
                }

                this->camara.setMoverCamara(false);
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
                                                               this->worms[this->id_gusano_actual]->get_tiempo()));
    
    } else if (armaEquipada == BAZOOKA) {
        cliente.send_queue.push(std::make_shared<Bazuka>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(), false));
    
    } else if (armaEquipada == BANANA) {
        cliente.send_queue.push(std::make_shared<GranadaBanana>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo()));
    
    } else if (armaEquipada == GRANADA_SANTA) {
        cliente.send_queue.push(std::make_shared<GranadaSanta>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->worms[this->id_gusano_actual]->get_tiempo()));
    
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
                                                               this->worms[this->id_gusano_actual]->get_tiempo()));
    
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

    if (dto->return_code() == GANADOR_CODE) {
        bool gano = ((int) dto->get_cliente_id() == (int) cliente.id);

        renderizar_resultado(renderer, gano);
        return false;
    }

    std::shared_ptr<Gusanos> gusanos  = std::dynamic_pointer_cast<Gusanos>(dto);

    /***** ACTUALIZAMOS EL ID DEL WORM QUE SE PODRA MOVER *****/

    int id_gusano_siguiente = gusanos->get_gusano_de_turno();

    if (this->id_gusano_actual != id_gusano_siguiente) {
        this->worms[this->id_gusano_actual]->set_turno(false); // Le aviso al Worm del turno anterior que ya no es mas su turno
        this->id_gusano_actual = id_gusano_siguiente;
        this->worms[this->id_gusano_actual]->set_turno(true); // Le aviso al Worm del turno actual que es su turno
        this->temporizador.tiempoInicial = this->temporizador.tiempoActual;
    
    } else {
        this->id_gusano_actual = id_gusano_siguiente;
        this->worms[this->id_gusano_actual]->set_turno(true);
    }

    /***** ACTUALIZAMOS LA POSICION DE CADA WORM *****/

    int cantidad = gusanos->cantidad();
    for (int i = 0; i < cantidad; i++) {
        std::shared_ptr<Gusano> gusano = gusanos->popGusano(i);

        int nuevoEstado = (int) gusano->get_estado();
        int tipoDeArma = (int) gusano->get_arma();

        if (nuevoEstado == MUERTO) {
            // this->worms.erase(gusano->get_id());
            this->worms[gusano->get_id()]->update_estado(renderer, nuevoEstado, tipoDeArma);
            continue;
        }

        float nuevoX = metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos()));
        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        this->worms[gusano->get_id()]->update(it, nuevoX, nuevoY, (int)gusano->get_vida(), (int) gusano->get_direccion(), (int) gusano->get_angulo());

        if ((this->worms[gusano->get_id()]->get_estado() != nuevoEstado) && (this->worms[gusano->get_id()]->get_estado() != APUNTANDO)) {
            this->worms[gusano->get_id()]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }

        else if ((this->worms[gusano->get_id()]->get_estado() != nuevoEstado) && (tipoDeArma == 10) && (this->worms[gusano->get_id()]->get_estado() == APUNTANDO)) {
            this->worms[gusano->get_id()]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }
    }

    /***** SI HAY PROYECTIL ACTUALIZAMOS SU POSICION Y LA CAMARA PARA QUE SE ENFOQUE EN ÈL *****/
    
    int flag = (int) gusanos->get_flag_proyectil();

    if (flag) {
        std::shared_ptr<Proyectiles> proyectiles = std::dynamic_pointer_cast<Proyectiles>(cliente.recv_queue.pop());
    
        int cantidad = proyectiles->cantidad();
        for (int i = 0; i < cantidad; i++) {
            std::shared_ptr<Proyectil> proyectil = proyectiles->popProyectil(i);

            float nuevoX = metros_a_pixeles(centimetros_a_metros((int)proyectil->x_pos()));
            float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)proyectil->y_pos()));
            this->worms[this->id_gusano_actual]->update_proyectil(renderer, (int) proyectil->get_id(), nuevoX, nuevoY, (int) proyectil->get_angulo(), (int) proyectil->get_direccion(), (int) proyectil->get_exploto(), (int) proyectil->get_tiempo());
        
            this->worms[this->id_gusano_actual]->set_camara(false);
            camara.seguir(nuevoX, nuevoY);
        }

    /***** ACTUALIZAMOS LA CAMARA PARA QUE SE ENFOQUE EN EL WORM DEL TURNO ACTUAL *****/

    } else {
        camara.seguirWorm(this->worms);
    }

    return true;
}

/******************** RENDERIZADO ********************/

void Partida::renderizar(SDL2pp::Renderer &renderer)
{
    renderer.SetDrawColor(0,0,0,255);
    renderer.Clear();

    renderizar_mapa(renderer);
    renderizar_agua(renderer);
    renderizar_temporizador(renderer);
    renderizar_worms(renderer);
    renderizar_vidas_totales(renderer);

    renderer.Present();
}

void Partida::renderizar_mapa(SDL2pp::Renderer &renderer)
{

    float altura = renderer.GetOutputHeight();

    renderer.Copy(*this->texturas[0], NullOpt, NullOpt);

    for (int i = 0; i < (int)this->vigas.size(); i++)
    {
        // Debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
        // tienen el (0,0) de los cuerpos en el centro de masa y ademas el (0,0) del mapa se ubica 
        // en la esquina inferior izquierda y no en la esquina superior izquierda como ocurre en SDL

        // Por ejemplo, si nos llega una viga larga en la posicion (5,5) siendo esta la posicon del centro de masa:
            // Al no hacer este corrimiento se graficara desde el (5,5) hasta el (11,5)
            // Al hacer este corrimiento se graficara desde el (2,5) hasta el (8,5) 
        
        float x = this->vigas[i]->x_pos() - (this->vigas[i]->return_ancho() / 2);
        float y = this->vigas[i]->y_pos() + (this->vigas[i]->return_alto() / 2);
        float ancho = this->vigas[i]->return_ancho();
        float alto = this->vigas[i]->return_alto();
        float angulo = -(this->vigas[i]->return_angulo());

        if (ancho == 600) {
            renderer.Copy(
                *this->texturas[2],
                Rect(0, 0, 50, 50),
                Rect(metros_a_pixeles(centimetros_a_metros(x) - this->camara.getLimiteIzquierdo()), altura - metros_a_pixeles(centimetros_a_metros(y) + this->camara.getLimiteSuperior()) ,
                metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
        
        } else if (ancho == 300) {
            renderer.Copy(
                *this->texturas[3],
                Rect(0, 0, 50, 50),
                Rect(metros_a_pixeles(centimetros_a_metros(x) - this->camara.getLimiteIzquierdo()), altura - metros_a_pixeles(centimetros_a_metros(y) + this->camara.getLimiteSuperior()),
                metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
        }
    }
}

void Partida::renderizar_agua(SDL2pp::Renderer &renderer) {
    Texture fondo(renderer, Surface(DATA_PATH "/back.png").SetColorKey(true, 0xff));

    float altura = renderer.GetOutputHeight();
    float ancho = renderer.GetOutputWidth();

    /***** Fondo *****/

    int i = - (ancho + metros_a_pixeles(this->camara.getLimiteIzquierdo()));
    int j = altura - metros_a_pixeles(this->camara.getLimiteSuperior());

    renderer.Copy(
        fondo, 
        NullOpt, 
        Rect(i,j + fondo.GetHeight(), (ancho + metros_a_pixeles(this->camara.getLimiteDerecho())), altura + metros_a_pixeles(this->camara.getLimiteInferior()))
    );

    /***** Olas *****/

    i = - (ancho + metros_a_pixeles(this->camara.getLimiteIzquierdo()));
    while (i < (ancho + metros_a_pixeles(this->camara.getLimiteDerecho()))) {

        int j = altura - metros_a_pixeles(this->camara.getLimiteSuperior());

        for(int x = 0; x < 5; x++) {
            renderer.Copy(
                *this->texturas[1], 
                NullOpt, 
                Rect(i,j, this->texturas[1]->GetWidth(), this->texturas[1]->GetHeight())
            );

            j += this->texturas[1]->GetHeight();
        }

        i += this->texturas[1]->GetWidth();
    }
}

void Partida::renderizar_worms(SDL2pp::Renderer &renderer)
{
    for (const auto &elemento : this->worms)
    {
        elemento.second->render(renderer, this->camara.getCentroX(), (this->camara.getLimiteIzquierdo() * 24), this->camara.getLimiteSuperior() * 24);
    }
}

void Partida::renderizar_vidas_totales(SDL2pp::Renderer &renderer) {

    std::map<int, int> vida_total;
    std::map<int, int> cantidad_worms;

    for (const auto &elemento : this->worms)
    {
        vida_total[elemento.second->get_color()] += elemento.second->get_vida();
        cantidad_worms[elemento.second->get_color()] += 1;
    }

    int offset = 0;
    for (const auto &elemento : vida_total) {
        int vida_total_maxima = (100 * cantidad_worms[elemento.first]);
        int ancho = (elemento.second * 200 / vida_total_maxima);

        /********** BORDE **********/

        SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

        renderer.Copy(
            borde,
            SDL2pp::NullOpt,
            SDL2pp::Rect((renderer.GetOutputWidth() / 2) - (vida_total_maxima/2) - 5, offset + (renderer.GetOutputHeight() - 30) - 5, (ancho) + 10, 18 + 10)
        );

        /********** VIDA **********/

        SDL2pp::Rect contenedor((renderer.GetOutputWidth() / 2) - (vida_total_maxima/2), offset + (renderer.GetOutputHeight() - 30), ancho, 18);
        renderer.SetDrawColor(this->colores[elemento.first]); 
        renderer.FillRect(contenedor);

        offset -= 30;
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

    Rect nombre(24, altura - 34, surface.GetWidth(), surface.GetHeight());
    renderer.Copy(texture, NullOpt, nombre);
}

void Partida::renderizar_resultado(SDL2pp::Renderer &renderer, bool resultado) {

    int currentFrame = 0;

    while (true)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {

                case SDL_QUIT:
                    return;

            }

            if (event.type == SDL_KEYDOWN)
            {

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                case SDLK_RETURN:
                    return;

            }

            }

        }

        renderer.SetDrawColor(0,0,0,255);
        renderer.Clear();

        int alto = renderer.GetOutputHeight();
        int ancho = renderer.GetOutputWidth();

        /********** LOGO **********/

        Texture logo(renderer, Surface(DATA_PATH "/background1.jpg").SetColorKey(true, 0xff));
        renderer.Copy(
            logo, 
            NullOpt, 
            Rect((ancho/2) - 212.5f, 10, 425, 240)
        );

        /********** WORM **********/

        if (resultado) {
            Texture worm_winner(renderer, Surface(DATA_PATH "/wwinner.png").SetColorKey(true, 0xff));

            int size = worm_winner.GetWidth();

            renderer.Copy(
                worm_winner, 
                SDL2pp::Rect(0, (size) * currentFrame, size, size), 
                Rect((ancho/2) - 30, (alto/2) - 20, size, size)
            );

            currentFrame++;
            currentFrame = currentFrame % (worm_winner.GetHeight() / worm_winner.GetWidth());

        } else {
            Texture worm_loser(renderer, Surface(DATA_PATH "/wloser.png").SetColorKey(true, 0xff));

            int size = worm_loser.GetWidth();

            renderer.Copy(
                worm_loser, 
                SDL2pp::Rect(0, (size) * currentFrame, size, size), 
                Rect((ancho/2) - 30, (alto/2) - 20, size, size)
            );

            currentFrame++;
            currentFrame = currentFrame % (worm_loser.GetHeight() / worm_loser.GetWidth());
        }

        /********** RESULTADO **********/

        std::string mensaje_resultado = resultado ? ("Ganaste") : ("Perdiste");

        Color blanco(255, 255, 255, 255);
        Surface surface_resultado = this->fuente.RenderText_Solid(mensaje_resultado, blanco);
        Texture texture_resultado(renderer, surface_resultado);

        Rect recta_resultado((ancho/2) - 35, (alto/2) + 65, surface_resultado.GetWidth(), surface_resultado.GetHeight());
        renderer.Copy(texture_resultado, NullOpt, recta_resultado);

        /********** MENSAJE DE SALIDA **********/

        Surface surface_salir = this->fuente.RenderText_Solid("Presione ENTER para salir", blanco);
        Texture texture_salir(renderer, surface_salir);

        Rect recta_salir((ancho/2) - 110, (alto/2) + 120, surface_salir.GetWidth(), surface_salir.GetHeight());
        renderer.Copy(texture_salir, NullOpt, recta_salir);
        
        renderer.Present(); 

    }
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

    for (int i = 0; i < (int)this->texturas.size(); i++)
    {
        delete this->texturas[i];
    }

    for (int i = 0; i < (int)this->worms.size(); i++)
    {
        Worm *worm = this->worms[i];
        delete worm;
    }
}
