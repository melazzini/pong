#pragma once
class RectangularGeometry
{
  public:
    explicit RectangularGeometry() = default;
    RectangularGeometry(int w, int h) : m_w{w}, m_h{h}
    {
    }

    RectangularGeometry(const RectangularGeometry &) = default;

    RectangularGeometry &operator=(const RectangularGeometry &) = default;

    virtual ~RectangularGeometry() = default;

    [[nodiscard]] int width() const
    {
        return m_w;
    }

    [[nodiscard]] int height() const
    {
        return m_h;
    }

    void resize(int w, int h)
    {
        m_w = w;
        m_h = h;
    }

    void setWidth(int w)
    {
        m_w = w;
    }

    void setHeight(int h)
    {
        m_h = h;
    }

    bool operator==(const RectangularGeometry &other) const
    {
        return ((other.m_h == this->m_h) && (other.m_w == this->m_w));
    }

  private:
    int m_w;
    int m_h;
};
