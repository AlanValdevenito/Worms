#include "client_vista.h"
#include <unistd.h>

#define ALTO_SPRITE 60
#define ANCHO_SPRITE 60

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

#define FILAS 5
#define COLUMNAS 9

Vista::Vista(Client &cliente): cliente(cliente) {}

float Vista::convertidor(float valor)  {
	return valor * 24;
}

int Vista::iniciar() {
    // cliente.conectarse();

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

	// Load sprites image as a new texture; since there's no alpha channel
	// but we need transparency, use helper surface for which set color key
	// to color index 0 -> black background on image will be transparent on our
	// texture
	Texture sprites(renderer, Surface(DATA_PATH "/gusano_caminando_derecha.png")
			.SetColorKey(true, 0));

	// Enable alpha blending for the sprites
	sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para una viga
	Texture viga(renderer, Surface(DATA_PATH "/viga_corta.png")
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

	// Estado del juego
	//Gusano gusano = this->cliente.get_gusano();
	Worm worm(sprites, convertidor(0), convertidor(9));

	// unsigned int prev_ticks = SDL_GetTicks();

	unsigned int tiempoInicial = SDL_GetTicks(); // Tiempo transcurrido en milisegundos desde que se inicializo SDL o desde que se llamo a la funcion SDL_Init(). .Devuelve el tiempo transcurrido como un valor entero sin signo (Uint32).
	unsigned int cuentaRegresiva = 60000; // 60 segundos en milisegundos

	while (1) {
		// Timing: Calculamos la diferencie entre este y el anterior frame en milisegundos
		// unsigned int frame_ticks = SDL_GetTicks();
		// unsigned int frame_delta = frame_ticks - prev_ticks;
		// prev_ticks = frame_ticks;

		unsigned int tiempoActual = SDL_GetTicks();
		unsigned int tiempoTranscurrido = tiempoActual - tiempoInicial; 
		unsigned int tiempoRestante = cuentaRegresiva - tiempoTranscurrido;

		if (tiempoTranscurrido > cuentaRegresiva) {
			tiempoInicial = tiempoActual;
		}

        if (handleEvents(worm)) {
			return 0;
		}

		actualizar(worm, FRAME_RATE);
		renderizar(renderer, sprites, viga, background, agua, font, worm, tiempoRestante);

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		//SDL_Delay(1);
		usleep(FRAME_RATE);
	}

    return 0;
}

bool Vista::handleEvents(Worm &worm) {
	// Procesamiento de evento
	SDL_Event event;

	// REvisamos si hay algun evento pendiente en la cola de eventos de SDL y, si lo hay, lo almacenamos en la estructura event.
	while (SDL_PollEvent(&event)) {

		// Si la ventana se cierra terminamos la ejecucion
		if (event.type == SDL_QUIT) {
			return true;

		// Si se hace click ...
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {

			switch (event.button.button) {

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
		} else if (event.type == SDL_KEYDOWN) {

			switch (event.key.keysym.sym) {

			// Si se presiona la tecla "Q" o "ESC" terminamos la ejecucion
			case SDLK_ESCAPE: case SDLK_q:
				return true;

			// Si se presiona la flecha hacia la derecha el gusano se mueve hacia la derecha
			case SDLK_RIGHT: 
				worm.moveRigth();
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
		} else if (event.type == SDL_KEYUP) {

			switch (event.key.keysym.sym) {

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

void Vista::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Worm &worm, Uint32 tiempoRestante) {
	renderer.Clear();

	renderizar_mapa(renderer, viga, background, agua);

	renderizar_temporizador(renderer, font, tiempoRestante);

	worm.render(renderer);

	//renderizar_nombre(renderer, font, animacion);
	//renderizar_vida(renderer, font, animacion);

	//renderizar_informacion(renderer, font, animacion);

	renderer.Present();
}

void Vista::renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua) {
	//int vcenter = renderer.GetOutputHeight() / 2;

	/*renderer.Copy(background, NullOpt, NullOpt);
	renderer.Copy(agua, NullOpt, NullOpt);

	Dto *vigas;
	Queue<Dto *> queue = cliente.recv_queue;

	while (queue.try_pop(vigas)) {

		float x = vigaa->x_pos();
		float y = vigaa->y_pos();
		float ancho = vigaa->return_ancho();
		float alto = vigaa->return_alto();

		renderer.Copy(
			viga,
			Rect(0, 0, 50, 50),
			Rect(convertidor(x / 100), convertidor(y / 100), convertidor(ancho / 100), convertidor(alto / 100))
		);
	}*/

	/****************************************************************************************************************/

	Dto *vigaa;
	bool booleano = cliente.recv_queue.try_pop(vigaa);

	if (booleano) {
		float x = vigaa->x_pos() / 100;
		float y = vigaa->y_pos() / 100;
		float ancho = vigaa->return_ancho();
		float alto = vigaa->return_alto();

		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << ancho / 100 << std::endl;
		std::cout << alto / 100 << std::endl;

		renderer.Copy(
			viga,
			Rect(0, 0, 50, 50),
			Rect(convertidor(x), convertidor(y), convertidor(ancho / 100), convertidor(alto / 100))
		);
	
	} else {
		renderer.Copy(
			viga,
			Rect(0, 0, 50, 50),
			Rect(convertidor(0), convertidor(9), convertidor(6), convertidor(0.8))
		);
	}

	/****************************************************************************************************************/

	/*std::vector<Viga> listado_vigas = this->cliente.get_vigas();

	for (int i = 0; i < listado_vigas.size(); i++) {
		renderer.Copy(
				viga,
				Rect(0, 0, 50, 50),
				Rect(convertidor(listado_vigas[i].x), convertidor(listado_vigas[i].y), convertidor(listado_vigas[i].ancho), convertidor(listado_vigas[i].alto))
			);
	}*/
}

void Vista::renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante) {
	Rect borde(5, 438, 65, 36);
	Color blanco(255, 255, 255, 255);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	Rect contenedor(7, 440, 61, 32);
	Color negro(0,0,0,255);
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

/*void Vista::renderizar_informacion(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion) {
	std::string texto = obtener_texto(animacion);

	Texture text_sprite(
			renderer,
			font.RenderText_Blended(texto, SDL_Color{255, 255, 255, 255})
		);

	renderer.Copy(text_sprite, NullOpt, Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));
}*/

void Vista::actualizar(Worm &worm, float dt) {
	worm.update(dt);
}

/*std::string Vista::obtener_texto(Animacion &animacion) {
	std::string text = "Gusano (" + std::to_string((int)animacion.gusano.x) + ", " + std::to_string((int)animacion.gusano.x) + ") - Running: " + (animacion.gusano_moviendose ? "true" : "false");
	return text;
}*/
