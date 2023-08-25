
class RectangularGeometry
{
  public:
    RectangularGeometry(int w, int h) : m_w{w}, m_h{h}
    {
    }

    int width() const
    {
        return m_w;
    }

    int height() const
    {
        return m_h;
    }

    void resize(int w, int h)
    {
        m_w = w;
        m_h = h;
    }

  private:
    int m_w;
    int m_h;
};
