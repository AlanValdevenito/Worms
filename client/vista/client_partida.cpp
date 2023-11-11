#include "client_partida.h"
#include <unistd.h>

#define TITULO "Worms 2D"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Partida::Partida(Client &cliente) : cliente(cliente), fuente(DATA_PATH "/Vera.ttf", 12), camara(ANCHO_VENTANA, ALTO_VENTANA) {}

int Partida::iniciar()
{
    /******************** INICIAR SDL ********************/

    SDL sdl(SDL_INIT_VIDEO);

    Window window(TITULO,
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  ANCHO_VENTANA, ALTO_VENTANA,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    /******************** TEXTURAS Y COLORES ********************/

    inicializar_texturas(renderer);
    inicializar_colores();

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, colores);

    this->granada = new Granada(renderer);

    /******************** GAME LOOP ********************/

    this->tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).
    unsigned int cuentaRegresiva = 61000;        // 60 segundos en milisegundos

    auto t1 = SDL_GetTicks();
    int it = 0;            // Registro del numero de iteraciones
    auto rate = 1000 / 30; // El tiempo entre cada iteracion sera de '1000 / 30' milisegundos. Como 'rate' es igual a '1000 / 30' quiere
                           // decir que la velocidad entre iteraciones sera de 30 veces por segundo

    while (true)
    {
        t1 = SDL_GetTicks(); // Inicializamos 't1' con el tiempo actual en milisegundos

        this->tiempoActual = SDL_GetTicks();
        unsigned int tiempoTranscurrido = this->tiempoActual - this->tiempoInicial;
        this->tiempoRestante = cuentaRegresiva - tiempoTranscurrido;

        if (tiempoTranscurrido > cuentaRegresiva)
        {
            this->tiempoInicial = this->tiempoActual;
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
        this->worms[gusano->get_id()] = new Worm(renderer, colores[(int) gusano->get_color()], metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), nuevoY, (int) gusano->get_vida());
    }

    camara.seguirWorm(*this->worms[this->id_gusano_actual]);

    // delete dto;
}

/******************** HANDLER DE EVENTOS ********************/

bool Partida::handleEvents(SDL2pp::Renderer &renderer)
{
    // Procesamiento de evento
    SDL_Event event;

    std::string ruta;
    std::string arma = "/bazooka.1.png";

    // Revisamos si hay algun evento pendiente en la cola de eventos de SDL y, si lo hay, lo almacenamos en la estructura event.
    while (SDL_PollEvent(&event))
    {

        // Si la ventana se cierra terminamos la ejecucion
        if (event.type == SDL_QUIT)
        {
            return true;

            // Si se hace click ...
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            switch (event.button.button)
            {

            // Si se hace click derecho se muestra el menu de armas
            case SDL_BUTTON_RIGHT:
                std::cout << "Click derecho" << std::endl;
                break;

            // Si se hace click izquierdo...
            case SDL_BUTTON_LEFT:
                std::cout << "Click izquierdo" << std::endl;
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
                this->worms[this->id_gusano_actual]->mirar_derecha();

                if (not this->worms[this->id_gusano_actual]->arma_equipada()) {
                    cliente.send_queue.push(std::make_shared<MoverADerecha>(this->cliente.id));
                } 

                break;

            // Si se presiona la flecha hacia la izquierda el gusano se mueve hacia la izquierda
            case SDLK_LEFT:
                this->worms[this->id_gusano_actual]->mirar_izquierda();

                if (not this->worms[this->id_gusano_actual]->arma_equipada()) {
                    cliente.send_queue.push(std::make_shared<MoverAIzquierda>(this->cliente.id));
                } 

                break;

            // Si se presiona la flecha hacia ariba el gusano direcciona su arma
            case SDLK_UP:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->aumentar_angulo();
                }

                break;

            // Si se presiona la flecha hacia abajo el gusano direcciona su arma
            case SDLK_DOWN:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->decrementar_angulo();
                }

                break;

            // Si se presiona la tecla de enter el gusano salta hacia adelante
            case SDLK_RETURN:
                
                if (not this->worms[this->id_gusano_actual]->arma_equipada()) {
                    cliente.send_queue.push(std::make_shared<Saltar>(this->cliente.id));
                } 
                
                break;

            // Si se presiona la tecla de espacio disparamos o aumentamos la potencia del disparo
            case SDLK_SPACE:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->granada->cambiar(arma);
                    this->worms[this->id_gusano_actual]->aumentar_potencia();
                }

                break;

            // Si se presiona la tecla de retroceso el gusano cambia su direccion (se da la vuelta)
            case SDLK_BACKSPACE:
                // ...
                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_1:
                
                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->granada->set_tiempo(1);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_2:
                
                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->granada->set_tiempo(2);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_3:
                
                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->granada->set_tiempo(3);
                }

                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_4:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->granada->set_tiempo(4);
                }

                break;

            // Si se presiona la tecla de F1 el worm se equipa un arma
            case SDLK_F1:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->desequipar_arma();
                
                } else {
                    ruta = "/wbazlnk.png";
                    arma = "/bazooka.1.png";
                    this->worms[this->id_gusano_actual]->equipar_arma(BAZOOKA, ruta);
                }

                break;

            // Si se presiona la tecla de F2 el worm se equipa un arma
            case SDLK_F2:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->desequipar_arma();
                
                } else {
                    ruta = "/wgrnlnk.png";
                    arma = "/grenade.1.png";
                    this->worms[this->id_gusano_actual]->equipar_arma(GRANADA_VERDE, ruta);
                }

                break;

            // Si se presiona la tecla de F7 el worm se equipa un arma
            case SDLK_F7:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->desequipar_arma();
                
                } else {
                    ruta = "/wbsblnk.png";
                    arma = "/baseball.1.png";
                    this->worms[this->id_gusano_actual]->equipar_arma(BATE, ruta);
                }

                break;
            }

            // Si se suelta alguna tecla...
        }
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

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    enviarAtaque();
                    this->worms[this->id_gusano_actual]->desequipar_arma();
                    this->tiempoInicial = this->tiempoActual;

                    this->granada->update(320, this->worms[this->id_gusano_actual]->get_y());
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
        this->granada->lanzarGranada();
        cliente.send_queue.push(std::make_shared<GranadaVerde>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo(),
                                                               this->granada->get_tiempo()));
    
    } else if (armaEquipada == BAZOOKA) {
        this->granada->lanzarGranada();
        cliente.send_queue.push(std::make_shared<Bazuka>(this->cliente.id, this->worms[this->id_gusano_actual]->get_potencia(),
                                                               this->worms[this->id_gusano_actual]->get_angulo()));
    } else {
        std::cerr << "El numero recibido no esta asociado a ningun arma\n";
    }
}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

bool Partida::actualizar(SDL2pp::Renderer &renderer, int it)
{
    // std::shared_ptr<Gusanos> dto = std::dynamic_pointer_cast<Gusanos>(cliente.recv_queue.pop());
    std::shared_ptr<Dto> dead = cliente.recv_queue.pop();
    
    if(not dead->is_alive())
        return false;

    std::shared_ptr<Gusanos> dto  = std::dynamic_pointer_cast<Gusanos>(dead);

    int id_gusano_siguiente = dto->get_gusano_de_turno();

    if (id_gusano_siguiente != this->id_gusano_actual) {
        this->worms[this->id_gusano_actual]->cambiar_turno(); // Le aviso al Worm del turno anterior que ya no es mas su turno
        this->id_gusano_actual = id_gusano_siguiente;
        this->worms[this->id_gusano_actual]->turno_actual(); // Le aviso al Worm del turno actual que es su turno
    
    } else {
        this->id_gusano_actual = id_gusano_siguiente;
        this->worms[this->id_gusano_actual]->turno_actual(); // Le aviso al Worm del turno actual que es su turno
    }

    float altura = renderer.GetOutputHeight();

    // Creamos la variable cantidad porque si incluimos en el for directamente 'dto->cantidad()' no iteraremos todos
    // los worms ya que estamos haciendo pop y en cada iteracion disminuye la cantidad de elemtentos en la lista
    int cantidad = dto->cantidad();
    for (int i = 0; i < cantidad; i++)
    {
        std::shared_ptr<Gusano> gusano = dto->popGusano(i);

        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        this->worms[gusano->get_id()]->update(it, metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos())), nuevoY, (int)gusano->get_vida());
    }

    this->granada->set_flag((int) dto->get_flag_proyectil());
    if (this->granada->get_flag()) {
        std::shared_ptr<Proyectil> proyectil = std::dynamic_pointer_cast<Proyectil>(cliente.recv_queue.pop());
        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)proyectil->y_pos()));
        this->granada->update(metros_a_pixeles(centimetros_a_metros((int)proyectil->x_pos())), nuevoY);

        // if(proyectil->return_code() == BAZUKA_CODE){
        //     std::shared_ptr<Bazuka> bazooka = std::dynamic_pointer_cast<Bazuka>(proyectil);
        //     float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)bazooka->y_pos()));
        //     this->bazooka->update(metros_a_pixeles(centimetros_a_metros((int)bazooka->x_pos())), nuevoY);
        // }

        // else{
        //     std::shared_ptr<GranadaVerde> granada = std::dynamic_pointer_cast<GranadaVerde>(proyectil);
        //     float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)granada->y_pos()));
        //     this->granada->update(metros_a_pixeles(centimetros_a_metros((int)granada->x_pos())), nuevoY);
        // }
        
    }

    camara.seguirWorm(*this->worms[this->id_gusano_actual]);

    return true;
}

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

        if (this->camara.comprobarRenderizado(centimetros_a_metros(x), centimetros_a_metros(y), ancho, alto)) {
            renderer.Copy(
                *this->texturas[2],
                Rect(0, 0, 50, 50),
                Rect(metros_a_pixeles(centimetros_a_metros(x - ancho/2) - this->camara.getLimiteIzquierdo()), altura - metros_a_pixeles(centimetros_a_metros(y - alto/2)),
                metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
        }
    }

    if((this->camara.comprobarRenderizado(this->granada->get_x() / 24, this->granada->get_y() / 24, 1, 1)) && (this->granada->seLanzoGranada())) {

        if (this->granada->get_flag() == 1) {
            this->granada->render(renderer, this->camara.getLimiteIzquierdo() * 24);

        } else if (this->granada->get_flag() == 0) {
            this->granada->explotar(renderer, this->camara.getLimiteIzquierdo() * 24);
        }

    }
}

void Partida::renderizar_worms(SDL2pp::Renderer &renderer)
{
    for (const auto &elemento : this->worms)
    {

        if (elemento.first == this->id_gusano_actual) {
            elemento.second->render(renderer);
        
        } else if (this->camara.comprobarRenderizado(elemento.second->get_x() / 24, elemento.second->get_y() / 24, 1, 1)) {
            elemento.second->render_camara(renderer, this->camara.getLimiteIzquierdo() * 24);
        }
    }
}

void Partida::renderizar_temporizador(SDL2pp::Renderer &renderer)
{
    int altura = renderer.GetOutputHeight(); // 480

    Rect borde(5, altura - 42, 65, 36);
    Color blanco(255, 255, 255, 255);
    renderer.SetDrawColor(blanco);
    renderer.FillRect(borde);

    Rect contenedor(7, altura - 40, 61, 32);
    Color negro(0, 0, 0, 255);
    renderer.SetDrawColor(negro);
    renderer.FillRect(contenedor);

    Surface surface = this->fuente.RenderText_Solid(std::to_string((int) (this->tiempoRestante * 0.001)), blanco);
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
