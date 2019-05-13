#include "firebeams.h"
#include "main.h"

Firebeams::Firebeams(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.025;
    speed1=0.025;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[1000];
    int vertex_count=0;
    vertex_buffer_data[vertex_count++]=1.2f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.2f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.2f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;


    vertex_buffer_data[vertex_count++]=-1.2f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.2f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.2f;
    vertex_buffer_data[vertex_count++]=0.45f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;



    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.15f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.05f;
    vertex_buffer_data[vertex_count++]=0.0f;



    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=-0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=-0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;


    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.35f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=-1.0f;
    vertex_buffer_data[vertex_count++]=0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;

    vertex_buffer_data[vertex_count++]=1.0f;
    vertex_buffer_data[vertex_count++]=0.25f;
    vertex_buffer_data[vertex_count++]=0.0f;






    this->object = create3DObject(GL_TRIANGLES, vertex_count, vertex_buffer_data, color, GL_FILL);
}


void Firebeams::draw(glm::mat4 VP) {
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

void Firebeams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeams::tick() {
    // this->rotation += 1;
    this->position.x -= speed;
    this->position.y+=speed1;
    if(this->position.y>3 || this->position.y<-2)
    {
        speed1=-speed1;
    }
    // this->position.y -= speed;
}
