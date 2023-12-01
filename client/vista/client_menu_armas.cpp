#include "client_menu_armas.h"

MenuArmas::MenuArmas(SDL2pp::Renderer &renderer): abierto(false), fuente(DATA_PATH "/Vera.ttf", 18) {
    this->armas[0] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/baseball.1.png")));
    this->armas[1] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/grenade.1.png")));
    this->armas[2] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/bazooka.1.png")));
    this->armas[3] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/banana.1.png")));
    this->armas[4] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/hgrenade.1.png")));
    this->armas[5] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/dynamite.1.png")));
    this->armas[6] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/teleport.1.png")));
    this->armas[7] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/airstrke.1.png")));
    this->armas[8] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/cluster.1.png")));
    this->armas[9] = std::make_shared<SDL2pp::Texture>(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/armas/mortar.1.png")));
}

void MenuArmas::render(SDL2pp::Renderer &renderer) {

    if (not this->abierto) {
        return;
    }

    SDL2pp::Color blanco(255, 255, 255, 255); 
    SDL2pp::Color negro(0, 0, 0, 255);

    int cantidad_armas = this->armas.size();

    float ancho = this->armas[0]->GetWidth() * 1.3f;
    float alto = this->armas[0]->GetHeight() * 1.3f;

    float offset = (renderer.GetOutputHeight()/2) - (ancho * (cantidad_armas/2));
    for (int i = 0; i < cantidad_armas; i++) {

        /***** FONDO *****/

        SDL2pp::Rect fondo(renderer.GetOutputWidth() - (ancho*2) - 24, offset, (ancho*2) + 6, alto + 4);
        renderer.SetDrawColor(blanco);
        renderer.FillRect(fondo);

        /***** ARMAS *****/

        renderer.Copy(
            *this->armas[i],
            SDL2pp::NullOpt,
            SDL2pp::Rect(renderer.GetOutputWidth() - ancho - 20, offset + 2, ancho, alto)
        );

        /***** TECLAS *****/

        SDL2pp::Rect contenedor(renderer.GetOutputWidth() - (ancho*2) - 22, offset + 2, ancho, alto);
        renderer.SetDrawColor(negro);
        renderer.FillRect(contenedor);

        std::string textoTecla = "F" + std::to_string(i+1);
        SDL2pp::Surface surface = this->fuente.RenderText_Solid(textoTecla, blanco);
        SDL2pp::Texture texture(renderer, surface);

        SDL2pp::Rect tecla(renderer.GetOutputWidth() - (ancho*2) - 22, 20 + offset, ancho/2, alto/2);
        renderer.Copy(texture, SDL2pp::NullOpt, tecla);

        offset += (ancho);
    }
}

void MenuArmas::abrirMenu() {
    if (this->abierto) {
        this->abierto = false;
    } else {
        this->abierto = true;
    }
}
