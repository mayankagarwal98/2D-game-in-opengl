#include "main.h"

#ifndef BALLON_H
#define BALLON_H
   

class Ballon {
public:
    Ballon() {}
    Ballon(float x, float y, color_t color);
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
