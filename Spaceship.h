#include "Actor.h"

class SpaceshipActor : public Actor {
public:
    SpaceshipActor(Game* game);
    void UpdateActor(float delta_time) override;
    void ProcessKeyboard(const bool* state);

    float GetHorizontalSpeed() { return horiz_speed_; }
    float GetVerticalSpeed() { return vert_speed_; }

private:
    float horiz_speed_;
    float vert_speed_;
};
