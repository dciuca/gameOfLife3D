#pragma once

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void update();
    bool isPaused();

private:
    bool m_isPaused;
};