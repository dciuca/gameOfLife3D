#pragma once

/**
 * Snapshot of the user's intentions for the current frame.
 * Platform-agnostic: values are already mapped to camera units,
 * so the core never deals with keys, mouse deltas or wheels.
 */
struct InputState {
  bool togglePause = false;
  float yaw = 0.0f;      // camera rotation around the up axis
  float pitch = 0.0f;    // camera rotation around the right axis
  float panRight = 0.0f; // camera pan along the screen horizontal axis
  float panUp = 0.0f;    // camera pan along the screen vertical axis
  float zoom = 0.0f;     // camera zoom amount (0 = no zoom)
  bool increaseSpeed = false;
  bool decreaseSpeed = false;
};

class IInputHandler {
public:
  virtual ~IInputHandler() = default;

  virtual InputState poll() = 0;
};