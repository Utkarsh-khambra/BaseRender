/*
    Camera.hpp
*/
#pragma once
const float MAX_VERTICLE_ANGLE = glm::radians(88.0);

class Camera {
public:
    Camera ();
    Camera (float fov, float aspact, float nearPlane, float farPlane);
    void setFOV( float angle );
    float fov() const;
    void setAspect( float x );
    float aspect() const;
    void setClipZ( float x, float y );
    float nearPlane() const;
    float farPlane() const;
    void setPosition( glm::vec3 x);
    glm::vec3 position() const;
    void lookAt( glm::vec3 target );
    glm::mat4 View();
    glm::mat4 Orientation();
    glm::mat4 cameraMatrix();
    void positionOffset( glm::vec3 target );
    void orientationOffset( float upAngle, float rightAngle );
    glm::vec3 up();
    glm::vec3 forward();
    glm::vec3 right();
    void info();
private:
    float fov_{60.0};
    float aspact_{4.0/3.0};
    float nearPlane_{0.1};
    float farPlane_{100};
    glm::vec3 position_{glm::vec3(0,0,0)};
    float horizontalAngle_{0.0};
    float verticleAngle_{0.0};

    void normalizeAngle ();
};
