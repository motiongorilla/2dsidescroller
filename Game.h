#pragma once

#include "Actor.h"
#include "SpriteComponent.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <vector>

class Game {
public:
    Game();

    bool Initialize();
    void Shutdown();
    void Run();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

private:
    void ProcessInput();
    void UpdateData();
    void Render();

    void RenderBackground(SDL_Renderer* renderer);
    void RenderForeground(SDL_Renderer* renderer);

    SDL_Texture* LoadTexture(const char* filepath);
    SDL_Texture* GetTexture(char* texture_path);

    void LoadData();
public:
    bool is_running_;
    bool updating_actors_;

    int tick_number_;
    int win_width_;
    int win_height_;

    SDL_Window* game_window_;
    SDL_Renderer* game_render_;

    std::vector<Actor*> actors_;
    std::vector<Actor*> actors_pending_;

    std::vector<SpriteComponent*> sprites_;

    std::map<const char*, SDL_Texture*> textures_;
};
