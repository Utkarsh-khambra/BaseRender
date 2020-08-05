#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "../include/Camera.hpp"
#include "../include/CameraFPS.hpp"
#include "../include/Mesh.hpp"
#include "../include/Object.hpp"
#include "../include/Scene.hpp"

Scene::Scene () {}
Scene::~Scene () {}

void Scene::addObjcet (Object& obj)
{
    if (!head)
    {
        obj.next = head;
        head = &obj;
    }
    else
    {
        head = &obj;
        obj.next = NULL;
    }
}

void Scene::removeObject (Object& obj)
{
    Object* temp = &obj;
    if (head == temp)
    {
        head = temp->next;
        temp->next = NULL;
    }
    Object* current = head;
    while (!current) {
        if (current->next == temp) {
            current->next = temp->next;
            temp->next = NULL;
        }
        current = current->next;
    }
}

void Scene::addCamera (CameraFPS& cam)
{
    camera = &cam;
}
