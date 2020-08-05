#pragma once

class Object;
struct Scene {
    Scene ();
    ~Scene ();
    void addObjcet (Object& obj);
    void removeObject (Object& obj);
    void addCamera (CameraFPS& cam);
    Object* head = NULL;
    CameraFPS* camera;
};
