#include "SpriteComponent.h"

class BackgroundSpriteComponent: public SpriteComponent {
public:
    BackgroundSpriteComponent(Actor* owner, int draw_order = 100);
    void Update(float delta_time) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetBGTextures(const std::vector<SDL_Texture*>& textures);

    void SetScreenSize(const Vector2& size) { screen_size_ = size; }
    void SetScrollSpeed(float speed) { scroll_speed_ = speed; }
    float GetScrollSpeed() const { return scroll_speed_; }
private:
    // struct to encapsulate every bg image and it's offsets
    struct BGTexture {
        SDL_Texture* texture_;
        Vector2 offset_;
    };

    std::vector<BGTexture> bg_textures_;
    float scroll_speed_;
    Vector2 screen_size_;
};
