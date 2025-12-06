#pragma once

#include "BaseTypes.h"

#include <vector>

class Component;
class Game;

class Actor {
public:
    // Tracking state of an actor
    enum class State {
        Active,
        Paused,
        Dead
    };

    // Constructor/destructor
    Actor(Game* game_ref);
    virtual ~Actor();

    void Update(float delta_time);
    void UpdateComponents(float delta_time);

    // Actor specific update
    virtual void UpdateActor(float delta_time);

    // Getters/Setters
    State GetState() const;
    void SetState(State new_state);

    Game* GetGameRef() const;

    float GetScale() const;
    float GetRotation() const;
    Vector2 GetPosition() const;

    void SetScale(float new_scale);
    void SetRotation(float new_rotation);
    void SetPosition(Vector2 new_position);

    // Add/remove components
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

private:
    State state_;
    Vector2 position_;
    float scale_;
    float rotation_;
    std::vector<Component*> components_;
    Game* game_;
};
