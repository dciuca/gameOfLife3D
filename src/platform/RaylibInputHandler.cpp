#include "platform/RaylibInputHandler.h"
#include "raylib.h"

RaylibInputHandler::RaylibInputHandler()
    : m_rotateSensitivity(0.001f),
      m_panSensitivity(0.001f) {};

InputState RaylibInputHandler::poll()
{
    InputState input;

    // --------------------------------------
    // PAUSE HANDLING
    // --------------------------------------
    input.togglePause = IsKeyPressed(KEY_P);

    const Vector2 delta = GetMouseDelta();

    // --------------------------------------
    // CAMERA ROTATION (left drag)
    // --------------------------------------
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        input.yaw = -delta.x * m_rotateSensitivity;
        input.pitch = -delta.y * m_rotateSensitivity;
    }

    // --------------------------------------
    // CAMERA PAN (right drag)
    // --------------------------------------
    // The scene follows the mouse: dragging right moves the camera left
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        input.panRight = -delta.x * m_panSensitivity;
        input.panUp = delta.y * m_panSensitivity;
    }

    // --------------------------------------
    // CAMERA ZOOM (wheel)
    // --------------------------------------
    // Wheel up = move closer to the target
    input.zoom = -GetMouseWheelMove();

    return input;
}