#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "coins.h"
#include "background.h"
#include "magnet.h"
#include "firelines.h"
#include "ballon.h"
#include "powerup1.h"
#include "firebeams.h"
#include "boomerangs.h"
#include "powerup2.h"
#include "circularring.h"

int magnet_visible=1,fireline_visible=0,ballon_visible=0,score=0,noofballon=4,boomerang_visible=1,circle_motion=0;
time_t time_mag=clock()-7000000,time_fireline=clock()-3000000,time_boomerang=clock();
float speed_ballon=0.025;
float ballon_gravity=0.0005;
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Background back;
Ball ball1,ball2;
Floor floor1[34];
Floor floor2[34];
Coins coins[10];
Coins coins1[10];
Firebeams firebeams;
Boomerangs boomerang;
Magnet magnet;
Firelines firelines;
Ballon ballon ;
Powerup1 power_ballon;
Powerup2 power_coins;
Circularring ring,ring1;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 0, 1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    back.draw(VP);

    ring.draw(VP);

    ring1.draw(VP);

    ballon.draw(VP);
    
    power_ballon.draw(VP);
    power_coins.draw(VP);
    magnet.draw(VP);
    firelines.draw(VP);
    boomerang.draw(VP);
    for(int i=0;i<6;i++)
        coins[i].draw(VP);
    firebeams.draw(VP); 
    ball2.draw(VP);    
    for(int i=0;i<30;i++)
    {
        floor1[i].draw(VP);
        floor2[i].draw(VP);
    } 
}
int prevballon;
float theta_circle;
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window,GLFW_KEY_SPACE);
    int ballon_key =glfwGetKey(window,GLFW_KEY_B);
    if (left) {
        if(circle_motion==0)
            ball2.tick(0);
        else
        {
            ball2.tick(4);
            // cout<<theta_circle*180.0/M_PI<<'\n';
            theta_circle-=0.01;
            if(theta_circle>M_PI || theta_circle<0)
                circle_motion=0;
        }
    }
    if(right){
        if(circle_motion==0)
            ball2.tick(1);
        else
        {
            ball2.tick(4);
            // cout<<theta_circle*180/M_PI<<'\n';
            theta_circle+=0.01;
            if(theta_circle>M_PI || theta_circle<0)
                circle_motion=0;
        }
    }
    if(space)
    {
        if(circle_motion==0)
            ball2.tick(2);
    }
    if(ballon_key!=prevballon && prevballon==1 && noofballon)
    {
        
      ballon_visible=1;
      ballon.position.x=ball2.position.x;
      ballon.position.y=ball2.position.y;
      speed_ballon=0.025;
      noofballon-- ;
    }
    prevballon=ballon_key;
}
void ballon_motion()
{
    ballon.position.x+=0.025;
    ballon.position.y+=speed_ballon;
    speed_ballon-=ballon_gravity;
}
void ballon_collision()
{
    if(ballon_visible && fireline_visible)
    {
         float theta=firelines.rotation;
         for(int k=0;k<=100;k++)
         {
            //  cout<<firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ballon.position.y<<' ';
            //  cout<<firelines.position.x-(float)k*cos(theta*M_PI/180.0)/100.0-ballon.position.x<<'\n';//" "<<abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ball2.position.y)<=0.6<<'\n';
             //" "<<abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ball2.position.y)<=0.6<<'\n';
            if(abs(firelines.position.x+(float)k*cos(theta*M_PI/180.0)/100.0-ballon.position.x)<=0.15 && abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ballon.position.y)<=0.15 )
            {
                cout<<"Balloon successfully hit firelines"<<'\n';
                score+=10;
                firelines.position.x=-100;
                break;
            }
            if(abs(firelines.position.x-(float)k*cos(theta*M_PI/180.0)/100.0-ballon.position.x)<=0.15 && abs(firelines.position.y-(float)k*sin(theta*M_PI/180.0)/100.0-ballon.position.y)<=0.15 )
            {
                cout<<"balloon successfully hit firelines"<<'\n';
                firelines.position.x=-100;
                score+=10;
                break;
            }
        }
    }
}
void fireline_make()
{
     firelines.tick();
      if(clock()-time_fireline>10000000)
     {
         fireline_visible=1-fireline_visible;
         if(fireline_visible==0)
         {
             firelines.position.x=-100.0;
             time_fireline=clock();
         }
         else
         {
            float k= ((float)(rand()%100))/33.3-2; 
            float m= ((float)(rand()%100))/33.3-2;
            float theta = ((float)(rand()%90));
            firelines.position.x=5;
            firelines.position.y=m;
            firelines.rotation=theta;
            time_fireline=clock()-3000000 ;
         }
     }
     if(fireline_visible && circle_motion==0)
     {
         float theta=firelines.rotation;
         for(int k=0;k<=100;k++)
         {
            //  cout<<firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0<<" "<<ball2.position.y<<' ';
            //  cout<<firelines.position.x+(float)k*cos(theta*M_PI/180.0)/100.0<<" "<<ball2.position.x<<'\n';//" "<<abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ball2.position.y)<=0.6<<'\n';
             //" "<<abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)/100.0-ball2.position.y)<=0.6<<'\n';
            if(abs(firelines.position.x+(float)k*cos(theta*M_PI/180.0)*1.1/100.0-ball2.position.x)<=0.65 && abs(firelines.position.y+(float)k*sin(theta*M_PI/180.0)*1.1/100.0-ball2.position.y)<=0.65 )
            {
                cout<<" Game over , score="<<score<<'\n';
                firelines.position.x=-100;
                exit(0);
                break;
            }
            if(abs(firelines.position.x-(float)k*cos(theta*M_PI/180.0)*1.1/100.0-ball2.position.x)<=0.65 && abs(firelines.position.y-(float)k*sin(theta*M_PI/180.0)*1.1/100.0-ball2.position.y)<=0.65 )
            {
                cout<<" Game over , score="<<score<<'\n';                
                firelines.position.x=-100;
                exit(0);
                break;
            }
        }
     }
}
void magnet_make()
{
     magnet.tick();
      if(clock()-time_mag>10000000)
     {
         magnet_visible=1-magnet_visible;
         if(magnet_visible==0)
         {
             magnet.position.x=-100.0;
             time_mag=clock();
         }
         else
         {
            float k= ((float)(rand()%100))/33.3-2; 
            magnet.position.x=k;
            time_mag=clock()-7000000;

         }
     }
   
     if(magnet_visible && circle_motion==0)
     {
         float mag_angle=atan((magnet.position.y-ball2.position.y)/(magnet.position.x-ball2.position.x));
         if(sin(mag_angle)<0)
         {
              ball2.position.x-=0.02*cos(mag_angle);
         }
         else
            ball2.position.x+=0.02*cos(mag_angle);

        ball2.position.y+=abs(0.02*sin(mag_angle));

     }
}
void coins_make()
{
      for(int i=0;i<6;i++)
    {
        coins[i].tick();
    }
     if(coins[4].position.x<=-5)
    {
        float k= ((float)(rand()%100))/33.3-2.0;
        k=-k;
        for(int i=0;i<6;i++)
        {
            coins[i].position.x+=10.0;
        }
        coins[0].position.y=k;
        coins[1].position.y=0.5+k;
        coins[2].position.y=k;
        coins[3].position.y=k;
        coins[4].position.y=0.5+k;
        coins[5].position.y=0.5+k;
    }
    // cout<<ball1.position.x<<" "<<coins[2].position.x<<'\n';
    for(int i=0;i<6;i++)
    {
        bounding_box_t a,b;
        a.x=ball2.position.x;
        a.y=ball2.position.y;
        b.x=coins[i].position.x;
        b.y=coins[i].position.y;
        if(i==1)
        {
            b.y+=0.5;
        }
        if(i==2)
        {
            b.x-=0.5;
        }
        if(i==3)
        {
            b.x+=0.5;
        }
        if(i==4)
        {
            b.x+=0.5;
            b.y+=0.5;
        }
        if(i==5)
        {
            b.x-=0.5;
            b.y+=0.5;
        }
        a.width=1.0;
        a.height=1.0;
        b.width=0.4;
        b.height=0.4;
        if(detect_collision(a,b))
        {
            // cout<<"true"<<'\n';
            score+=2;
            coins[i].position.y=-100;
        }
    }

}
void floor_make()
{
    for(int i=0;i<30;i++)
    {   
        floor1[i].tick();
        floor2[i].tick();
    }
    float l=0.0;
    if(floor1[0].position.x<=-1.64-8.04)
    {
        for(int i=0;i<30;i++)
        {
            floor1[i].position.x=l-1.64;
            floor2[i].position.x=l-1.64;
            l+=0.67;
        }
    }
}
void ballon_make()
{
    if(ballon_visible)
     {
        ballon.tick();
        ballon_motion();
        ballon_collision();
     }
     else
     {
         ballon.position.x=-100;
     }
}
float powerup1_gravity=0.0007,speed_powerup1=0.055;

void powerup1_motion()
{
    power_ballon.position.x-=0.03;
    if(power_ballon.position.x<3.5)
    {
        power_ballon.position.y+=speed_powerup1;
        speed_powerup1-=powerup1_gravity;
    }
    else
    {
        speed_powerup1=0.055;
    }
}
void powerup1_make()
{
    powerup1_motion();
    power_ballon.tick();
    bounding_box_t a,b;
    a.x=ball2.position.x;
    a.y=ball2.position.y;
    b.x=power_ballon.position.x;
    b.y=power_ballon.position.y;
    a.width=1;
    a.height=1;
    b.width=0.8;
    b.height=0.8;
    if(detect_collision(a,b))
    {
        noofballon+=4;
        power_ballon.position.x=-100;
    }
    if(power_ballon.position.x<-20)
    {
        power_ballon.position.x = 30;
        float ran=(float)(rand()%100)/20-2.5;
        power_ballon.position.y=ran;
    }
}
float powerup2_gravity=0.0007,speed_powerup2=0.055;

void powerup2_motion()
{
    power_coins.position.x-=0.03;
    if(power_coins.position.x<3.5)
    {
        power_coins.position.y+=speed_powerup2;
        speed_powerup2-=powerup2_gravity;
    }
    else
    {
        speed_powerup2=0.055;
    }
}
void powerup2_make()
{
    powerup2_motion();
    power_coins.tick();
    bounding_box_t a,b;
    a.x=ball2.position.x;
    a.y=ball2.position.y;
    b.x=power_coins.position.x;
    b.y=power_coins.position.y;
    a.width=1;
    a.height=1;
    b.width=0.8;
    b.height=0.8;
    if(detect_collision(a,b))
    {
        score+=10;
        power_coins.position.x=-100;
    }
    if(power_coins.position.x<-20)
    {
        power_coins.position.x = 30;
        float ran=(float)(rand()%100)/20-2.5;
        power_coins.position.y=ran;
    }
}
void firebeams_make()
{
    firebeams.tick();
    bounding_box_t a,b,c;
    a.x=ball2.position.x;
    a.y=ball2.position.y;
    a.width=1;
    a.height=1;
    b.x=firebeams.position.x;
    b.y=firebeams.position.y;
    b.width=2.0;
    b.height=0.7;
    c.x=ballon.position.x;
    c.y=ballon.position.y;
    c.width=0.3;
    c.height=0.3;
    if(firebeams.position.x<-20)
    {
        firebeams.position.x=30;
    }
    if(detect_collision(a,b) && circle_motion==0)
    {
        cout<<"score="<<score<<"  Gameover"<<'\n';
        exit(0);
    }
    if(detect_collision(b,c))
    {
        cout<<"ballon successfully hit firebeams"<<'\n';
        score+=10;
        firebeams.position.x=30;
    }

}
void boomerang_make()
{
    boomerang.tick();
    if(clock()-time_boomerang>30000000)
    {
        boomerang_visible=1-boomerang_visible;
        float ran= (float)(rand()%100)/50.0+2;
        boomerang.position.y=4;
        boomerang.position.x=-4;
        time_boomerang=clock();
    }
    bounding_box_t a,b;
    a.x=ball2.position.x;
    a.y=ball2.position.y;
    b.x=boomerang.position.x;
    b.y=boomerang.position.y;
    a.width=1;
    a.height=1;
    b.height=0.8;
    b.width=0.8;
    if(detect_collision(a,b) && circle_motion==0)
    {
        cout<<"Boomerang strikes Game over score="<<score<<'\n';
        exit(0);
    }
}

void circularring_make()
{
    ring.tick();
    ring1.tick();
    if(1.35+0.717>sqrt((ring.position.x-ball2.position.x)*(ring.position.x-ball2.position.x)+(ring.position.y-ball2.position.y)*(ring.position.y-ball2.position.y)) && ring.position.y>ball2.position.y && circle_motion==0)
    {
        circle_motion=1;
        theta_circle=atan((ring.position.y-ball2.position.y)/(ring.position.x-ball2.position.x));
    }
    if(ring.position.x<-6)
    {
        ring.position.x=20;
        ring1.position.x=20;
    }
    if(ring.position.x<-4)
    {
        circle_motion=0;
    }
     theta_circle+=0.005;
}
void tick_elements() {
    if(magnet_visible==0 && circle_motion==0)
    {
        ball2.tick(3);
    }
    
    if(circle_motion==1)
    {
        // theta_circle+=0.1;
        ball2.tick(4);
        ball2.position.x=ring.position.x-1.6*cos(theta_circle);
        ball2.position.y=ring.position.y-1.6*sin(theta_circle);
    }
    back.tick();
    ballon_make();
    fireline_make();
    magnet_make();
    coins_make();
    floor_make();
    powerup1_make();
    powerup2_make();
    firebeams_make();
    boomerang_make();
    circularring_make(); 
    if(back.position.x<-7)
    {
        back.position.x=7;
    }
    camera_rotation_angle += 0;
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball2 = Ball(-1.5,-2.487, COLOR_RED);
    coins[0] =  Coins(0.0,0.0,COLOR_GOLD);
    coins[1] =  Coins(0.0,0.5,COLOR_BROWN);
    coins[2] =  Coins(-0.5,0.0,COLOR_BROWN);
    coins[3] =  Coins(0.5,0.0,COLOR_BROWN);
    coins[4] =  Coins(0.5,0.5,COLOR_GOLD);
    coins[5] =  Coins(-0.5,0.5,COLOR_GOLD);
    firelines = Firelines( -100,0,COLOR_FIRELINE);
    firebeams = Firebeams(10,0,COLOR_FIRELINE);
    ballon =  Ballon(0,0,COLOR_BLACK);
    power_ballon = Powerup1(-10,-1,COLOR_BLACK);
    power_coins = Powerup2(-20,0,COLOR_GOLD);
    magnet = Magnet(2,2,COLOR_DARKRED);
    boomerang = Boomerangs(-4,4,COLOR_VOILET);
    ring = Circularring(20,1,2,COLOR_RING);
    ring1 = Circularring(20,1,1.2,COLOR_BACKGROUND);
    back =      Background(7,0,COLOR_WALL);


    float l=0;
    for(int i=0;i<15;i++)
    {
        floor1[2*i]     = Floor(l-1.64,-1.847,COLOR_GREEN);
        floor2[2*i]     = Floor(l-1.64,0.6-1.847,COLOR_RED);
        l+=0.67;
        floor1[2*i+1]     = Floor(l-1.64,-1.847,COLOR_RED);
        floor2[2*i+1]     = Floor(l-1.64,0.6-1.847,COLOR_GREEN);
        l+=0.67;
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);
    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            char x[1000];
            sprintf(x,"SCORE : %d  BALLOONS : %d",score,noofballon);
            glfwSetWindowTitle(window,x);
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
