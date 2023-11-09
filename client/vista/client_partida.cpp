#include "client_partida.h"
#include <unistd.h>

#define TITULO "Worms 2D"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Partida::Partida(Client &cliente) : cliente(cliente), camara(ANCHO_VENTANA, ALTO_VENTANA) {}

int Partida::iniciar()
{
    /******************** INICIAR SDL ********************/

    SDL sdl(SDL_INIT_VIDEO);

    SDLTTF ttf;

    Window window(TITULO,
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  ANCHO_VENTANA, ALTO_VENTANA,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    /******************** TEXTURAS ********************/

    this->texturas[0] = new Texture(renderer, Surface(DATA_PATH "/background.png").SetColorKey(true, 0xff));
    this->texturas[1] = new Texture(renderer, Surface(DATA_PATH "/agua.png").SetColorKey(true, 0xff));
    this->texturas[2] = new Texture(renderer, Surface(DATA_PATH "/grdl4.png").SetColorKey(true, 0xff));

    // Cargamos la fuente de la letra
    Font font(DATA_PATH "/Vera.ttf", 12);

    /******************** COLORES ********************/

    std::map<int, Color> colores;

    colores[0] = SDL2pp::Color(255,0,0); // Rojo
    colores[1] = SDL2pp::Color(0,0,255); // Azul
    colores[2] = SDL2pp::Color(0,255,0); // Verde
    colores[3] = SDL2pp::Color(255,255,255); // Blanco
    colores[4] = SDL2pp::Color(0,0,0); // Negro

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, colores);

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

        renderizar(renderer, font);

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

bool Partida::handleEvents(SDL2pp::Renderer &renderer)
{
    // Procesamiento de evento
    SDL_Event event;

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
                    this->worms[this->id_gusano_actual]->aumentar_potencia();
                }

                break;

            // Si se presiona la tecla de retroceso el gusano cambia su direccion (se da la vuelta)
            case SDLK_BACKSPACE:
                // ...
                break;

            // Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
            case SDLK_0:
                // ...
                break;

            // Si se presiona la tecla de F7 el worm se equipa un arma
            case SDLK_F7:

                if (this->worms[this->id_gusano_actual]->arma_equipada()) {
                    this->worms[this->id_gusano_actual]->desequipar_arma();
                
                } else {
                    this->worms[this->id_gusano_actual]->equipar_arma();
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
                    cliente.send_queue.push(std::make_shared<Batear>(this->cliente.id, this->worms[this->id_gusano_actual]->get_angulo()));
                    this->worms[this->id_gusano_actual]->desequipar_arma();

                    this->tiempoInicial = this->tiempoActual;
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

void Partida::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Font &font)
{
    renderer.Clear();

    renderizar_mapa(renderer);
    renderizar_temporizador(renderer, font);
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

        //if (this->camara.comprobarRenderizado(centimetros_a_metros(x), centimetros_a_metros(y), ancho, alto)) {
            renderer.Copy(
                *this->texturas[2],
                Rect(0, 0, 50, 50),
                Rect(metros_a_pixeles(centimetros_a_metros(x - ancho/2) /*- this->camara.getLimiteIzquierdo()*/), altura - metros_a_pixeles(centimetros_a_metros(y)),
                metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
        //}
    }
}

void Partida::renderizar_worms(SDL2pp::Renderer &renderer)
{
    for (const auto &elemento : this->worms)
    {
        //if (this->camara.comprobarRenderizado(elemento.second->get_x(), elemento.second->get_y(), 24, 24)) {
            elemento.second->render(renderer);
        //}
    }
}

void Partida::renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font)
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

    Surface surface = font.RenderText_Solid(std::to_string((int) (this->tiempoRestante * 0.001)), blanco);
    Texture texture(renderer, surface);

    Rect nombre(24, altura - 34, surface.GetWidth() + 5, surface.GetHeight() + 5);
    renderer.Copy(texture, NullOpt, nombre);
}

bool Partida::actualizar(SDL2pp::Renderer &renderer, int it)
{
    // std::shared_ptr<Gusanos> dto = std::dynamic_pointer_cast<Gusanos>(cliente.recv_queue.pop());

    std::shared_ptr<Dto> dead = cliente.recv_queue.pop();
    
    if(not dead->is_alive())
        return false;

    std::shared_ptr<Gusanos> dto  = std::dynamic_pointer_cast<Gusanos>(dead);
    this->id_gusano_actual = dto->get_gusano_de_turno();

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

    // camara.seguirWorm(*this->worms[this->id_gusano_actual]);

    return true;
}

float Partida::metros_a_pixeles(float metros)
{
    return metros * 24;
}

float Partida::centimetros_a_metros(float centimetros)
{
    return centimetros / 100;
}

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
