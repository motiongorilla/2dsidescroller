#include "Game.h"

#include <algorithm>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_timer.h>

Game::Game() {
    game_window_ = nullptr;
    is_running_ = true;
    tick_number_ = 0;
}

bool Game::Initialize() {
    bool sdl_init = SDL_Init(SDL_INIT_VIDEO);

    if(!sdl_init) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode* displayData = SDL_GetDesktopDisplayMode(display_id);

    game_window_ = SDL_CreateWindow("Hybrid architecture game", 1024, 1024, SDL_WINDOW_RESIZABLE);

    if(!game_window_) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
    }

    game_render_ = SDL_CreateRenderer(game_window_, NULL);
    SDL_SetRenderVSync(game_render_, 1);

    return true;
}

void Game::Run() {
    while(is_running_) {
        ProcessInput();
        UpdateData();
        Render();
    }
}

void Game::Shutdown() {
    while(!actors_.empty()) {
        delete actors_.back();
        actors_.pop_back();
    }

    while(!actors_pending_.empty()) {
        delete actors_pending_.back();
        actors_pending_.pop_back();
    }

    SDL_DestroyWindow(game_window_);
    SDL_DestroyRenderer(game_render_);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_EVENT_QUIT:
                is_running_ = false;
                break;
        }
    }

    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        is_running_ = false;
    }
}

void Game::UpdateData() {
    float delta_time = (SDL_GetTicks() - tick_number_) / 1000.f;

    tick_number_ = SDL_GetTicks();

    if (delta_time > 0.05f) {
        delta_time = 0.05f;
    }

    // Update all actors
    updating_actors_ = true;
    for (Actor* actor : actors_) {
        actor->Update(delta_time);
    }
    updating_actors_ = false;

    // Move pending actors to live actors
    for (Actor* pending : actors_pending_) {
        actors_.emplace_back(pending);
    }
    actors_pending_.clear();

    std::vector<Actor*> dead_actors;

    for (Actor* actor : actors_) {
        if (actor->GetState() == Actor::State::Dead) {
            dead_actors.emplace_back(actor);
        }
    }

    // delete dead actors which removes them from Game::actors_
    for (Actor* actor : dead_actors) {
        RemoveActor(actor);
        delete actor;
    }
}

void Game::Render() {
    // background
    SDL_SetRenderDrawColor(game_render_, 0, 50, 25, 255);

    // clearing back buffer
    SDL_RenderClear(game_render_);

    RenderForeground();

    // swapping back to front
    SDL_RenderPresent(game_render_);
}

void Game::AddActor(Actor* actor) {
    if (updating_actors_) {
        actors_pending_.emplace_back(actor);
    } else {
        actors_.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    auto it = find(actors_.begin(), actors_.end(), actor);

    if(it != actors_.end()) {
        actors_.erase(it);
        return;
    }

    auto pit = find(actors_pending_.begin(), actors_pending_.end(), actor);

    if(pit != actors_pending_.end()) {
        actors_pending_.erase(pit);
        return;
    }
}

void Game::RenderForeground() {

}

SDL_Texture* Game::LoadTexture(const char* filepath) {
    SDL_Surface* img_surface = IMG_Load(filepath);
    if(!img_surface) {
        SDL_Log("Failed to load texture file %s", filepath);
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game_render_, img_surface);
    SDL_DestroySurface(img_surface);
    if (!texture) {
        SDL_Log("Failed to convert surface to texture for %s", filepath);
        return nullptr;
    }
    return texture;
}

SDL_Texture* Game::GetTexture(char* texture_path) {
    SDL_Texture* requested_texture = textures_.at(texture_path);
    if(!requested_texture) {
        SDL_Texture* new_texture = LoadTexture(texture_path);
        textures_.insert({texture_path, new_texture});
        requested_texture = new_texture;
    }

    return requested_texture;

}

void Game::AddSprite(SpriteComponent* sprite) {
    // find insertion point in the sorted vector
    int sprite_draw_order = sprite->GetDrawOrder();

    auto iter = sprites_.begin();
    for (; iter != sprites_.end(); ++iter) {
         if (sprite_draw_order < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    sprites_.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    auto it = find(sprites_.begin(), sprites_.end(), sprite);

    if(it != sprites_.end()) {
        sprites_.erase(it);
        return;
    }
}
