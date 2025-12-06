#include "Actor.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game_ref) {
    game_ = game_ref;
}

Actor::~Actor() {
}

void Actor::Update(float delta_time){
    UpdateComponents(delta_time);
    UpdateActor(delta_time);
}

void Actor::UpdateComponents(float delta_time) {
    for(Component* comp : components_) {
        comp->Update(delta_time);
    }
}

void Actor::UpdateActor(float delta_time) {

}

Actor::State Actor::GetState() const {
    return state_;
}

void Actor::SetState(Actor::State new_state) {
    state_ = new_state;
}

Game* Actor::GetGameRef() const {
    return game_;
}


float Actor::GetScale() const {
    return scale_;
}
float Actor::GetRotation() const {
    return rotation_;
}
Vector2 Actor::GetPosition() const {
    return position_;
}

void Actor::SetScale(float new_scale) {
    scale_ = new_scale;
}
void Actor::SetRotation(float new_rotation) {
    rotation_ = new_rotation;
}
void Actor::SetPosition(Vector2 new_position) {
    position_ = new_position;
}

void Actor::AddComponent(Component* component) {
    int component_update_order = component->GetUpdateOrder();

    auto it = components_.begin();
    for(; it != components_.end(); ++it) {
        if (component_update_order < (*it)->GetUpdateOrder()) {
            break;
        }
    }
    components_.insert(it, component);
}

void Actor::RemoveComponent(Component* component) {
    auto it = find(components_.begin(), components_.end(), component);

    if (it != components_.end()) {
        components_.erase(it);
        return;
    }
}
