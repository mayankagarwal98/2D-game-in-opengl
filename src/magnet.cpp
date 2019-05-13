#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[40000];
    float r1=0.6,r2=0.4;
    int vertex_count=0;
    float i=0.0f,j=r1,a=0.0f,b=r2,temp_a,temp_b,temp_i,temp_j;
    for(int k=90;k<271;k++)
    {
        temp_a=a;
        temp_b=b;
        a=r2*cos((float(k)*M_PI/180.0));
        b=r2*sin((float(k)*M_PI/180.0));
        temp_i=i;
        temp_j=j;
        i=r1*cos((float(k)*M_PI/180.0));
        j=r1*sin((float(k)*M_PI/180.0));

        vertex_buffer_data[vertex_count++]=temp_i;
        vertex_buffer_data[vertex_count++]=temp_j;
        vertex_buffer_data[vertex_count++]=0.0;

        vertex_buffer_data[vertex_count++]=temp_a;
        vertex_buffer_data[vertex_count++]=temp_b;
        vertex_buffer_data[vertex_count++]=0.0;

        vertex_buffer_data[vertex_count++]=a;
        vertex_buffer_data[vertex_count++]=b;
        vertex_buffer_data[vertex_count++]=0.0;

        vertex_buffer_data[vertex_count++]=temp_i;
        vertex_buffer_data[vertex_count++]=temp_j;
        vertex_buffer_data[vertex_count++]=0.0;

        vertex_buffer_data[vertex_count++]=i;
        vertex_buffer_data[vertex_count++]=j;
        vertex_buffer_data[vertex_count++]=0.0;

        vertex_buffer_data[vertex_count++]=a;
        vertex_buffer_data[vertex_count++]=b;
        vertex_buffer_data[vertex_count++]=0.0;

   }
    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=r1;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=r1;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=r1;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=-r1;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=-r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-r2;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-r1;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=0.0f;
    vertex_buffer_data[vertex_count++]=-r1;
    vertex_buffer_data[vertex_count++]=0.0f;


    this->object = create3DObject(GL_TRIANGLES, vertex_count, vertex_buffer_data, color, GL_FILL);
}


void Magnet::draw(glm::mat4 VP) {
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

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->rotation += 1;
    this->position.x -= speed;
    // this->position.y -= speed;
    
}
