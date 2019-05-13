#include "main.h"

#ifndef FIRELINES_H
#define FIRELINES_H
   

class Firelines {
public:
    Firelines() {}
    Firelines(float x, float y, color_t color);
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
