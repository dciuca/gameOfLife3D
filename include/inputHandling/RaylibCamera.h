#pragma once

#include "raylib.h"
#include "rcamera.h"
#include "../core/interfaces/ICamera.h"

class RaylibCamera : public ICamera
{
public:
    RaylibCamera()
    {
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

    void yaw(float angle) override
    {
        CameraYaw(&m_camera, angle, true);
    }
    void pitch(float angle) override
    {
        CameraPitch(&m_camera, angle, true, true, true);
    }
    void zoom(float wheel) override
    {
        CameraMoveToTarget(&m_camera, wheel);
    }
    Camera3D &getCamera() { return m_camera; }

private:
    Camera3D m_camera;
};