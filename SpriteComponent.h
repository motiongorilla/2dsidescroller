#pragma once

#include "Actor.h"
#include "Component.h"
#include <SDL3/SDL_render.h>

class SpriteComponent : public Component {
public:
    // lower draw order -> further back
    SpriteComponent(Actor* owner, int draw_order = 100);
    virtual ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const {return draw_order_;}
    int GetTexHeight() const {return texture_height_;}
    int GetTexWidth() const {return texture_width_;}

protected:
    SDL_Texture* texture_;
    int draw_order_;
    int texture_width_;
    int texture_height_;
};
