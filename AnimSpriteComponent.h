#include "SpriteComponent.h"
#include "Actor.h"

class AnimSpriteComponent: public SpriteComponent {
public:
    AnimSpriteComponent(Actor* owner, int draw_order = 100);
    // update animation every frame
    void Update(float delta_time) override;

    // set textures used for animation
    void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);

    float GetAnimFPS() const {return animation_fps_;}
    void SetAnimFPS(int fps) {animation_fps_ = fps;}

private:
    std::vector<SDL_Texture*> animation_textures_;
    // float to track how long the frame has been displayed
    float current_frame_displayed_;
    int animation_fps_;
};
