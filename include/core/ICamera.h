#pragma once

class ICamera {
public:
  virtual ~ICamera() = default;

  virtual void yaw(float angle) = 0;
  virtual void pitch(float angle) = 0;
  virtual void zoom(float wheel) = 0;
};