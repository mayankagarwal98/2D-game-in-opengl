#include "main.h"

#ifndef POWERUP2_H

#define POWERUP2_H
   

class Powerup2 {
public:
    Powerup2() {}
    Powerup2(float x, float y, color_t color);
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
