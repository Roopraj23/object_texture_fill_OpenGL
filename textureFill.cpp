#define GL_SILENCE_DEPRECATION

#include <bits/stdc++.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "imageio.h" 

int texImageWidth;
int texImageHeight;
int window;

int mouse_x, mouse_y;
bool RIGHT_BUTTON_DOWN;

double rotate_y = 0; 
double rotate_x = 0;

static GLuint handles[6];			//texture names
int anglex= 30, angley = 40, anglez = 0;	//rotation angles

//images for texture maps for 6 faces of cube
char maps[][40] = { "box.png",  "box.png",  "box.png", "box.png", "box.png", "box.png" };


GLubyte *makeTexImage( char *loadfile ) //load texture image
{
   int i, j, c, width, height;
   GLubyte *texImage;

   texImage = loadImageRGBA( (char *) loadfile, &width, &height);	
   texImageWidth = width;
   texImageHeight = height;

   return texImage;
}

void init(void) //Initialization
{
  glClearColor(0,0,0,0);
  glShadeModel(GL_FLAT); //surface shade

   glEnable(GL_DEPTH_TEST);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   //handles is global
   glGenTextures(6, handles);
   for ( int i = 0; i < 6; ++i ) {
        if(i != 3 && i != 5){
     GLubyte *texImage = makeTexImage( maps[i] );
     if ( !texImage ) {
       printf("\nError reading %s \n", maps[i] );
       continue;
     }
     glBindTexture(GL_TEXTURE_2D, handles[i]);		//now we work on handles
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth, texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

     delete texImage;					//free memory holding texture image
    }
   }
}

float ver[8][3] = 
{
    {-1.0, -1.0, 1.0},  //a -0
    {-1.0, 1.0, 1.0},   //b -1
    {1.0, 1.0, 1.0},    //c -2
    {1.0, -1.0, 1.0},   //d -3
    {-1.0, -1.0, -1.0}, //e -4
    {-1.0, 1.0, -1.0},  //f -5
    {1.0, 1.0, -1.0},   //g -6
    {1.0, -1.0, -1.0},  //h -7
};

GLfloat color[6][3] = {
    {1,0,0},
    {1,1,0},
    {1,0,1},
    {1,0.5,0},
    {1,0,0.5},
    {1,1,1},
    
};

void quad(int a,int b,int c,int d, int h) //Draw the face of Polygon
{
    glBindTexture(GL_TEXTURE_2D, handles[h]);
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(ver[a]);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(ver[b]);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(ver[c]);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(ver[d]);

    glEnd();
}

void colorcube() //Draw polygon
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable( GL_CULL_FACE );
    glCullFace ( GL_BACK );
    quad(0,3,2,1,0);  //1
	quad(4,5,6,7,1);  //2
    quad(2,3,7,6,2);  //3
    quad(0,4,7,3,3);  //4
	quad(0,1,5,4,4);  //5
    quad(1,2,6,5,5);  //6
    glFlush();
   glDisable(GL_TEXTURE_2D);
}

void keybourdKeys( int key, int x, int y ) // Up, Down, Right, Left
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

void mouseCordValue ( int button, int state, int x , int y )//Mouse coordinate value
{
    mouse_x = x;
    mouse_y = y;

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        RIGHT_BUTTON_DOWN = true;
    glutPostRedisplay();
	
}

void motion(int x, int y) //conver the mouse coordinate value for rotation
{
    if (RIGHT_BUTTON_DOWN) {
        rotate_x += (float)(x - mouse_x) / 4.0; 
        rotate_y += (float)(mouse_y - y) / 4.0;
    }

    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

void display() //Display the cube
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 10 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3, 
               0, 0, 0,
               0, 0, 1
              );

    glRotatef( -rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( -rotate_y, 0.0, 1.0, 0.0 );
    colorcube();

    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}


int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow("Texture Mapping in 3D cube");
	init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseCordValue);
    glutMotionFunc(motion);
    glutSpecialFunc(keybourdKeys);
    glEnable( GL_DEPTH_TEST );
    glutMainLoop();
    return 0;
}