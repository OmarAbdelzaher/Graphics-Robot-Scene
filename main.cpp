#include<windows.h>
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <iostream>
#include "glm.h"
#include "imageloader.h"

static int shoulderRx = -80, elbowR = 0, fingerBaseR = 0, fingerUpR = 0, footRx = 0,footRz = 0, elbowRx = 0;
static int shoulderLx = 80, elbowL = 0, fingerBaseL = 0 , fingerUpL = 0, footLx = 0,footLz = 0, elbowLx = 0;
static int upper_legRx = 0, lower_legRx = 0, upper_legLx = 0, lower_legLx = 0,shoulderRz = 0;
static int upper_legRz = 0, lower_legRz = 0, upper_legLz = 0, lower_legLz = 0,shoulderLz = 0;
int moving, startx, starty;
int Body_Rot = 0;
float x_position = 0.0;
float y_position = 0.0;
float z_position = 0.0;
float obj_pos = 0.0;
int state = 1;

int windowWidth = 1024;
int windowHeight = 768;
float aspect = float(windowWidth) / float(windowHeight);

GLMmodel* pmodel;
GLMmodel* pmodel1;
GLMmodel* pmodel2;
GLMmodel* pmodel3;
GLMmodel* pmodel4;
GLMmodel* pmodel5;
GLMmodel* pmodel6;

//double eye[] = { 0, 0, 0 };
//double center[] = { 0, 0, -1 };
//double up[] = { 0, 1, 0 };

// RGBA
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1.0 };
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = {0.0,-15.0, 3.0,0.0 };
GLfloat lightPos1[] = {0.0,15.0,0.5,0.0 };
// Material Properties
GLfloat mat_amb_diff[] = {0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = {100.0 };
//left teapot specular
GLfloat teapotl_diff[] = { 0.0,0.0, 1.0, 1.0 };
GLfloat teapotl_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotl_shininess[] = {10.0 };
//middle teapot diffuse
GLfloat teapotm_diff[] = { 1.0, 0, 0.0, 1.0 };
GLfloat teapotm_specular[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat teapotm_shininess[] = {1.0 };
//right teapot glosy
GLfloat teapotr_diff[] = { 1.0, .0, 0.0, 1.0 };
GLfloat teapotr_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotr_shininess[] = {1000.0 };
//cube
GLfloat cube_diff[] = {1.0,0.0, 0.0, 1.0 };
GLfloat cube_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cube_shininess[] = {10.0 };

double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double horizontal[] = {0,0,0};
double direction[] = {0,0,0};
double speed = 0.05f;

GLfloat angle = 0.0;
GLfloat angle2 = 0.0;
GLfloat Theta_1 = 0.0;
GLfloat Theta_2 = 0.0;

GLuint loadTexture(Image* image) {
      GLuint textureId;
      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);

      glTexImage2D(GL_TEXTURE_2D,
                               0,
                               GL_RGB,
                               image->width, image->height,
                               0,
                               GL_RGB,
                               GL_UNSIGNED_BYTE,

                               image->pixels);
      return textureId;
}
GLuint _textureId;
GLuint _textureId1;
GLuint startList;

void drawmodel1(void)
{
	if (!pmodel1) {
		pmodel1 = glmReadOBJ("data/Bed.obj");

		if (!pmodel1) exit(0);
		glmUnitize(pmodel1);
		glmFacetNormals(pmodel1);
		glmVertexNormals(pmodel1, 90.0);
		glmScale(pmodel1, 2.0);
	}
	glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodel4(void)
{
	if (!pmodel4) {
		pmodel4 = glmReadOBJ("data/chair.obj");

		if (!pmodel4) exit(0);
		glmUnitize(pmodel4);
		glmFacetNormals(pmodel4);
		glmVertexNormals(pmodel4, 90.0);
		glmScale(pmodel4, 2.0);
	}
	glmDraw(pmodel4, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodel2(void)
{
	if (!pmodel2) {
		pmodel2 = glmReadOBJ("data/chairD.obj");
		if (!pmodel2) exit(0);
		glmUnitize(pmodel2);
		glmFacetNormals(pmodel2);
		glmVertexNormals(pmodel2, 90.0);
		glmScale(pmodel2, 2.0);
	}
	glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodel3(void)
{
	if (!pmodel3) {
		pmodel3 = glmReadOBJ("data/lamp_2.obj");

		if (!pmodel3) exit(0);
		glmUnitize(pmodel3);
		glmFacetNormals(pmodel3);
		glmVertexNormals(pmodel3, 90.0);
		glmScale(pmodel3, 2.0);
	}
	glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
}
//Free model Drawer(Final) .obj
void drawmodel5(void)
{
	if (!pmodel5) {
		pmodel5 = glmReadOBJ("data/Table.obj");

		if (!pmodel5) exit(0);
		glmUnitize(pmodel5);
		glmFacetNormals(pmodel5);
		glmVertexNormals(pmodel5, 90.0);
		glmScale(pmodel5, 2.0);
	}
	glmDraw(pmodel5, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodel6(void)
{
	if (!pmodel6) {
		pmodel6 = glmReadOBJ("data/micro.obj");

		if (!pmodel6) exit(0);
		glmUnitize(pmodel6);
		glmFacetNormals(pmodel6);
		glmVertexNormals(pmodel6, 90.0);
		glmScale(pmodel6, 2.0);
	}
	glmDraw(pmodel6, GLM_SMOOTH | GLM_MATERIAL);
}


void initRendering(const char* floorTexture , GLuint &_textureId) {
     Image* image = loadBMP(floorTexture);
    _textureId = loadTexture(image);
    delete image;
    // Turn on the power
    glEnable(GL_LIGHTING);

    // Flip light switch
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // assign light parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    // Material Properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    GLfloat lightColor1[] = {1.0f, 1.0f,  1.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
    glEnable(GL_NORMALIZE);

    //Enable smooth shading
    glShadeModel(GL_SMOOTH);

    // Enable Depth buffer
    glEnable(GL_DEPTH_TEST);

}

void screen_menu(int value)
{
	char* name = 0;

	switch (value) {
	case '1':
		initRendering("Floors/wall.bmp",_textureId);
		break;
	case '2':
		initRendering("Floors/tile_1.bmp",_textureId);
		break;
	case '3':
		initRendering("Floors/square.bmp",_textureId);
		break;
	}
	glutPostRedisplay();
}



void init(void)
{
    glMatrixMode(GL_PROJECTION);
	gluPerspective(120.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()
{
	rotatePoint(up,Theta_1 - 0.02f,eye);

}

void Right()
{
	rotatePoint(up,Theta_1 + 0.02f,eye);
}

void Up()
{

	crossProduct(up,eye,horizontal);
	normalize(horizontal);
	rotatePoint(horizontal,Theta_2 - 0.02f,eye);
	rotatePoint(horizontal,Theta_2 - 0.02f,up);
}

void Down()
{
	crossProduct(up,eye,horizontal);
	normalize(horizontal);
	rotatePoint(horizontal,Theta_2 + 0.02f,eye);
	rotatePoint(horizontal,Theta_2 + 0.02f,up);

}

void moveForward()
{
    direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    += direction[0] * speed;
	eye[1]    += direction[1] * speed;
	eye[2]    += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{
    direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    -= direction[0] * speed;
	eye[1]    -= direction[1] * speed;
	eye[2]    -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;

}

static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      moving = 1;
      startx = x;
    }
    if (state == GLUT_UP) {
      moving = 0;
    }
  }
}
static void motion(int x, int y)
{
  if (moving) {
    angle = angle + (x - startx);
    startx = x;
    glutPostRedisplay();
  }
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
    glPopMatrix();

    //materials properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
   //floor
   glPushMatrix();
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBegin(GL_QUADS);

        glNormal3f(0.0,-1.0,0.0);
            glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-20,-5,10);
            glTexCoord2f(5.0f,  0.0f);
        glVertex3f(20,-5,10);
            glTexCoord2f(5.0f,  20.0f);
        glVertex3f(20,-5,-10);
            glTexCoord2f(0.0f, 20.0f);
        glVertex3f(-20,-5,-10);
        glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

    //model drawing
    glPushMatrix();
    	glTranslatef(12.0, -2.5, 6.4);
    	glRotatef(90,-1,0,0);
    	glScalef(3.0,3.0,3.0);
    	drawmodel1();
	glPopMatrix();


    glPushMatrix();
    	glTranslatef(-10, -0.9, -4.6);
    	glRotatef(90,-1,0,0);
    	glScalef(2.0,2.0,2.0);
    	drawmodel2();
	glPopMatrix();

	glPushMatrix();
    	glTranslatef(-10, 4.8, -1.6);
    	glRotatef(90,-1,0,0);
    	glScalef(2.0,2.0,5.0);
    	drawmodel3();
	glPopMatrix();

    glPushMatrix();
    	glTranslatef(12.0, -2.8, -6.4);
    	glRotatef(90,0,1,0);
    	glScalef(3.0,3.0,3.0);
    	drawmodel4();
	glPopMatrix();

	glPushMatrix();
    	glTranslatef(18.0, -3.8, -1.0);
    	glRotatef(90,0,1,0);
    	glScalef(2.0,1.0,2.0);
    	drawmodel5();
	glPopMatrix();


	glPushMatrix();
    	glTranslatef(18.0, obj_pos - 0.5, -2.0);
    	glRotatef(90,0,1,0);
    	drawmodel6();
	glPopMatrix();

   //the body
   glPushMatrix();
   glTranslatef (x_position,y_position,z_position);
   glRotatef ((GLfloat) Body_Rot, 0.0, 1.0, 0.0);
   glPushMatrix();
   glScalef (2.0,2.5,1.0);
   glutSolidCube(1.0);
   glPopMatrix();

    //Draw Head
   glPushMatrix();
   glTranslatef (0.0,2.0,0.0);
   glutWireSphere(0.5,10,10);
   glPopMatrix();

   //shoulder right
   glPushMatrix();

   glTranslatef (1.0,0.95,0.0);
   glRotatef ((GLfloat) shoulderRx, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) shoulderRz, 0.0, 1.0, 0.0);
   glTranslatef ( 1.0,0.0, 0.0);

   glPushMatrix();
   glScalef (2.0, 0.6,1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //elbow right
   glTranslatef (1.0,0.0,0.0);
   glRotatef ((GLfloat) elbowR, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) elbowRx, 0.0, 1.0, 0.0);
   glTranslatef (1.0,0.0,0.0);

   glPushMatrix();
   glScalef (2.0, 0.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1
    glPushMatrix();
    glTranslatef(1.0, 0.15, -0.1);
    glRotatef((GLfloat)fingerBaseR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0,0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flang 1
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUpR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();


    //Draw finger flang 2
    glPushMatrix();
    glTranslatef(1.0, 0.165, 0.15);
    glRotatef((GLfloat)fingerBaseR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0 , 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flang 2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUpR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

//Draw finger flang 3
    glPushMatrix();
    glTranslatef(1.0, 0.165, 0.4);
    glRotatef((GLfloat)fingerBaseR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0 , 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();


    //Draw finger flang 3
    glTranslatef(0.15, 0.0 , 0.0);
    glRotatef((GLfloat)fingerUpR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();


    //Draw finger flang 4
    glPushMatrix();
    glTranslatef(1.0, 0.165, -0.35);
    glRotatef((GLfloat)fingerBaseR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flang 4
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUpR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();


//Draw finger flang 5
    glPushMatrix();
    glTranslatef(1.0, -0.2, -0.1);
    glRotatef((GLfloat)fingerBaseR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flang 5
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUpR, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

   glPopMatrix();

   //other arm
   //Shoulder left
   glPushMatrix();

   glTranslatef ( -1.0,0.95,0.0);
   glRotatef ((GLfloat) shoulderLx, 0.0,0.0, 1.0);
   glRotatef ((GLfloat) shoulderLz, 0.0,1.0, 0.0);
   glTranslatef ( -1.0,0.0,0.0);

   glPushMatrix();
   glScalef (2.0, 0.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Elbow left
   glTranslatef (-1.0,0.0,0.0);
   glRotatef ((GLfloat) elbowL, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) elbowLx, 0.0, 1.0, 0.0);
   glTranslatef (-1.0,0.0,0.0);

   glPushMatrix();
   glScalef (2.0, 0.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1
   glPushMatrix();
   glTranslatef(-1.0,0.15,-0.1);
   glRotatef((GLfloat)fingerBaseL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 1
   glTranslatef(-0.15,0.0,0.0);
   glRotatef((GLfloat)fingerUpL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 2
   glPushMatrix();
   glTranslatef(-1.0,0.165,0.15);
   glRotatef((GLfloat)fingerBaseL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 2
   glTranslatef(-0.15,0.0,0.0);
   glRotatef((GLfloat)fingerUpL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();


   //Draw finger flang 3
   glPushMatrix();
   glTranslatef(-1.0,0.165,0.4);
   glRotatef((GLfloat)fingerBaseL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 3
   glTranslatef(-0.15,0.0,0.0);
   glRotatef((GLfloat)fingerUpL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 4
   glPushMatrix();
   glTranslatef(-1.0,0.165,-0.35);
   glRotatef((GLfloat)fingerBaseL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 4
   glTranslatef(-0.15,0.0,0.0);
   glRotatef((GLfloat)fingerUpL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 5
   glPushMatrix();
   glTranslatef(-1.0, -0.2, -0.1);
   glRotatef((GLfloat)fingerBaseL, 0.0, 0.0, 1.0);
   glTranslatef(-0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 5
   glTranslatef(-0.15,0.0,0.0);
   glRotatef((GLfloat)fingerUpL, 0.0, 0.0, 1.0);
   glTranslatef( -0.15,0.0,0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   glPopMatrix();

   //Right upper leg

   glPushMatrix();

   glTranslatef ( -0.75,-1.25,0.0);
   glRotatef ((GLfloat) upper_legRx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) upper_legRz, 0.0, 0.0, 1.0);
   glTranslatef (0.0,-0.8,0.0);

   glPushMatrix();
   glScalef (0.5, 1.6, 1.0);
   glutWireCube (1.0);

   glPopMatrix();

   //Right lower leg
   glTranslatef (0.0, -0.8,0.0);
   glRotatef ((GLfloat) lower_legRx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) lower_legRz, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.8,0.0);

   glPushMatrix();
   glScalef (0.5, 1.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Right Foot

   glTranslatef (0.0,-0.8,0.0);
   glRotatef ((GLfloat) footRx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) footRz, 0.0, 0.0, 1.0);
   glTranslatef (0.0,-0.25,0.0);

   glPushMatrix();

   glScalef (0.5,0.5, 1.5);
   glutSolidCube(1.0);
   glPopMatrix();

    glPopMatrix();

   //Left upper leg
   glPushMatrix();

   glTranslatef ( 0.75, -1.25,0.0);
   glRotatef ((GLfloat) upper_legLx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) upper_legLz, 0.0, 0.0, 1.0);
   glTranslatef (0.0 ,-0.8,0.0);

   glPushMatrix();
   glScalef (0.5, 1.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Left lower leg

   glTranslatef (0.0, -0.8,0.0);
   glRotatef ((GLfloat) lower_legLx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) lower_legLz, 0.0, 0.0, 1.0);
   glTranslatef (0.0,-0.8,0.0);

   glPushMatrix();
   glScalef (0.5, 1.6, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //Left Foot
   glTranslatef (0.0, -0.8,0.0);
   glRotatef ((GLfloat) footLx, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) footLz, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.25,0.0);

   glPushMatrix();
   glScalef (0.5,0.5, 1.5);
   glutSolidCube(1.0);
   glPopMatrix();
   glPopMatrix();

   glPopMatrix();

   glPopMatrix();

	glutSwapBuffers();
}


void Step_Forward(int)
{
    switch(state)
    {
    case 1 :
        {
            upper_legRx = (upper_legRx - 1) % 360;
            lower_legRx = (lower_legRx + 1) % 360;
            shoulderLz = (shoulderLz + 1) % 360;
            shoulderRz = (shoulderRz + 1) % 360;
            z_position += 0.05;
            lower_legLx = (lower_legLx + 1) % 360;
            if(upper_legRx <= -20)
                state = 2;
            glutTimerFunc(1000/60,Step_Forward,0);
            break;
        }
    case 2 :
        {
            upper_legRx = (upper_legRx + 1) % 360;
            lower_legRx = (lower_legRx - 1) % 360;
            shoulderLz = (shoulderLz - 1) % 360;
            shoulderRz = (shoulderRz - 1) % 360;
            z_position += 0.05;
            lower_legLx = (lower_legLx - 1) % 360;
            if(upper_legRx >= 0)
                state = 3;
            glutTimerFunc(1000/60,Step_Forward,0);
            break;
        }

    case 3 :
        {
            if(z_position < 8)
            state = 1;
            break;
        }

    }
    glutPostRedisplay();

}


void Step_Backward(int)
{
    switch(state)
    {
    case 1 :
        {
            upper_legRx = (upper_legRx - 1) % 360;
            lower_legRx = (lower_legRx + 1) % 360;
            shoulderLz = (shoulderLz + 1) % 360;
            shoulderRz = (shoulderRz + 1) % 360;
            z_position -= 0.05;
            lower_legLx = (lower_legLx + 1) % 360;
            if(upper_legRx <= -20)
                state = 2;
            glutTimerFunc(1000/60,Step_Backward,0);
            break;
        }
    case 2 :
        {
            upper_legRx = (upper_legRx + 1) % 360;
            lower_legRx = (lower_legRx - 1) % 360;
            shoulderLz = (shoulderLz - 1) % 360;
            shoulderRz = (shoulderRz - 1) % 360;
            z_position -= 0.05;
            lower_legLx = (lower_legLx - 1) % 360;
            if(upper_legRx >= 0)
                state = 3;
            glutTimerFunc(1000/60,Step_Backward,0);
            break;
        }

    case 3 :
        {
            if(z_position > -8)
            state = 1;
            break;
        }

    }
    glutPostRedisplay();

}

int flag = 0;
void Turn_Left(int)
{
    switch(flag)
    {
    case 1:
        {
            if(Body_Rot < 90)
            Body_Rot = (Body_Rot + 1) % 360;
            glutTimerFunc(1000/60,Turn_Left,0);
            glutPostRedisplay();
            break;
        }
    case 2:
        {
            if(Body_Rot < 180)
            Body_Rot = (Body_Rot + 1) % 360;
            glutTimerFunc(1000/60,Turn_Left,0);
            glutPostRedisplay();
            break;
        }

    case 3:
        {
            if(Body_Rot < 270)
            Body_Rot = (Body_Rot + 1) % 360;
            glutTimerFunc(1000/60,Turn_Left,0);
            glutPostRedisplay();
            break;
        }

    case 4:
        {
            if(Body_Rot < 359)
            {
                Body_Rot = (Body_Rot + 1) % 360;
                glutTimerFunc(1000/60,Turn_Left,0);
                glutPostRedisplay();
            }
            else
            {
                Body_Rot = 0;
                flag = 0;
            }
            break;
        }

    glutPostRedisplay();
    }
}

void Step_Forward_x(int)
{
    switch(state)
    {
    case 1 :
        {
            upper_legRx = (upper_legRx - 1) % 360;
            lower_legRx = (lower_legRx + 1) % 360;
            shoulderLz = (shoulderLz + 1) % 360;
            shoulderRz = (shoulderRz + 1) % 360;
            x_position += 0.05;
            lower_legLx = (lower_legLx + 1) % 360;
            if(upper_legRx <= -20)
                state = 2;
            glutTimerFunc(1000/60,Step_Forward_x,0);
            break;
        }
    case 2 :
        {
            upper_legRx = (upper_legRx + 1) % 360;
            lower_legRx = (lower_legRx - 1) % 360;
            shoulderLz = (shoulderLz - 1) % 360;
            shoulderRz = (shoulderRz - 1) % 360;
            x_position += 0.05;
            lower_legLx = (lower_legLx - 1) % 360;
            if(upper_legRx >= 0)
                state = 3;
            glutTimerFunc(1000/60,Step_Forward_x,0);
            break;
        }

    case 3 :
        {
            if(x_position < 16)
            state = 1;
            break;
        }

    }
    glutPostRedisplay();
}

void Step_Backward_x(int)
{
    switch(state)
    {
    case 1 :
        {
            upper_legRx = (upper_legRx - 1) % 360;
            lower_legRx = (lower_legRx + 1) % 360;
            shoulderLz = (shoulderLz + 1) % 360;
            shoulderRz = (shoulderRz + 1) % 360;
            x_position -= 0.05;
            lower_legLx = (lower_legLx + 1) % 360;
            if(upper_legRx <= -20)
                state = 2;
            glutTimerFunc(1000/60,Step_Backward_x,0);
            break;
        }
    case 2 :
        {
            upper_legRx = (upper_legRx + 1) % 360;
            lower_legRx = (lower_legRx - 1) % 360;
            shoulderLz = (shoulderLz - 1) % 360;
            shoulderRz = (shoulderRz - 1) % 360;
            x_position -= 0.05;
            lower_legLx = (lower_legLx - 1) % 360;
            if(upper_legRx >= 0)
                state = 3;
            glutTimerFunc(1000/60,Step_Backward_x,0);
            break;
        }

    case 3 :
        {
            if(x_position > -16)
            state = 1;
            break;
        }

    }
    glutPostRedisplay();
}


int flag_2 = 1;
void Sit_Down(int)
{
    switch(flag_2)
    {
    case 1 :
        {
            if(upper_legRx >= -90)
            {
                upper_legRx = (upper_legRx - 1) % 360;
                lower_legRx = (lower_legRx + 1) % 360;
                y_position -= 0.015;
                elbowRx = (elbowRx - 1) % 360;
                elbowLx = (elbowLx + 1) % 360;
                upper_legLx = (upper_legLx - 1) % 360;
                lower_legLx = (lower_legLx + 1) % 360;
                glutTimerFunc(1000/60,Sit_Down,0);
                glutPostRedisplay();
            }
            else
            {
                flag_2 = 0;
            }
            break;
        }
        glutPostRedisplay();
    }
}
int flag_3 =1 ;
void Stand_up(int)
{
    switch(flag_3)
    {
    case 1 :
        {
            if(upper_legRx <= 0)
            {
                upper_legRx = (upper_legRx + 1) % 360;
                lower_legRx = (lower_legRx - 1) % 360;
                y_position += 0.015;
                elbowRx = (elbowRx + 1) % 360;
                elbowLx = (elbowLx - 1) % 360;
                upper_legLx = (upper_legLx + 1) % 360;
                lower_legLx = (lower_legLx - 1) % 360;
                glutTimerFunc(1000/60,Stand_up,0);
                glutPostRedisplay();
            }
            else
            {
                flag_3 = 0;
            }
            break;
        }
    glutPostRedisplay();
    }
}
int position = 1;
void interact(int)
{
   switch(position)
   {
   case 1:
    {
        if (shoulderRz > -100 )
        {
            shoulderRz = (shoulderRz - 1) % 360;
            //std::cout<<shoulderRz<<std::endl;
            shoulderLz = (shoulderLz + 1) % 360;
            obj_pos += 0.05;
            glutTimerFunc(1000/60,interact,0);
            glutPostRedisplay();
        }
        else
        {
            position = 0;
        }
        break;
    }
    glutPostRedisplay();
   }
}

int position_2 = 1;
void interact_2(int)
{
    switch(position_2)
    {
    case 1:
    {
        if (shoulderRz <= -70)
        {
            shoulderRz = (shoulderRz + 1) % 360;
            shoulderLz = (shoulderLz - 1) % 360;
            obj_pos -= 0.05;
            glutTimerFunc(1000/60,interact_2,0);
            glutPostRedisplay();
        }
        else
        {
            position_2 = 0;
        }
        break;
    }
    glutPostRedisplay();
    }
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	// List all your keyboard keys from assignment two her for body movement
	switch (key)
	{
	case 'm':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBack();
		glutPostRedisplay();
		break;
	default:
		break;
	}

	switch (key)
   {

    case 'v':
    {
        position = 1;
        glutTimerFunc(0,interact,0);
       break;
    }
    case 'V':
    {
        position_2 = 1;
        glutTimerFunc(0,interact_2,0);
       break;
    }
    case 'p':
    {
       glutTimerFunc(0,Step_Forward,0);
       break;
    }
    case 'P':
    {
       glutTimerFunc(0,Step_Backward,0);
       break;
    }

    case 'w':
    {
       flag += 1 ;
       glutTimerFunc(0,Turn_Left,0);
       break;
    }
    case 'n' :
        {
          if (shoulderRz > -100 ){
          shoulderRz = (shoulderRz - 5) % 360;
          shoulderLz = (shoulderLz + 5) % 360;
          glutPostRedisplay();}
          break;
        }
    case 'N':
        {
          if (shoulderRz <= 0 ){
          shoulderRz = (shoulderRz + 5) % 360;
          shoulderLz = (shoulderLz - 5) % 360;
          glutPostRedisplay();}
          break;
        }
    case 'i':
        {
          glutTimerFunc(0,Step_Forward_x,0);
          break;
        }
    case 'I':
        {
          glutTimerFunc(0,Step_Backward_x,0);
          break;
        }
    case 'y':
        {
          flag_2 = 1 ;
          glutTimerFunc(0,Sit_Down,0);
          break;
        }
    case 'Y':
        {
          flag_3 = 1;
          glutTimerFunc(0,Stand_up,0);
          break;
        }
   case 's':{
       if (shoulderRx < 60){
      shoulderRx = (shoulderRx + 5) % 360;
      shoulderLx = (shoulderLx - 5) % 360;
      glutPostRedisplay();}
      break;}
   case 'S':{
       if (shoulderRx > -90 ){
      shoulderRx = (shoulderRx - 5) % 360;
      shoulderLx = (shoulderLx + 5) % 360;
      glutPostRedisplay();}
      break;}
   case 'e':{
      if (elbowR < 150){
      elbowR = (elbowR + 5) % 360;
      elbowL = (elbowL - 5) % 360;
      glutPostRedisplay();}
      break;}
   case 'E':{
       if(elbowR > 0){
      elbowR = (elbowR - 5) % 360;
      elbowL = (elbowL + 5) % 360;
      glutPostRedisplay();}
      break;}
   case 'f':{
    if (fingerBaseR < 0)
   {
      fingerBaseR = (fingerBaseR + 5) % 360;
      fingerBaseL = (fingerBaseL - 5) % 360;
      glutPostRedisplay(); }
      break;}
   case 'F':{
      if(fingerBaseR > -90){
      fingerBaseR = (fingerBaseR - 5) % 360;
      fingerBaseL = (fingerBaseL + 5) % 360;
      glutPostRedisplay();}
      break;}
      case 'g':{
          if(fingerUpR < 0){
      fingerUpR = (fingerUpR + 5) % 360;
      fingerUpL = (fingerUpL - 5) % 360;
      glutPostRedisplay();}
      break;}
   case 'G':{
       if (fingerUpR > -90){
      fingerUpR = (fingerUpR - 5) % 360;
      fingerUpL = (fingerUpL + 5) % 360;
      glutPostRedisplay();}
      break;}

    case 'r':{
       if (upper_legRz > -90){
      upper_legRz = (upper_legRz - 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'R':{
       if (upper_legRz < 0){
      upper_legRz = (upper_legRz + 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'l':{
       if (upper_legLz < 90){
      upper_legLz = (upper_legLz + 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'L':{
       if (upper_legLz > 0){
      upper_legLz = (upper_legLz - 5) % 360;
      glutPostRedisplay();}
      break;}


    case 'q':{
       if (upper_legRx > -90){
      upper_legRx = (upper_legRx - 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'Q':{
       if (upper_legRx < 0){
      upper_legRx = (upper_legRx + 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'a':{
       if (upper_legLx > -90){
      upper_legLx = (upper_legLx - 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'A':{
       if (upper_legLx < 0){
      upper_legLx = (upper_legLx + 5) % 360;
      glutPostRedisplay();}
      break;}


    case 'u':{
       if (lower_legRx < 90){
      lower_legRx = (lower_legRx + 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'U':{
       if (lower_legRx > 0){
      lower_legRx = (lower_legRx - 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'j':{
       if (lower_legLx < 90){
      lower_legLx = (lower_legLx + 5) % 360;
      glutPostRedisplay();}
      break;}
    case 'J':{
       if (lower_legLx > 0){
      lower_legLx = (lower_legLx - 5) % 360;
      glutPostRedisplay();}
      break;}

   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ROOM");

	initRendering("Floors/square.bmp",_textureId);
	init();
	glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutCreateMenu(screen_menu);
	glutAddMenuEntry("Floor_1", '1');
	glutAddMenuEntry("Floor_2", '2');
	glutAddMenuEntry("Default", '3');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
