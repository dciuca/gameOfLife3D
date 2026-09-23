#pragma once

/**
 * Orbit camera: it always looks at a target point.
 * - yaw/pitch rotate the camera around the target
 * - pan moves camera and target together on the screen plane
 * - zoom moves the camera towards (< 0) or away from (> 0) the target
 */
class ICamera {
public:
  virtual ~ICamera() = default;

  virtual void yaw(float angle) = 0;
  virtual void pitch(float angle) = 0;
  virtual void pan(float right, float up) = 0;
  virtual void zoom(float amount) = 0;
};