// Bhinyaporn Pattanasethanon
// Snow glob project
// For a hollow circle, use GL_LINE_LOOP
// For a filled circle, use GL_TRIANGLE_FAN
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <iostream>
#include <math.h>
#define PI 3.1415926535898
#define WINDOW_WIDTH	300
#define WINDOW_HEIGHT	300
void keyb(unsigned char key, int x, int y);

int windowID;

//*************************************
//Create a structure for x and y plots
//*************************************
struct  Wall
{
    int x;
    int y;
};

Wall xWall[500];

//*******************************************
//draw one small square from 4 dotted points
//*******************************************

void draw(Wall wall)
{
    int xx=wall.x/3.5;
    int yy=wall.y/3.5;
    glBegin(GL_QUADS);						// Drawing Using Quads
    glVertex2i( 250+xx , 250+yy);				// Top
    glVertex2i( 250+xx , 255+yy );				// Bottom Left
    glVertex2i( 255+xx , 255+yy );				// Bottom Right
    glVertex2i( 255+xx , 250+yy );				// Bottom Right
    glEnd();
}

//***********************************************************
//create snow based on random position from the draw function
//***********************************************************
void snow(){
   
    for(int i=0;i< 500;i++)
    {
        Wall wall;
        wall.x =(int)( (rand()* 10000) %500);
        wall.y =(int)( (rand()* 10000) %500);
        xWall[i] =  wall;
        
    }
        
    for(int i=0;i< 500;i++)
    {
        glColor3f(1, 1, 1);
        //glColor3b((rand()%(256/2)), (rand()%(256/2)), (rand()%(256/2)));
        draw(xWall[i]);
    }
}

void bitmap_output(int x, int y, void *font, char*s){
    int len,i;
    glRasterPos2f(x, y);
    len=(int)strlen(s);
    for(i=0;i<len;i++) //glutBitmapCharacter(font, s[i]);
    glutStrokeCharacter(font, s[i]);
}

void myreshape(GLsizei w, GLsizei h){
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
     if(w<=h)
     gluOrtho2D(-1.0, 1.0, -1*(GLfloat)h/w, (GLfloat)h/w);
     else {
     gluOrtho2D(-1*(GLfloat)w/h, (GLfloat)w/h, -1.0, 1.0);
     }*/
    gluOrtho2D(0, w, 0, h); // for (0,0)-(x,y) 
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);//adjust viewpoint
    
}

//******************************
//create snow globe square base
//******************************

void draw_square(int x, int y, int w, int l){
    glBegin(GL_QUADS);
    glVertex2i(x, y);glVertex2i(x, y+l);
    glVertex2i(x+w, y+l);glVertex2i(x+w, y);
    glEnd();

}

//*************************
//create snow globe circle
//*************************

void draw_circle(int x1, int y1,int r1,int cp){

    int i, circle_points = cp;
    float angle;
	
    glBegin(GL_TRIANGLE_FAN);
    for (i=0; i < circle_points; i++)
    {
        angle = 2*PI*i/circle_points;
        glVertex2f(x1 + (r1 * cos(angle)), y1 + (r1 * sin(angle)));
    }
    glEnd();
}

//***********************************
//create christmas tree from triangle
//***********************************

void draw_triangle(int x, int y, int w, int l){
    
    glBegin(GL_POLYGON);
    glVertex2i(x,y);glVertex2i(x+w*0.5, y+l);
    glVertex2i(x+w-w*0.5, y+l);glVertex2i(x+w, y);
    
    glEnd();

}
//*********************************
//create snow globe trapezoid base
//*********************************

void draw_trapezoid(int x, int y, int w, int l){
    
    glBegin(GL_POLYGON);
    glVertex2i(x,y);glVertex2i(x+w*0.25, y+l);
    glVertex2i(x+w-w*0.25, y+l);glVertex2i(x+w, y);
    
    glEnd();
    
}

void Display(void){
 
    
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.6, 0.5, 0.4);
    draw_trapezoid(40, 20, 430, 100);
    
    glColor3f(0.3, 0.55, 1);
    draw_circle(250,250,200,200);
   
    glColor3f(1, 1, 0);
   
    draw_circle(350, 380, 30,200);
   
    glColor3f(0.3, 0.55, 1);
    draw_circle(340,380,25,200);
   
    for (int i=0; i<3; i++) {
        for(int j=0;j<5;j++)
	{
            glColor3f(0.2, 1, 0);
            draw_triangle(120+j*60, 180+i*20, 50, 30);
            glColor3f(0.4, 0.3, 0.2);
            draw_square(140+j*60, 150, 15,30 );        
        }
    }

    snow();
 
    glPushMatrix();// push and pop so that the letter wouldn't move to the right
    glScalef(0.11, 0.2, 0.2);
    glColor3f(1, 1, 0.5);
    glTranslatef(200, 120, 0);
    bitmap_output(300, 300, GLUT_STROKE_MONO_ROMAN, "Press 'q' for quit and any key to snow");
    glPopMatrix();
        
    glFlush();
   
  }

//******************************
//keyboard input functions
//******************************

void keyb(unsigned char key, int x, int y){
    
    
    printf("%d", key );
	switch (key)
    {
        case 113:
            glutDestroyWindow(windowID);
            exit(0);
            break;
	}
    Display();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) WINDOW_WIDTH, 0.0, (GLdouble) WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);

}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitWindowPosition(200, 200 );
        glutInitWindowSize(500,500);
	windowID=glutCreateWindow("My Snow Globe");
        glutKeyboardFunc(keyb);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
        glutReshapeFunc(myreshape);
	glutDisplayFunc(&Display);
	init();
	glutMainLoop();
	return 0;
}
