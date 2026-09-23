#pragma once

#include "core/ICamera.h"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

class RaylibCamera : public ICamera {
public:
  RaylibCamera() {
    // safe camera margin from grid border
    float cameraDistance = 100.0f;

    // Camera in top-right corner
    m_camera.position = {
        cameraDistance * 0.6f, // X
        cameraDistance * 0.8f, // Y
        cameraDistance * 0.6f  // Z
    };

    // Camera init
    m_camera.target = {0.0f, 0.0f, 0.0f};
    m_camera.up = {0.0f, 1.0f, 0.0f};
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
  }

  void yaw(float angle) override { CameraYaw(&m_camera, angle, true); }
  void pitch(float angle) override {
    CameraPitch(&m_camera, angle, true, true, false);
  }

  // Pan amounts are relative to the distance from the target,
  // so the movement speed feels the same at any zoom level.
  void pan(float right, float up) override {
    const float distance = Vector3Distance(m_camera.position, m_camera.target);

    const Vector3 rightDir = GetCameraRight(&m_camera);
    const Vector3 upDir =
        Vector3CrossProduct(rightDir, GetCameraForward(&m_camera));

    const Vector3 offset =
        Vector3Add(Vector3Scale(rightDir, right * distance),
                   Vector3Scale(upDir, up * distance));

    m_camera.position = Vector3Add(m_camera.position, offset);
    m_camera.target = Vector3Add(m_camera.target, offset);
  }

  // Zoom is proportional to the distance from the target:
  // fast when far away, precise when close.
  void zoom(float amount) override {
    const float distance = Vector3Distance(m_camera.position, m_camera.target);
    const float newDistance =
        Clamp(distance * (1.0f + amount * ZOOM_STEP), MIN_DISTANCE, MAX_DISTANCE);

    CameraMoveToTarget(&m_camera, newDistance - distance);
  }

  Camera3D &getCamera() { return m_camera; }

private:
  static constexpr float ZOOM_STEP = 0.1f; // 10% of the distance per step
  static constexpr float MIN_DISTANCE = 2.0f;
  static constexpr float MAX_DISTANCE = 1000.0f;

  Camera3D m_camera;
};