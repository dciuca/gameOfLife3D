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
  void zoom(float wheel) override {
    // CameraMoveToTarget(&m_camera, wheel);

    if (wheel == 0.0f)
      return;
    float step = 0.1f;

    Ray ray = GetMouseRay(GetMousePosition(), m_camera);
    if (fabsf(ray.direction.y) < 1e-4f)
      return;

    float t = -ray.position.y / ray.direction.y;
    if (t < 0.0f)
      return;

    Vector3 P = Vector3Add(ray.position, Vector3Scale(ray.direction, t));

    float k = 1.0f + wheel * step;
    if (k < 0.05f)
      k = 0.05f; // clamp per non passare attraverso P

    m_camera.target =
        Vector3Add(P, Vector3Scale(Vector3Subtract(m_camera.target, P), k));
    m_camera.position =
        Vector3Add(P, Vector3Scale(Vector3Subtract(m_camera.position, P), k));
  }
  Camera3D &getCamera() { return m_camera; }

private:
  Camera3D m_camera;
};