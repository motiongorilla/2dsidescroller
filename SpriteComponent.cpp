#include "Game.h"
#include "SpriteComponent.h"

#include <numbers>
#include <SDL3/SDL_rect.h>

SpriteComponent::SpriteComponent(Actor* owner, int draw_order) : Component(owner, draw_order) {
    draw_order_ = draw_order;
    owner_ = owner;
    owner->GetGameRef()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner_->GetGameRef()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture) {
    texture_ = texture;

    //get width & height of texture
    texture_height_ = texture_->h;
    texture_width_ = texture_->w;
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (texture_) {
        SDL_FRect r;
        // scale width and hight by owners scale
        r.w = static_cast<int>(texture_width_ * owner_->GetScale());
        r.h = static_cast<int>(texture_height_ * owner_->GetScale());

        // center rect from the position of the owning actor
        r.x = static_cast<int>(owner_->GetPosition().x_ - static_cast<float>(r.w)/2.f);
        r.y = static_cast<int>(owner_->GetPosition().y_ - static_cast<float>(r.h)/2.f);

        // Draw
        double rotation_amount = static_cast<double>(owner_->GetRotation() * (180/std::numbers::pi)); // converting radians to degrees
        SDL_RenderTextureRotated(renderer, texture_, nullptr, &r, -rotation_amount, nullptr, SDL_FLIP_NONE);
    }
}
