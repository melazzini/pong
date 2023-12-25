#pragma once
#include "Component.h"
#include "ComponentManager.h"
#include "GameObject.h"
#include <string>
#include <vector>

struct BoxColliderComponent;

struct BoxColliderComponentManagerBase : ComponentManager
{
    void checkForCollisionsWith(std::string)
    {
    }
};

class BoxColliderComponent : public Component
{
  public:
    BoxColliderComponent(GameObject *owner, BoxColliderComponentManagerBase *manager, std::string tag = "unknown")
        : Component(owner, manager), m_manager{manager}, m_tag{tag}
    {
    }
    void update(uint32_t deltatime) override
    {
    }

    const std::string &tag() const
    {
        return m_tag;
    }

  protected:
    BoxColliderComponentManagerBase *m_manager;

  private:
    std::string m_tag;
};

class BoxColliderComponentManager : public BoxColliderComponentManagerBase
{
  public:
    static BoxColliderComponentManager *getInstance();

  private:
    BoxColliderComponentManager() = default;
};
