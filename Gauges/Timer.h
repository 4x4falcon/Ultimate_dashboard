class Timer
{
    typedef void (*Callback)();

  public:
    Timer();
    void every(unsigned long millis, Callback callback);
    void update();

  private:
    unsigned long m_interval;
    unsigned long m_lastTime;
    Callback m_callback;
};

Timer::Timer()
{
  m_interval = 0;
  m_lastTime = 0;
  m_callback = NULL;
}

void Timer::every(unsigned long millis, Callback callback)
{
  m_interval = millis;
  m_callback = callback;
}

void Timer::update()
{
  unsigned long time = millis();
  if (time - m_lastTime > m_interval) {
    if (m_callback) {
      m_callback();
    }
    m_lastTime = time;
  }
}
