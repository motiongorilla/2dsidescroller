#pragma once

class Actor;

class Component {
public:
    // Constructor. the lower the update_order the earlier it will update
    Component(Actor* owner, int update_order = 100);
    virtual ~Component();

    virtual void Update(float delta_time);
    int GetUpdateOrder() const { return update_order_; }

protected:
    Actor* owner_;
    int update_order_;
};
