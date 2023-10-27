#include "client_vista.h"
#include <unistd.h>

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Vista::Vista(Client &cliente) : cliente(cliente) {}

int Vista::iniciar()
{
	// Inicializamos la libreria SDL
	SDL sdl(SDL_INIT_VIDEO);

	// Inicializamos la libreria SDL_ttf
	SDLTTF ttf;

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	// Creamos la ventana main: Dimensiones de 640x480, Redimensionable, Titulo de la ventana "Worms 2D"
	Window window("Worms 2D",
				  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				  ANCHO_VENTANA, ALTO_VENTANA,
				  SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	/******************** TEXTURAS ********************/

	// Load sprites image as a new texture; since there's no alpha channel
	// but we need transparency, use helper surface for which set color key
	// to color index 0 -> black background on image will be transparent on our
	// texture
	Texture sprites(renderer, Surface(DATA_PATH "/worm_walk.png")
								  .SetColorKey(true, 0));

	// Enable alpha blending for the sprites
	sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para una viga
	Texture viga(renderer, Surface(DATA_PATH "/viga_larga.png")
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

	// Cargamos la fuente de la letra y le ajustamos un tamaño de 12 pt
	Font font(DATA_PATH "/Vera.ttf", 12);

	/******************** ESTADO DEL JUEGO ********************/

	guardar_vigas();

	Dto *gusano = cliente.recv_queue.pop();
	Worm worm(sprites, metros_a_pixeles(centimetros_a_metros(gusano->x_pos())), metros_a_pixeles(centimetros_a_metros(gusano->y_pos())));

	/******************** GAME LOOP ********************/

	unsigned int tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).
	unsigned int cuentaRegresiva = 60000;		 // 60 segundos en milisegundos

	while (1)
	{
		unsigned int tiempoActual = SDL_GetTicks();
		unsigned int tiempoTranscurrido = tiempoActual - tiempoInicial;
		unsigned int tiempoRestante = cuentaRegresiva - tiempoTranscurrido;

		if (tiempoTranscurrido > cuentaRegresiva)
		{
			tiempoInicial = tiempoActual;
				}

		if (handleEvents(worm))
		{
			return 0;
		}

		actualizar(worm, FRAME_RATE);
		renderizar(renderer, viga, background, agua, font, worm, tiempoRestante);

		usleep(FRAME_RATE);
	}

	return 0;
}

void Vista::guardar_vigas()
{
	Dto *dto = cliente.recv_queue.pop();

	for (int i = 0; i < dto->cantidad(); i++)
	{
		Viga *viga = (Viga *)dto->popViga();
		this->vigas.push_back(viga); // Liberar memoria de las vigas cuando se sale de la vista
	}
}

bool Vista::handleEvents(Worm &worm)
{
	// Procesamiento de evento
	SDL_Event event;

	// REvisamos si hay algun evento pendiente en la cola de eventos de SDL y, si lo hay, lo almacenamos en la estructura event.
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
				// worm.moveRigth();
				// Dto *d = new Mover();
				// cliente.send_queue.push(d);
				break;

			// Si se presiona la flecha hacia la izquierda el gusano se mueve hacia la izquierda
			case SDLK_LEFT:
				worm.moveLeft();
				break;

			// Si se presiona la flecha hacia ariba el gusano direcciona su arma
			case SDLK_UP:
				// ...
				break;

			// Si se presiona la flecha hacia abajo el gusano direcciona su arma
			case SDLK_DOWN:
				// ...
				break;

			// Si se presiona la tecla de enter el gusano salta hacia adelante
			case SDLK_RETURN:
				// ...
				break;

			// Si se presiona la tecla de espacio disparamos o aumentamos la potencia del disparo
			case SDLK_SPACE:
				// ...
				break;

			// Si se presiona la tecla de retroceso el gusano cambia su direccion (se da la vuelta)
			case SDLK_BACKSPACE:
				// ...
				break;

			// Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
			case SDLK_0:
				// ...
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
				worm.stopMoving();
				break;

			// Si se suelta la flecha hacia la izquierda cambiamos el estado del gusano
			case SDLK_LEFT:
				worm.stopMoving();
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
				// ...
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

void Vista::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Worm &worm, Uint32 tiempoRestante)
{
	renderer.Clear();

	renderizar_mapa(renderer, viga, background, agua);

	renderizar_temporizador(renderer, font, tiempoRestante);

	worm.render(renderer);

	// renderizar_nombre(renderer, font, animacion);
	// renderizar_vida(renderer, font, animacion);

	renderer.Present();
}

void Vista::renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua)
{

	renderer.Copy(background, NullOpt, NullOpt);
	renderer.Copy(agua, NullOpt, NullOpt);

	for (int i = 0; i < (int)this->vigas.size(); i++)
	{

		float x = this->vigas[i]->x_pos();
		float y = this->vigas[i]->y_pos();
		float ancho = this->vigas[i]->return_ancho();
		float alto = this->vigas[i]->return_alto();

		renderer.Copy(
			viga,
			Rect(0, 0, 50, 50),
			Rect(metros_a_pixeles(centimetros_a_metros(x)), metros_a_pixeles(centimetros_a_metros(y)),
				 metros_a_pixeles(centimetros_a_metros(ancho)), metros_a_pixeles(centimetros_a_metros(alto))));
	}
}

void Vista::renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante)
{
	Rect borde(5, 438, 65, 36);
	Color blanco(255, 255, 255, 255);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	Rect contenedor(7, 440, 61, 32);
	Color negro(0, 0, 0, 255);
	renderer.SetDrawColor(negro);
	renderer.FillRect(contenedor);

	int tiempo = tiempoRestante * 0.001;
	Surface surface = font.RenderText_Solid(std::to_string(tiempo), blanco);
	Texture texture(renderer, surface);

	Rect nombre(24, 446, surface.GetWidth() + 5, surface.GetHeight() + 5);
	renderer.Copy(texture, NullOpt, nombre);
}

/*void Vista::renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion) {
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

/*void Vista::renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion) {
	int vcenter = renderer.GetOutputHeight() / 2;

	Rect borde((int)animacion.gusano.x + 16, vcenter - 52, 29, 21);
	Color blanco(255, 255, 255, 255);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	Rect contenedor((int)animacion.gusano.x + 18, vcenter - 50, 25, 17);
	Color negro(0,0,0,255);
	renderer.SetDrawColor(negro);
	renderer.FillRect(contenedor);

	Surface surface = font.RenderText_Solid(std::to_string(animacion.gusano.vida), blanco);
	Texture texture(renderer, surface);

	Rect vida((int)animacion.gusano.x + 18, vcenter - 50, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, NullOpt, vida);
}*/

void Vista::actualizar(Worm &worm, float dt)
{
	worm.update(dt);
}

float Vista::metros_a_pixeles(float metros)
{
	return metros * 24;
}

float Vista::centimetros_a_metros(float centimetros)
{
	return centimetros / 100;
}
