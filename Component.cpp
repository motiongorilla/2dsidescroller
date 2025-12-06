#include "Component.h"


Component::Component(Actor* owner, int update_order) {
    owner_ = owner;
    update_order_ = update_order;
}

Component::~Component() {

}

void Component::Update(float delta_time) {

}
