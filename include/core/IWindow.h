#pragma once

class IWindow {
public:
  virtual ~IWindow() = default;
  virtual void init() = 0;
  virtual bool shouldClose() const = 0;
  virtual float getTimeFrame() = 0;
};