#include "coins.h"
#include "main.h"

Coins::Coins(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.025;
    int n=15;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[150] ;
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[9*i]=x+0.2*cos((2* M_PI*i)/n);
        vertex_buffer_data[9*i+1]=y+0.2*sin((2* M_PI*i)/n);
        vertex_buffer_data[9*i+2]=0.0f;
        vertex_buffer_data[9*i+3]=x+0.2*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[9*i+4]=y+0.2*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[9*i+5]=0.0f;
        vertex_buffer_data[9*i+6]=x;
        vertex_buffer_data[9*i+7]=y;
        vertex_buffer_data[9*i+8]=0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 15*9, vertex_buffer_data, color, GL_FILL);
}

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coins::tick() {
    this->position.x-=speed ;
}

