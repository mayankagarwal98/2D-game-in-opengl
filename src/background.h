#include "main.h"

#ifndef BACKGROUND_H

#define BACKGROUND_H
   

class Background {
public:
    Background() {}
    Background(float x, float y, color_t color);
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
