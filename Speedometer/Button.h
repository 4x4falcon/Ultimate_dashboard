class Button
{
    typedef void (*Handler)();

  public:
    Button(int pin, int pressedVal, unsigned long longPressTime);
    void setPressHandler(Handler handler);
    void setLongPressHandler(Handler handler);
    int check();

  private:
    int m_pin;
    int m_pressedVal;
    unsigned long m_longPressTime;
    unsigned long m_downTime;
    bool m_pressed;
    bool m_eventFired;
    Handler m_pressHandler;
    Handler m_longPressHandler;
};

Button::Button(int pin, int pressedVal, unsigned long longPressTime) :
  m_pin(pin),
  m_pressedVal(pressedVal),
  m_longPressTime(longPressTime),
  m_downTime(0),
  m_pressed(false),
  m_eventFired(false)
{
}

void Button::setPressHandler(Handler handler)
{
  m_pressHandler = handler;
}

void Button::setLongPressHandler(Handler handler)
{
  m_longPressHandler = handler;
}

int Button::check()
{
  int value = digitalRead(m_pin);
  if (value == m_pressedVal && !m_pressed) {
    delay(50); // Debounce
    m_downTime = millis();
    m_pressed = true;
    m_eventFired = false;
  }
  else if (value == m_pressedVal && m_pressed) {
    unsigned long duration = millis() - m_downTime;
    if (duration >= m_longPressTime && !m_eventFired) {
      m_eventFired = true;
      if (m_longPressHandler) {
        m_longPressHandler();
      }
    }
  }
  else if (value != m_pressedVal && m_pressed) {
    if (!m_eventFired) {
      m_eventFired = true;
      if (m_pressHandler) {
        m_pressHandler();
      }
    }
    m_pressed = false;
  }
}
