#include "AnimSpriteComponent.h"
#include "Game.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int draw_order) : SpriteComponent(owner, draw_order) {
    current_frame_displayed_ = 0.f;
    animation_fps_ = 5;
}

void AnimSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures) {
    animation_textures_ = textures;
    current_frame_displayed_ = 0.f;
    SetTexture(animation_textures_[0]);
}

void AnimSpriteComponent::Update(float delta_time) {
    SpriteComponent::Update(delta_time);

    if (animation_textures_.size() > 0) {
        // update current frame based on framerate
        current_frame_displayed_ += animation_fps_ * delta_time;

        while(current_frame_displayed_ >= animation_textures_.size()) {
            current_frame_displayed_ -= animation_textures_.size();
        }

        SetTexture(animation_textures_[static_cast<int>(current_frame_displayed_)]);
    }
}
