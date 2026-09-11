#include "inputHandler.h"
#include "raylib.h"
#include "Utils.h" // DEBUG

InputHandler::InputHandler()
{
    m_isPaused = false;
}

InputHandler::~InputHandler()
{
}

void InputHandler::update()
{
    if (IsKeyPressed(KEY_P))
    {
        m_isPaused = !m_isPaused;
        Utils::log(std::string("P key pressed, m_isPaused= ") + (m_isPaused ? "true" : "false"));
    }
}

bool InputHandler::isPaused()
{
    return m_isPaused;
}