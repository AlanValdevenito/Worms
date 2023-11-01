#include "client_menu.h"
#include <unistd.h>

#define ALTO_VENTANA 480
#define ANCHO_VENTANA 640

#define OFFSET_BOTON 50

Menu::Menu(Client &cliente) : cliente(cliente)  {}

int Menu::iniciar() 
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

    // Cargamos la imagen para el fondo
	Texture background(renderer, Surface(DATA_PATH "/background1.jpg")
			.SetColorKey(true, 0));

	background.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para botones
	Texture boton(renderer, Surface(DATA_PATH "/boton.png")
			.SetColorKey(true, 0));

	boton.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la fuente de la letra y le ajustamos un tamaño de 15 pt
	Font font(DATA_PATH "/Vera.ttf", 20);

	while (true) {

        if (handleEvents()) {
			return 0;
		}

		renderizar(renderer, background, boton, font);

		SDL_Delay(1);
	}

    return 0;
}

bool Menu::handleEvents() {
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

				// Si se hace click izquierdo...
				case SDL_BUTTON_LEFT:
		
					if ((200 < event.button.x && event.button.x < 440) && (240 < event.button.y && event.button.y < 290)) {
						std::cout << "Te uniste a 'Partida 1'" << std::endl;
						return true;
					}

					break;
			}

		} else if (event.type == SDL_KEYDOWN) {

			switch (event.key.keysym.sym) {

			// Si se presiona la tecla "Q" o "ESC" terminamos la ejecucion
			case SDLK_ESCAPE: case SDLK_q:
				return true;

			// case SDLK_RETURN: 
			// 	return true;
            }
		}	
	}

	return false;
}

void Menu::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &background, SDL2pp::Texture &boton, SDL2pp::Font &font) {
	renderer.Clear();

    int x_centro = renderer.GetOutputWidth() / 2; // 340
    int y_centro = renderer.GetOutputHeight() / 2; // 240

    Rect posicionLogo(x_centro - 200, y_centro - y_centro, 400, 200);
	renderer.Copy(background, NullOpt, posicionLogo);

	/*****************************************/

	/* Boton para unirse a la primer partida */

	Rect posicionBoton(x_centro - 125, y_centro, 250, 50);
	renderer.Copy(boton, NullOpt, posicionBoton);

	Color negro(0,0,0,255);
	Surface surface = font.RenderText_Solid("Partida 1", negro);
	Texture texture(renderer, surface);

	Rect mensaje(x_centro - 125 + 75, y_centro + 10, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, NullOpt, mensaje);

	/* Boton para unirse a la segunda partida */

	Rect posicionBoton2(x_centro - 125, y_centro + OFFSET_BOTON, 250, 50);
	renderer.Copy(boton, NullOpt, posicionBoton2);

	Surface surface2 = font.RenderText_Solid("Partida 2", negro);
	Texture texture2(renderer, surface2);

	Rect mensaje2(x_centro - 125 + 75, y_centro + 10 + OFFSET_BOTON, surface2.GetWidth(), surface2.GetHeight());
	renderer.Copy(texture2, NullOpt, mensaje2);

	/*****************************************/

	renderer.Present();
}

/*void Menu::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &background, SDL2pp::Font &font) {
	renderer.Clear();

	renderer.Copy(background, NullOpt, NullOpt);

    int x_centro = renderer.GetOutputWidth() / 2;
    int y_centro = renderer.GetOutputHeight() / 2;

    int ancho = 250;
    int alto = 50;
	Rect contenedor(x_centro - 125, y_centro + 150, ancho, alto);
	Color blanco(255, 255, 255, 255);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(contenedor);

    Color negro(0,0,0,255);
	Surface surface = font.RenderText_Solid("Presione ENTER para comenzar", negro);
	Texture texture(renderer, surface);

	Rect mensaje(x_centro - 125 + 5, y_centro + 165, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, NullOpt, mensaje);

	renderer.Present();
}*/
