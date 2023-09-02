#pragma once
#include <memory>
class TransformComponent;

class Paddle
{
  public:
    explicit Paddle();
    template <typename ComponentT> [[nodiscard]] ComponentT &component()
    {
        return *m_transform;
    }

  private:
    std::unique_ptr<TransformComponent> m_transform;
};
