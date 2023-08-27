
class RectangularGeometry
{
  public:
    RectangularGeometry(int w, int h) : m_w{w}, m_h{h}
    {
    }

    RectangularGeometry(const RectangularGeometry &) = default;

    RectangularGeometry &operator=(const RectangularGeometry &) = default;

    virtual ~RectangularGeometry()
    {
    }

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

  private:
    int m_w;
    int m_h;
};
