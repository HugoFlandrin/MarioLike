#pragma once
#include <SFML/Graphics.hpp>
#include "AComponent.h"
#include "box2d/box2d.h"

class Entity : public sf::Drawable
{
    int ID;
    std::vector<AComponent*> components;

public:
    Entity(int _id);
    int getId() const;
    void setId(int _id);

    virtual void update(float _deltaTime);
    virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

    std::vector<AComponent*>* getComponents();

    template<typename U>
    U* getComponent() {
        for (auto it : components) {
            if (U* c = dynamic_cast<U*>(it)) {
                return c;
            }
        }
        return nullptr;
    }

    template<typename U>
    U* createComponent() {
        U* t = new U();
        t->parent = this;
        components.push_back(t);
        return t;
    }

    void addComponent(AComponent* _component);

    template<typename U>
    void removeComponent(AComponent* _component) {
        components.erase(find(components.begin(), components.end(), _component));
    }

    void createPhysics(b2Vec2 _size = b2Vec2(64, 64), b2BodyType _bodyType = b2_staticBody, bool _fixedRotation = true, float _density = 0.f, float _friction = 0.f);
};
