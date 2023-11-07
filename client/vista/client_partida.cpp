#include "client_partida.h"
#include <unistd.h>
#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Partida::Partida(Client &cliente) : cliente(cliente) {}

int Partida::iniciar()
{
    /******************** INICIAR SDL ********************/

    SDL sdl(SDL_INIT_VIDEO);

    SDLTTF ttf;

    std::string titulo = "Worms 2D - [" + std::to_string(cliente.id) + "]";

    Window window(titulo,
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  ANCHO_VENTANA, ALTO_VENTANA,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    /******************** TEXTURAS ********************/

    // Cargamos la imagen para un worm
    Texture sprites(renderer, Surface(DATA_PATH "/worm_walk.png").SetColorKey(true, 0));

    sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la imagen para un arma
    Texture arma(renderer, Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0));

    arma.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la imagen para un worm
    Texture potencia(renderer, Surface(DATA_PATH "/potencia.png").SetColorKey(true, 0));

    potencia.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la imagen para una viga
    Texture viga(renderer, Surface(DATA_PATH "/grdl4.png")
                               .SetColorKey(true, 0xff));

    viga.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la imagen para el fondo
    Texture background(renderer, Surface(DATA_PATH "/background.png")
                                     .SetColorKey(true, 0xff));

    background.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la imagen para el agua
    Texture agua(renderer, Surface(DATA_PATH "/agua.png")
                               .SetColorKey(true, 0xff));

    agua.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la fuente de la letra
    Font font(DATA_PATH "/Vera.ttf", 12);

    /******************** GUARDAR ESTADO DEL JUEGO ********************/

    guardar_vigas();
    guardar_worms(renderer, sprites, arma, potencia);

    /******************** GAME LOOP ********************/

    unsigned int tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).
    unsigned int cuentaRegresiva = 60000;        // 60 segundos en milisegundos

    auto t1 = SDL_GetTicks();
    int it = 0;            // Registro del numero de iteraciones
    auto rate = 1000 / 30; // El tiempo entre cada iteracion sera de '1000 / 30' milisegundos. Como 'rate' es igual a '1000 / 30' quiere
                           // decir que la velocidad entre iteraciones sera de 30 veces por segundo

    while (true)
    {
        t1 = SDL_GetTicks(); // Inicializamos 't1' con el tiempo actual en milisegundos

        unsigned int tiempoActual = SDL_GetTicks();
        unsigned int tiempoTranscurrido = tiempoActual - tiempoInicial;
        unsigned int tiempoRestante = cuentaRegresiva - tiempoTranscurrido;

        if (tiempoTranscurrido > cuentaRegresiva)
        {
            tiempoInicial = tiempoActual;
        }

        if (handleEvents(renderer, arma))
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

        // actualizar(renderer, it);
        renderizar(renderer, viga, background, agua, font, tiempoRestante);

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

void Partida::guardar_worms(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &arma, SDL2pp::Texture &potencia)
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
        this->worms[gusano->get_id()] = new Worm(sprites, arma, potencia, metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), nuevoY, (int) gusano->get_vida());
    }

    // delete dto;
}

bool Partida::handleEvents(SDL2pp::Renderer &renderer, SDL2pp::Texture &arma)
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
                // ...
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
                    arma.Update(NullOpt, Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0));
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
                    arma.Update(NullOpt, Surface(DATA_PATH "/wbsbbk2.png").SetColorKey(true, 0));
                    cliente.send_queue.push(std::make_shared<Batear>(this->cliente.id, 0));
                    this->worms[this->id_gusano_actual]->desequipar_arma();
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

void Partida::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Uint32 tiempoRestante)
{
    renderer.Clear();

    renderizar_mapa(renderer, viga, background, agua);
    renderizar_temporizador(renderer, font, tiempoRestante);
    renderizar_worms(renderer);

    // renderizar_nombre(renderer, font, animacion);

    renderer.Present();
}

void Partida::renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua)
{

    renderer.Copy(background, NullOpt, NullOpt);
    renderer.Copy(agua, NullOpt, NullOpt);

    float altura = renderer.GetOutputHeight();

    for (int i = 0; i < (int)this->vigas.size(); i++)
    {
        // Debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
        // tienen el (0,0) de los cuerpos en el centro y ademas el (0,0) del mapa se ubica 
        // en la esquina inferior izquierda y no en la esquina superior izquierda como ocurre en SDL
        float x = this->vigas[i]->x_pos() - (this->vigas[i]->return_ancho() / 2);
        float y = this->vigas[i]->y_pos();
        float ancho = this->vigas[i]->return_ancho();
        float alto = this->vigas[i]->return_alto();
        float angulo = -(this->vigas[i]->return_angulo());

        renderer.Copy(
            viga,
            Rect(0, 0, 50, 50),
            Rect(metros_a_pixeles(centimetros_a_metros(x)), altura - metros_a_pixeles(centimetros_a_metros(y)),
                 metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))), angulo);
    }
}

void Partida::renderizar_worms(SDL2pp::Renderer &renderer)
{
    for (const auto &elemento : this->worms)
    {
        elemento.second->render(renderer);
    }
}

void Partida::renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante)
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

    int tiempo = tiempoRestante * 0.001;
    Surface surface = font.RenderText_Solid(std::to_string(tiempo), blanco);
    Texture texture(renderer, surface);

    Rect nombre(24, altura - 34, surface.GetWidth() + 5, surface.GetHeight() + 5);
    renderer.Copy(texture, NullOpt, nombre);
}

/*void Partida::renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion) {
    int vcenter = renderer.GetOutputHeight() / 2;

    Rect borde((int)animacion.gusano.x + 6, vcenter - 77, 50, 21);
    Color blanco(255, 255, 255, 255);
    renderer.SetDrawColor(blanco);
    renderer.FillRect(borde);

    Rect contenedor((int)animacion.gusano.x + 8, vcenter - 75, 46, 17);
    Color negro(0,0,0,255);
    renderer.SetDrawColor(negro);
    renderer.FillRect(contenedor);

    Surface surface = font.RenderText_Solid(animacion.gusano.nombre, blanco);
    Texture texture(renderer, surface);

    Rect nombre((int)animacion.gusano.x + 18, vcenter - 75, surface.GetWidth(), surface.GetHeight());
    renderer.Copy(texture, NullOpt, nombre);
}*/

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

        // Necesito un booleano que me indique que el Worm dejo de moverse luego de que su vida llego a 0.
        // Esto porque no necesariamente que un gusano tenga vida igual a 0 implica que haya que dejar de renderizarlo.
        // Desde la vista se debe renderizar y mostrar toda la animacion aun cuando el Worm tenga vida igual a 0.
        // Luego de que termino la animacion del Worm es cuando se deja de renderizar. Esto implica que se elimina del diccionario.
        /*if (gusano->delete()) {
            this->worms.erase(gusano->get_id());
            continue;
        }*/

        float nuevoY = altura - metros_a_pixeles(centimetros_a_metros((int)gusano->y_pos()));
        this->worms[gusano->get_id()]->update(it, metros_a_pixeles(centimetros_a_metros((int)gusano->x_pos())), nuevoY, (int)gusano->get_vida());
    }

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
