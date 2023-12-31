#include "client_partida.h"
#include <unistd.h>

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

#define VOLUMEN_MUSICA_AMBIENTE SDL_MIX_MAXVOLUME / 15
#define CANAL_MUSICA_AMBIENTE 0

#define FPS 1000 / 30

#define OFFSET_VIDAS_TOTALES 30

#define RELACION_METRO_PIXEL 24
#define RELACION_CENTIMETRO_METRO 100

Partida::Partida(Client &cliente) : cliente(cliente), fuente(DATA_PATH "/Vera.ttf", 18), camara(ANCHO_VENTANA, ALTO_VENTANA) 
{
    YAML::Node nodo = YAML::LoadFile("../configuracion.yml");
    this->temporizador.cuentaRegresiva = (nodo["turn_duration"].as<unsigned int>()) * 1000;
}

int Partida::iniciar()
{
    try {

    /******************** INICIAR SDL ********************/

    SDL sdl(SDL_INIT_VIDEO); 

    std::string titulo = "Worms 2D - Jugador " + std::to_string(this->cliente.id);

    Window window(titulo,
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  ANCHO_VENTANA, ALTO_VENTANA,
                  SDL_WINDOW_RESIZABLE);

    window.SetIcon(Surface(DATA_PATH "/icono.png").SetColorKey(true, 0));  

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    /******************** INICIALIZAR MUSICA AMBIENTE ********************/

    Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    Chunk sound(DATA_PATH "/sonidos/musica-ambiente.ogg");

    sound.SetVolume(VOLUMEN_MUSICA_AMBIENTE);

    mixer.PlayChannel(CANAL_MUSICA_AMBIENTE, sound, -1);

    /******************** TEXTURAS Y COLORES ********************/

    inicializar_texturas(renderer);
    inicializar_sonidos(renderer);
    inicializar_colores();

    this->armas = std::make_unique<MenuArmas>(renderer);

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, colores);

    /******************** GAME LOOP ********************/

    this->temporizador.tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).

    auto t1 = SDL_GetTicks();
    int it = 0; // Registro del numero de iteraciones
    auto rate = FPS;

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
            cliente.servidorCerro();
            liberar_memoria();
            return this->resultado;
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

    } catch (const std::exception &err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    }
}

/******************** ALMACENAMIENTO DEL ESTADO INICIAL DEL JUEGO ********************/

void Partida::guardar_vigas()
{
    std::shared_ptr<Dto> dto = cliente.recv_queue.pop();

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

    int cantidad = dto->cantidad();
    for (int i = 0; i < cantidad; i++)
    {
        std::shared_ptr<Gusano> gusano = dto->popGusano(i);

        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        this->worms[gusano->get_id()] = new AnimacionWorm(renderer, this->texturas, this->sonidos, colores[(int) gusano->get_color()], (int) gusano->get_color(), metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), nuevoY, (int) gusano->get_vida(), (int) gusano->get_direccion());
    }
}

/******************** HANDLER DE EVENTOS ********************/

bool Partida::handleEvents(SDL2pp::Renderer &renderer)
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {

            case SDL_QUIT:
                return true;
            
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->camara.setDimensiones(renderer.GetOutputWidth(), renderer.GetOutputHeight());
                }

            case SDL_MOUSEMOTION:
                float x = -(event.motion.xrel) * 0.1;
                float y = -(event.motion.yrel) * 0.1;

                if ((x <= 1) && (x >= -1) && (y <= 1) && (y >= -1)) {
                    this->camara.mover(x, y);
                }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            switch (event.button.button)
            {

            case SDL_BUTTON_RIGHT:
                this->armas->abrirMenu();
                break;

            case SDL_BUTTON_LEFT:
                this->x = event.button.x;
                this->y = (renderer.GetOutputHeight()) - event.button.y;
                break;
            }

        }
        else if (event.type == SDL_KEYDOWN)
        {

            switch (event.key.keysym.sym)
            {

            case SDLK_ESCAPE:
            case SDLK_q:
                return true;

            case SDLK_c:
                this->camara.setMoverCamara(true);
                break;

            case SDLK_RIGHT:
                cliente.send_queue.push(std::make_shared<MoverADerecha>(this->cliente.id));
                break;

            case SDLK_LEFT:
                cliente.send_queue.push(std::make_shared<MoverAIzquierda>(this->cliente.id));
                break;

            case SDLK_UP:
                this->worms[this->id_gusano_actual]->aumentar_angulo();
                break;

            case SDLK_DOWN:
                this->worms[this->id_gusano_actual]->decrementar_angulo();
                break;

            case SDLK_RETURN:
                
                if (this->worms[this->id_gusano_actual]->get_estado() != APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<Saltar>(this->cliente.id, SALTO_ADELANTE));
                } 
                
                break;

            case SDLK_SPACE:
                this->worms[this->id_gusano_actual]->aumentar_potencia();
                break;

            case SDLK_BACKSPACE:

                if (this->worms[this->id_gusano_actual]->get_estado() != APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<Saltar>(this->cliente.id, SALTO_ATRAS));
                } 

                break;

            case SDLK_1:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(1);
                }

                break;

            case SDLK_2:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(2);
                }

                break;

            case SDLK_3:
                
                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(3);
                }

                break;

            case SDLK_4:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(4);
                }

                break;

            case SDLK_5:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    this->worms[this->id_gusano_actual]->set_tiempo(5);
                }

                break;

            case SDLK_F1:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BATE));
                }

                break;

            case SDLK_F2:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_VERDE));
                }

                break;

            case SDLK_F3:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));

                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BAZOOKA));
                }

                break;

            case SDLK_F4:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, BANANA));
                }

                break;

            case SDLK_F5:

                if (this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_SANTA));
                }

                break;

            case SDLK_F6:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, DINAMITA));
                }

                break;

            case SDLK_F7:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, TELETRANSPORTACION));
                }

                break;

            case SDLK_F8:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, ATAQUE_AEREO));
                }

                break;

            case SDLK_F9:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, GRANADA_ROJA));
                }

                break;

            case SDLK_F10:

                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, MORTERO));
                
                } else {
                    cliente.send_queue.push(std::make_shared<EquiparArma>(this->cliente.id, MORTERO));
                }

                break;

            }

        }

        else if (event.type == SDL_MOUSEBUTTONUP)
        {

            switch (event.button.button)
            {

            case SDL_BUTTON_RIGHT:
                this->camara.setMoverCamara(false);
                break;

            case SDL_BUTTON_LEFT:
                
                if (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA) {
                    enviarAtaque();
                }

                break;
            }
        }

        else if (event.type == SDL_KEYUP)
        {

            switch (event.key.keysym.sym)
            {

            case SDLK_c:
                this->camara.setMoverCamara(false);
                break;

            case SDLK_v:
                cliente.send_queue.push(std::make_shared<Cheat>(this->cliente.id, VIDA_INFINITA_CODE));
                break;

            case SDLK_t:
                cliente.send_queue.push(std::make_shared<Cheat>(this->cliente.id, TURNO_INFINITO_CODE));
                break;

            case SDLK_m:
                cliente.send_queue.push(std::make_shared<Cheat>(this->cliente.id, MUNICION_INFINITA_CODE));
                break;

            case SDLK_SPACE:

                if ((this->worms[this->id_gusano_actual]->get_estado() == APUNTANDO) || (this->worms[this->id_gusano_actual]->get_estado() == EQUIPANDO_ARMA)) {
                    enviarAtaque();
                }
                
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
        this->resultado = ((int) dto->get_cliente_id() == (int) cliente.id);
        return false;
    }

    std::shared_ptr<Gusanos> gusanos  = std::dynamic_pointer_cast<Gusanos>(dto);

    /***** ACTUALIZAMOS EL ID DEL WORM QUE SE PODRA MOVER *****/

    int id_gusano_siguiente = gusanos->get_gusano_de_turno();
    
    if (this->id_gusano_actual != id_gusano_siguiente) {
        this->camara.seguir(this->worms[id_gusano_siguiente]->get_x(), this->worms[id_gusano_siguiente]->get_y());
        this->temporizador.tiempoInicial = this->temporizador.tiempoActual;
    }

    this->id_gusano_actual = id_gusano_siguiente;

    /***** ACTUALIZAMOS LA POSICION DE CADA WORM *****/

    int cantidad = gusanos->cantidad();
    for (int i = 0; i < cantidad; i++) {
        std::shared_ptr<Gusano> gusano = gusanos->popGusano(i);

        int id = gusano->get_id();
        int nuevoEstado = (int) gusano->get_estado();
        int tipoDeArma = (int) gusano->get_arma();

         if (nuevoEstado == MUERTO) {
            this->worms[id]->update_estado(renderer, nuevoEstado, tipoDeArma);

            float nuevoX = metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos()));
            float nuevoY = metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
            bool turno = (id == this->id_gusano_actual);

            this->worms[id]->update(it, nuevoX, nuevoY, (int)gusano->get_vida(), (int) gusano->get_direccion(), (int) gusano->get_angulo(), turno);
            continue;
        }

        float nuevoX = metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos()));
        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        bool turno = (id == this->id_gusano_actual);

        this->worms[id]->update(it, nuevoX, nuevoY, (int)gusano->get_vida(), (int) gusano->get_direccion(), (int) gusano->get_angulo(), turno);

        if ((this->worms[id]->get_tipo_de_arma() != tipoDeArma)) {
            this->worms[id]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }

        if ((this->worms[id]->get_estado() != nuevoEstado) && (this->worms[id]->get_estado() != APUNTANDO)) {
            this->worms[id]->update_estado(renderer, nuevoEstado, tipoDeArma);
        }

        else if ((this->worms[id]->get_estado() != nuevoEstado) && (tipoDeArma == SIN_ARMA) && (this->worms[id]->get_estado() == APUNTANDO)) {
            this->worms[id]->update_estado(renderer, nuevoEstado, tipoDeArma);
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
    renderizar_worms(renderer);
    renderizar_vidas_totales(renderer);
    renderizar_temporizador(renderer);

    this->armas->render(renderer);

    renderer.Present();
}

void Partida::renderizar_mapa(SDL2pp::Renderer &renderer)
{

    float altura = renderer.GetOutputHeight();

    renderer.Copy(*this->texturas[0], NullOpt, NullOpt);

    for (int i = 0; i < (int)this->vigas.size(); i++)
    {
        float x = this->vigas[i]->x_pos() - (this->vigas[i]->return_ancho() / 2);
        float y = metros_a_centimetros(pixeles_a_metros(altura)) - this->vigas[i]->y_pos() - (this->vigas[i]->return_alto() / 2);
        float ancho = this->vigas[i]->return_ancho();
        float alto = this->vigas[i]->return_alto();
        float angulo = -(this->vigas[i]->return_angulo());

        if (this->camara.comprobarRenderizado(centimetros_a_metros(x), centimetros_a_metros(y), centimetros_a_metros(ancho), centimetros_a_metros(ancho))) {

            if (ancho == 600) {
                renderer.Copy(
                    *this->texturas[2],
                    Rect(0, 0, 50, 50),
                    Rect(metros_a_pixeles(centimetros_a_metros(x) - this->camara.getLimiteIzquierdo()), metros_a_pixeles(centimetros_a_metros(y) - this->camara.getLimiteSuperior()) ,
                    metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
            
            } else if (ancho == 300) {
                renderer.Copy(
                    *this->texturas[3],
                    Rect(0, 0, 50, 50),
                    Rect(metros_a_pixeles(centimetros_a_metros(x) - this->camara.getLimiteIzquierdo()), metros_a_pixeles(centimetros_a_metros(y) - this->camara.getLimiteSuperior()),
                    metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
            }    
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

    for (const auto &elemento : this->worms) {
        float y = (elemento.second->get_estado() == MUERTO) ? (renderer.GetOutputHeight() - elemento.second->get_y()) : (elemento.second->get_y());

        if (this->camara.comprobarRenderizado(pixeles_a_metros(elemento.second->get_x()), pixeles_a_metros(y), 1.0f, 1.0f)) {
            float limiteSuperior = (elemento.second->get_estado() == MUERTO) ? (renderer.GetOutputHeight() - (this->camara.getLimiteSuperior() * 24)) : (this->camara.getLimiteSuperior() * 24);
            
            elemento.second->render(renderer, this->camara.getCentroX(), (this->camara.getLimiteIzquierdo() * 24), limiteSuperior);
        }

        elemento.second->render_arma(renderer, (this->camara.getLimiteIzquierdo() * 24), this->camara.getLimiteSuperior() * 24);

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

        SDL2pp::Rect borde((renderer.GetOutputWidth() / 2) - (200/2) - 5, offset + (renderer.GetOutputHeight() - 30) - 5, (ancho) + 10, 18 + 10);
        renderer.SetDrawColor(this->colores[6]); 
        renderer.FillRect(borde);

        /********** VIDA **********/

        SDL2pp::Rect contenedor((renderer.GetOutputWidth() / 2) - (200/2), offset + (renderer.GetOutputHeight() - 30), ancho, 18);
        renderer.SetDrawColor(this->colores[elemento.first]); 
        renderer.FillRect(contenedor);

        offset -= OFFSET_VIDAS_TOTALES;
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

/******************** CONVERSIONES ********************/

float Partida::metros_a_pixeles(float metros)
{
    return metros * RELACION_METRO_PIXEL;
}

float Partida::centimetros_a_metros(float centimetros)
{
    return centimetros / RELACION_CENTIMETRO_METRO;
}

float Partida::pixeles_a_metros(float pixeles)
{
    return pixeles / RELACION_METRO_PIXEL;
}

float Partida::metros_a_centimetros(float metros)
{
    return metros * RELACION_CENTIMETRO_METRO;
}

/******************** MEMORIA ********************/

void Partida::liberar_memoria()
{
    for (int i = 0; i < (int)this->worms.size(); i++)
    {
        AnimacionWorm *worm = this->worms[i];
        delete worm;
    }
}

/******************** INICIALIZADO DE TEXTURAS Y SONIDO ********************/

void Partida::inicializar_texturas(SDL2pp::Renderer &renderer) {
    this->texturas[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/background.png").SetColorKey(true, 0));
    this->texturas[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/blue00.png").SetColorKey(true, 0));
    this->texturas[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grdl4.png").SetColorKey(true, 0));
    this->texturas[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grds4.png").SetColorKey(true, 0));

    /* WORM */
    this->texturas[4] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/worm_walk.png").SetColorKey(true, 0));
    this->texturas[5] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wfall.png").SetColorKey(true, 0));
    this->texturas[6] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wflylnk.png").SetColorKey(true, 0));
    this->texturas[7] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbackflp.png").SetColorKey(true, 0));
    this->texturas[8] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wfly1.png").SetColorKey(true, 0));
    this->texturas[9] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grave1.png").SetColorKey(true, 0));

    /* EQUIPADO */
    this->texturas[10] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0));
    this->texturas[11] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wgrnlnk.png").SetColorKey(true, 0));
    this->texturas[12] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbazlnk.png").SetColorKey(true, 0));
    this->texturas[13] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbanlnk.png").SetColorKey(true, 0));
    this->texturas[14] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/whgrlnk.png").SetColorKey(true, 0));
    this->texturas[15] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wdynlnk.png").SetColorKey(true, 0));
    this->texturas[16] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wtellnk.png").SetColorKey(true, 0));
    this->texturas[17] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wairlnk.png").SetColorKey(true, 0));
    this->texturas[18] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wclslnk.png").SetColorKey(true, 0));
    this->texturas[19] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbazlnk.png").SetColorKey(true, 0));

    /* EXPLOSION */
    this->texturas[20] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));
    this->texturas[21] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/expow.png").SetColorKey(true, 0));
    this->texturas[22] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exfoom.png").SetColorKey(true, 0));

    /* MOVIMIENTO */
    this->texturas[22] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grenade.png").SetColorKey(true, 0));
    this->texturas[23] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/missile.png").SetColorKey(true, 0));
    this->texturas[24] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/banana.png").SetColorKey(true, 0));
    this->texturas[25] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/hgrenade.png").SetColorKey(true, 0));
    this->texturas[26] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/dynamite.png").SetColorKey(true, 0));
    this->texturas[27] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/airmisl.png").SetColorKey(true, 0));
    this->texturas[28] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/cluster.png").SetColorKey(true, 0));
    this->texturas[29] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/mortar.png").SetColorKey(true, 0));
    this->texturas[30] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/clustlet.png").SetColorKey(true, 0));

    /* APUNTADO */
    this->texturas[31] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbsbaim.png").SetColorKey(true, 0));
    this->texturas[32] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrgrn.png").SetColorKey(true, 0));
    this->texturas[33] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbaz.png").SetColorKey(true, 0));
    this->texturas[34] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrban.png").SetColorKey(true, 0));
    this->texturas[35] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrhgr.png").SetColorKey(true, 0));
    this->texturas[36] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrcls.png").SetColorKey(true, 0));

    /* EFECTOS DE EXPLOSION */
    this->texturas[37] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0));
    this->texturas[38] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0));
    this->texturas[39] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/flame1.png").SetColorKey(true, 0));
    this->texturas[40] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/hexhaust.png").SetColorKey(true, 0));
}

void Partida::inicializar_sonidos(SDL2pp::Renderer &renderer) {
    this->sonidos[0] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/worms/YESSIR.WAV");
    this->sonidos[1] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/worms/JUMP1.WAV");
    this->sonidos[2] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/worms/BACKFLIP.WAV");
    this->sonidos[3] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/worms/DEAD1.WAV");

    this->sonidos[4] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/armas/EXPLOSION1.WAV");
    this->sonidos[5] = std::make_shared<SDL2pp::Chunk>(DATA_PATH "/sonidos/armas/HOLYGRENADE.WAV");
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
