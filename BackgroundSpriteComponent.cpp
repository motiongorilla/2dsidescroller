#include "BackgroundSpriteComponent.h"
#include "Game.h"
#include <numbers>

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* owner, int draw_order) : SpriteComponent(owner, draw_order) {
    draw_order_ = draw_order;
    owner_ = owner;
    owner->GetGameRef()->AddSprite(this);
}

void BackgroundSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures) {
    int count = 0;
    for(SDL_Texture* texture : textures) {
        BGTexture temp;

        temp.texture_ = texture;
        // each texture is screen-width in offset
        temp.offset_.x_ = count * screen_size_.x_;
        temp.offset_.y_ = 0;
        bg_textures_.emplace_back(temp);
        count++;
    }
}

void BackgroundSpriteComponent::Update(float delta_time) {
    for (BGTexture& bg : bg_textures_) {
        bg.offset_.x_ += scroll_speed_ * delta_time;

        if(bg.offset_.x_ < -screen_size_.x_) {
            bg.offset_.x_ = (bg_textures_.size() - 1) * screen_size_.x_ - 1;
        }
    }
}
void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer) {
    for (BGTexture& bg_texture : bg_textures_) {
        SDL_FRect r;
        // scale width and hight by owners scale
        r.w = static_cast<int>(screen_size_.x_ * owner_->GetScale());
        r.h = static_cast<int>(screen_size_.y_ * owner_->GetScale());

        // center rect from the position of the owning actor
        r.x = static_cast<int>(owner_->GetPosition().x_ - static_cast<float>(r.w)/2.f - bg_texture.offset_.x_);
        r.y = static_cast<int>(owner_->GetPosition().y_ - static_cast<float>(r.h)/2.f - bg_texture.offset_.y_);

        // Draw
        double rotation_amount = static_cast<double>(owner_->GetRotation() * (180/std::numbers::pi)); // converting radians to degrees
        SDL_RenderTextureRotated(renderer, bg_texture.texture_, nullptr, &r, -rotation_amount, nullptr, SDL_FLIP_NONE);
    }
}
