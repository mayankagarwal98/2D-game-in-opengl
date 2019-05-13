#include "main.h"

#ifndef POWERUP1_H

#define POWERUP1_H
   

class Powerup1 {
public:
    Powerup1() {}
    Powerup1(float x, float y, color_t color);
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
