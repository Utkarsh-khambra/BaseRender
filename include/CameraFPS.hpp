#pragma once

class Window;
class Camera;
const float MOUSE_SENSITIVITY = 0.001, CAMERA_SPEED = 0.2;
const char MOVE_FORWARD = 'W';
const char MOVE_BACKWARD = 'S';
const char MOVE_RIGHT = 'D';
const char MOVE_LEFT = 'A';
class CameraFPS : public Camera {
public:
    CameraFPS ();
    CameraFPS (float fov, float aspact, float nearPlane, float farPlane);
    void update (Window& window);

};
