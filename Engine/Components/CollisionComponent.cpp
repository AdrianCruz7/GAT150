#include "CollisionComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
    void neu::CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();
        if (component)
        {
            g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);
        }
    }

    void neu::CollisionComponent::Update()
    {
    }

    void neu::CollisionComponent::OnCollisionEnter(Actor* other)
    {
        std::cout << other->GetName() << std::endl;
        if (m_enterFunction) m_enterFunction(other);
    }

    void neu::CollisionComponent::OnCollisionExit(Actor* other)
    {
        std::cout << other->GetName() << std::endl;
        if (m_exitFunction) m_exitFunction(other);
    }

    bool neu::CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool neu::CollisionComponent::Read(const rapidjson::Value& value)
    {
        Vector2 size;
        float density = 1;
        float friction = 1;
        float restitution = 0.3f;
        bool is_trigger = false;

        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);

        return true;
    }
}