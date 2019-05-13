#include "main.h"

#ifndef CIRCULARRING_H

#define CIRCULARRING_H
   

class Circularring {
public:
    Circularring() {}
    Circularring(float x, float y,float radius, color_t color);
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
