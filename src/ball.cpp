#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.035;
    speed1 = 0.035;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0.0f,0.5f,0.0f,
        0.5f,0.2f,0.0f,
        0.3f,0.2f,0.0f,

        0.0f,0.5f,0.0f,
        -0.5f,0.2f,0.0f,
        -0.3f,0.2f,0.0f,

        0.0f,0.5f,0.0f,
        0.0f,-0.1f,0.0f,
        0.3f,0.2f,0.0f,

        0.3f,-0.2f,0.0f,
        0.3f,0.2f,0.0f,
        0.0f,-0.1f,0.0f,

        0.3f,-0.2f,0.0f,
        0.3f,0.2f,0.0f,
        0.0f,-0.1f,0.0f,

        0.3f,0.2f,0.0f,
        0.5f,0.2f,0.0f,
        0.3f,-0.3f,0.0f,

        0.5f,0.2f,0.0f,
        0.5f,-0.2f,0.0f,
        0.3f,-0.3f,0.0f,



         0.0f,0.5f,0.0f,
        0.0f,-0.1f,0.0f,
        -0.3f,0.2f,0.0f,

        -0.3f,-0.2f,0.0f,
        -0.3f,0.2f,0.0f,
        0.0f,-0.1f,0.0f,

        -0.3f,-0.2f,0.0f,
        -0.3f,0.2f,0.0f,
        0.0f,-0.1f,0.0f,

        -0.3f,0.2f,0.0f,
        -0.5f,0.2f,0.0f,
        -0.3f,-0.3f,0.0f,

        -0.5f,0.2f,0.0f,
        -0.5f,-0.2f,0.0f,
        -0.3f,-0.3f,0.0f,
    };
    static const GLfloat vertex_buffer_data1[]={
        -0.5f,0.2f,0.0f,
        -0.5f,-0.2f,0.0f,
        -0.3f,-0.3f,0.0f,

        0.5f,0.2f,0.0f,
        0.5f,-0.2f,0.0f,
        0.3f,-0.3f,0.0f,
    };

     static const GLfloat vertex_buffer_data2[]={
         0.5f,0.0f,0.0f,
         -0.5f,0.0f,0.0f,    
         0.5f,-0.3f,0.0f,

         -0.5f,0.0f,0.0f,
         -0.5f,-0.3f,0.0f, 
         0.5f,-0.3f,0.0f,    
    };
     static GLfloat vertex_buffer_data3[1000];
    int vertex_count=0,n=10;
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data3[vertex_count++]=0.2+0.04*cos((2* M_PI*i)/n);
        vertex_buffer_data3[vertex_count++]=0.05+0.04*sin((2* M_PI*i)/n);
        vertex_buffer_data3[vertex_count++]=0.0f;
        vertex_buffer_data3[vertex_count++]=0.2+0.04*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data3[vertex_count++]=0.05+0.04*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data3[vertex_count++]=0.0f;
        vertex_buffer_data3[vertex_count++]=0.2;
        vertex_buffer_data3[vertex_count++]=0.05;
        vertex_buffer_data3[vertex_count++]=0.0f;
    }    

    for(int i=0;i<n;i++)
    {
        vertex_buffer_data3[vertex_count++]=-0.2+0.04*cos((2* M_PI*i)/n);
        vertex_buffer_data3[vertex_count++]=0.05+0.04*sin((2* M_PI*i)/n);
        vertex_buffer_data3[vertex_count++]=0.0f;
        vertex_buffer_data3[vertex_count++]=-0.2+0.04*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data3[vertex_count++]=0.05+0.04*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data3[vertex_count++]=0.0f;
        vertex_buffer_data3[vertex_count++]=-0.2;
        vertex_buffer_data3[vertex_count++]=0.05;
        vertex_buffer_data3[vertex_count++]=0.0f;
    }    
    
    this->object2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data2, COLOR_GOLD, GL_FILL);    
    this->object = create3DObject(GL_TRIANGLES, 3*12, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data1, COLOR_FIRELINE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, vertex_count, vertex_buffer_data3, COLOR_BLACK, GL_FILL);    

    
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);    
    draw3DObject(this->object);
    draw3DObject(this->object1); 
    draw3DObject(this->object3);    

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int a) {
    this->rotation += 0;
    if(a==1 && this->position.x<3.5)
        this->position.x+= speed;
    else if(a==0 && this->position.x>-3.5)
        this->position.x-= speed;
    else if(a==2 && this->position.y< 3.5)
    {
        this->position.y+=0.25;
    }
    if(this->position.y>-2.487 && a!=4)
    {
        // speed1-=0.0025;
        this->position.y-=speed1;
    }
}

