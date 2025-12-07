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

void SpriteComponent::SetSpriteRenderFrame(Vector2 pos, Vector2 extents, bool is_full) {
    if(is_full) {
        use_render_frame_ = false;
        return;
    }

    sprite_render_frame_.w = extents.x_;
    sprite_render_frame_.h = extents.y_;

    sprite_render_frame_.x = pos.x_;
    sprite_render_frame_.y = pos.y_;

    use_render_frame_ = true;
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (texture_) {
        SDL_FRect r;

        // get width and height based on render frame
        float src_w = use_render_frame_ ? sprite_render_frame_.w : static_cast<float>(texture_width_);
        float src_h = use_render_frame_ ? sprite_render_frame_.h : static_cast<float>(texture_height_);

        // scale width and hight by owners scale
        r.w = src_w * owner_->GetScale();
        r.h = src_h * owner_->GetScale();

        // center rect from the position of the owning actor
        r.x = owner_->GetPosition().x_ - static_cast<float>(r.w)/2.f;
        r.y = owner_->GetPosition().y_ - static_cast<float>(r.h)/2.f;

        // Draw
        double rotation_amount = static_cast<double>(owner_->GetRotation() * (180/std::numbers::pi)); // converting radians to degrees

        SDL_FRect* srcrect = use_render_frame_ ? &sprite_render_frame_ : nullptr;
        SDL_RenderTextureRotated(renderer, texture_, srcrect, &r, -rotation_amount, nullptr, SDL_FLIP_NONE);
    }
}
