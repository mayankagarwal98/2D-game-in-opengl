#include "main.h"

#ifndef FIREBEAMS_H

#define FIREBEAMS_H
   

class Firebeams {
public:
    Firebeams() {}
    Firebeams(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed1;
private:
    VAO *object;
};

#endif // BALL_H
