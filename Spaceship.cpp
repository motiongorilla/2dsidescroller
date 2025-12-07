#include "Spaceship.h"
#include <SDL3/SDL_scancode.h>

SpaceshipActor::SpaceshipActor(Game* game) : Actor(game) {
    horiz_speed_ = 0.f;
    vert_speed_ = 0.f;
}

void SpaceshipActor::ProcessKeyboard(const bool* state) {
    horiz_speed_ = 0.f;
    vert_speed_ = 0.f;

    if (state[SDL_SCANCODE_A]){
        horiz_speed_ += -200;
    }
    if (state[SDL_SCANCODE_D]) {
        horiz_speed_ += 200;
    }
    if (state[SDL_SCANCODE_W]) {
        vert_speed_ += -200;
    }
    if (state[SDL_SCANCODE_S]) {
        vert_speed_ += 200;
    }

}

void SpaceshipActor::UpdateActor(float delta_time) {
    Actor::UpdateActor(delta_time);
    Vector2 pos = GetPosition();

    pos.x_ += horiz_speed_ * delta_time;
    pos.y_ += vert_speed_ * delta_time;

    SetPosition(pos);
}
