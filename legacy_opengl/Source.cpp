
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>		// Header File For The GLu32 Library
#include <cmath>
#include <time.h>
#include <texture.h>
#include <camera.h>
#include <Moving.h>
#include <iostream>
#include <vector>
#include <string>


#define M_PI 3.14

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Cntext
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default
char    charArray[] = "Aram AL-Taki";
float	mercuryAngle,venusAngle,earthAngle,marsAngle,jupiterAngle,saturnAngle,uranusAngle,neptuneAngle  = 0.0f;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

bool direction = true;
Camera MyCamera;
Moving moving;
float dz = 1.0, angle1 = 0;
float dz1 = 1.0;
float z = 0, z1 = 0;
double move = 0;
double angle = 0;

char wl[] = "resources/Al_Qibli/qibli_walls_new.bmp";  // Al Qibli Walls
char dn[] = "resources/Al_Qibli/qibli_dn.bmp";	   // Al Qibli Floor
char rd[] = "resources/Al_Qibli/qibli_road.bmp";	   // Al Qibli Road
char rf[] = "resources/Al_Qibli/qibli_roof.bmp";	   // Al Qibli Roof
char wn[] = "resources/Al_Qibli/qibli_window.bmp";	   // Al Qibli Roof
char wlw[] = "resources/Al_Qibli/qibli_walls_window.bmp";	   // Al Qibli Roof
char wl2[] = "resources/Al_Qibli/qibli_walls.bmp";	   // Al Qibli Roof
char sw2[] = "resources/Al_Qibli/side2_walls.bmp";	   // Al Qibli 
char sw[] = "resources/Al_Qibli/side_wall.bmp";	   // Al Qibli Roof
char qd[] = "resources/Al_Qibli/doors.bmp";	   // Al Qibli Roof
char ti[] = "resources/Al_Qibli/doors.bmp";	   // Al Qibli Roof

int qibli_walls, qibli_dn , qibli_road , qibli_roof , qibli_window , qibli_walls2 , qibli_walls_window , side_walls , side2_walls , qibli_door , top_inside;

class Point {
private:
	int x, y, z;
public:
	Point(float x,float y,float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
};

Point qibli = Point(0,0,0);

void glDraw3DCube(Point origin, float length, float height, float width, int colorR , int colorG ,int colorB , bool up , bool right , bool left , bool down , bool front , bool back) {
	glEnable(GL_DEPTH_TEST);
	//Bottom Face
	if (down) {
		glBegin(GL_QUADS); //BOTTOM = RED
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX(), origin.getY(), origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ() + width);
		glVertex3f(origin.getX() , origin.getY(), origin.getZ() + width);
	}
	if (up) {
		//Upper Face
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ() + width);
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ() + width);
	}
	if (left) {  //Front in Project
		//Left Face
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX(), origin.getY(), origin.getZ());
		glVertex3f(origin.getX(), origin.getY(), origin.getZ() + width);
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ() + width);
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ());
	}
	if (right) {   // Back in Project
		//Right Face
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ() + width);
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ() + width);
	}
	if (front) {  //Left in Project
		//Front Face
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX(), origin.getY(), origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ());
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ());
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ());
	}
	if (back) {   //Right in Project
		//Back Face
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(origin.getX(), origin.getY(), origin.getZ() + width);
		glVertex3f(origin.getX(), origin.getY() + height, origin.getZ() + width);
		glVertex3f(origin.getX() + length, origin.getY() + height, origin.getZ() + width);
		glVertex3f(origin.getX() + length, origin.getY(), origin.getZ() + width);
		glEnd();
	}
}
void drawAxes() {
	glBegin(GL_LINES);

	// X-axis (red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	// Y-axis (green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Z-axis (blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glEnd();
}
void glDrawPalestine() {
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.1f, 0.1f); //BLACK PART
	glVertex2f(0.0f, 2.0f);
	glVertex2f(0.0f,1.32f);
	glVertex2f(3.0f, 1.32f);
	glVertex2f(3.0f, 2.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f); //WHITE PART
	glVertex2f(0.0f, 1.32f);
	glVertex2f(3.0f, 1.32f);
	glVertex2f(3.0f, 0.66f);
	glVertex2f(0.0f, 0.66f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 1.0f, 0.0f); //GREEN PART
	glVertex2f(0.0f, 0.0f);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(3.0f, 0.66f);
	glVertex2f(0.0f, 0.66f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0.0f, 0.0f); 
	glVertex2f(0.0f, 2.0f);
	glVertex2f(0.85f, 1.0f);
	glEnd();
}
void drawCircle(float radius, int select) {
	float x, z;
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle <= (2.0f * 3.14f) * 50.0f; angle += 0.1f)
	{
		glLineWidth(0.01f);
		x = radius * cos(angle);
		z = radius * sin(angle);
		glVertex3f(x,0.0f, z);
		switch (select) {
		case(1):
			glColor3ub(116, 123, 129);
			break;
		case(2):
			glColor3ub(255, 50, 50);
			break;
		case(3):
			glColor3ub(2, 60, 120);
			break;
		case(4):
			glColor3ub(230, 125, 110);
			break;
		case(5):
			glColor3ub(188, 175, 178);
			break;
		case(6):
			glColor3ub(171, 96, 74);
			break;
		case(7):
			glColor3ub(172, 229, 238);
			break;
		case(8):
			glColor3ub(75, 112, 221);
			break;
		}
	}
	glEnd();
}
void glDrawSphere(float radius,int slices,int stacks,int red,int green,int blue) {
	float phi, theta;
	float x, y, z;
	for (int i = 0; i < slices; i++) {
		glBegin(GL_POLYGON);
		for (int j = 0; j < stacks; j++) {
			phi = j * 3.14f / stacks;
			theta = i * 2 * 3.14f / slices;
			x = cos(theta) * sin(phi);
			y = cos(phi);
			z = sin(theta) * sin(phi);
			glNormal3f(x, y, z);
			glColor3ub(red,green,blue);
			glVertex3f(x * radius , y * radius + 1, z * radius);
			phi = (j + 1) * 3.14f / stacks;
			x = cos(theta) * sin(phi);
			y = cos(phi);
			z = sin(theta) * sin(phi);
			glNormal3f(x, y, z);
			glColor3ub(red, green, blue);
			glVertex3f(x * radius, y * radius +1 , z * radius);
		}
		glEnd();
	}
}
void glDrawSolarSystem() {
	glPushMatrix();
	//drawAxes();
	drawCircle(1.5f, 1);
	drawCircle(2.5f, 2);
	drawCircle(4.0f, 3);
	drawCircle(5.0f, 4);
	drawCircle(6.5f, 5);
	drawCircle(8.5f, 6);
	drawCircle(10.5f, 7);
	drawCircle(12.5f, 8);

	//Sun
	glDrawSphere(1.2f, 50, 50, 253, 184, 19);

	//Mercury
	glRotatef(mercuryAngle, 0, 1, 0.2);
	mercuryAngle += 0.15f;
	glTranslatef(1.5f, 0, 0);
	glDrawSphere(0.15f, 50, 50, 116, 123, 129);
	glPushMatrix();

	//Venus
	glPopMatrix();
	glPushMatrix();
	glRotatef(venusAngle, 0, 1, 0.2);
	venusAngle += 0.11f;
	glTranslatef(2.5f, 0, 0);
	glDrawSphere(0.25f, 50, 50, 255, 50, 50);

	//Earth
	glPopMatrix();
	glPushMatrix();
	glRotatef(earthAngle, 0, 1, 0.2);
	earthAngle += 0.09f;
	glTranslatef(4.0f, 0, 0);
	glDrawSphere(0.35f, 50, 50, 2, 60, 120);

	//Mars
	glPopMatrix();
	glPushMatrix();
	glRotatef(marsAngle, 0, 1, 0.2);
	marsAngle += 0.08f;
	glTranslatef(5.0f, 0, 0);
	glDrawSphere(0.3f, 50, 50, 230, 125, 110);

	//Jupiter
	glPopMatrix();
	glPushMatrix();
	glRotatef(jupiterAngle, 0, 1, 0.2);
	jupiterAngle += 0.06f;
	glTranslatef(6.5f, 0, 0);
	glDrawSphere(0.7f, 50, 50, 188, 175, 178);

	//Saturn
	glPopMatrix();
	glPushMatrix();
	glRotatef(saturnAngle, 0, 1, 0.2);
	saturnAngle += 0.045f;
	glTranslatef(8.5f, 0, 0);
	glDrawSphere(0.55f, 50, 50, 171, 96, 74);
	drawCircle(1.0f, 5);

	//Uranus
	glPopMatrix();
	glPushMatrix();
	glRotatef(uranusAngle, 0, 1, 0.2);
	uranusAngle += 0.03f;
	glTranslatef(10.5f, 0, 0);
	glDrawSphere(0.50f, 50, 50, 172, 229, 238);

	//Neptune
	glPopMatrix();
	glPushMatrix();
	glRotatef(neptuneAngle, 0, 1, 0.2);
	neptuneAngle += 0.02f;
	glTranslatef(12.5f, 0, 0);
	glDrawSphere(0.50f, 50, 50, 75, 112, 221);
}
void glApplyTexture() {
	//QIBLI ROAD
	glBindTexture(GL_TEXTURE_2D, qibli_road);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() - 1000.0f, qibli.getY() + 0.0f, qibli.getZ() - 1000.0f);
		glTexCoord2f(300.0f, 0.0f);
		glVertex3f(qibli.getX() + 1000.0f, qibli.getY() + 0.0f, qibli.getZ() - 1000.0f);
		glTexCoord2f(300.0f, 300.0f);
		glVertex3f(qibli.getX() + 1000.0f, qibli.getY() + 0.0f, qibli.getZ() + 1000.0f);
		glTexCoord2f(0.0f, 300.0f);
		glVertex3f(qibli.getX() - 1000.0f, qibli.getY() + 0.0f, qibli.getZ() + 1000.0f);
	glEnd();
	//QIBLI FLOOR
	glBindTexture(GL_TEXTURE_2D, qibli_dn);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.1f, qibli.getZ() + 0.0f);
		glTexCoord2f(30.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.1f, qibli.getZ() + 60.0f);
		glTexCoord2f(30.0f, 30.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.1f, qibli.getZ() + 60.0f);
		glTexCoord2f(0.0f, 30.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.1f, qibli.getZ() + 0.0f);
	glEnd();
	//Door
	glBindTexture(GL_TEXTURE_2D, qibli_door);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 14.7f, qibli.getY() + 0.0f, qibli.getZ() + 22.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 14.7f, qibli.getY() + 15.0f, qibli.getZ() + 22.0f);
		glTexCoord2f(2.0f, 4.0f);
		glVertex3f(qibli.getX() + 14.7f, qibli.getY() + 15.0f, qibli.getZ() + 35.0f);
		glTexCoord2f(0.0f, 4.0f);
		glVertex3f(qibli.getX() + 14.7f, qibli.getY() + 0.0f, qibli.getZ() + 35.0f);
	glEnd();
	//Side Windows
	glBindTexture(GL_TEXTURE_2D, qibli_window);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 20.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(8.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 20.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(8.0f,	2.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 32.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 32.0f, qibli.getZ() + -0.3f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls_window);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 20.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(6.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 20.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(6.0f, 1.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 30.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 30.0f, qibli.getZ() + 60.3f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, side_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(6.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(6.0f, 1.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 20.0f, qibli.getZ() + -0.3f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 20.0f, qibli.getZ() + -0.3f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, side_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(8.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(8.0f, 1.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 20.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 20.0f, qibli.getZ() + 60.3f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, side2_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(4.0f, 1.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 32.0f, qibli.getZ() + 60.3f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 32.0f, qibli.getZ() + 60.3f);
	glEnd();
	//Wooden Roof
	glBindTexture(GL_TEXTURE_2D, top_inside);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 34.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 34.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(10.0f, 6.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 34.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(0.0f, 6.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 34.0f, qibli.getZ() + 60.0f);
	glEnd();
	//Qibli Walls
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 35.0f, qibli.getZ() + 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 35.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 60.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 0.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 35.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(qibli.getX() + 110.0f, qibli.getY() + 35.0f, qibli.getZ() + 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.1f, qibli.getY() + 0.0f, qibli.getZ() + 0.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.1f, qibli.getY() + 0.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(qibli.getX() + 15.1f, qibli.getY() + 35.0f, qibli.getZ() + 60.0f);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(qibli.getX() + 15.1f, qibli.getY() + 35.0f, qibli.getZ() + 0.0f);
	glEnd();
	//Qibli Roof
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(20.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(20.0f, 5.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 37.0f, qibli.getZ() + 18.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 37.0f, qibli.getZ() + 18.0f);
		glTexCoord2f(10.0f, 1.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 37.0f, qibli.getZ() + 32.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 37.0f, qibli.getZ() + 32.0f);
		glTexCoord2f(10.0f, 1.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 32.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(3.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 32.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(3.0f, 1.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 32.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(5.0f, 1.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 32.0f, qibli.getZ() + 62.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 32.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 32.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(5.0f, 1.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 32.0f, qibli.getZ() - 2.0f);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 32.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(5.0f, 1.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() + 62.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 112.0f, qibli.getY() + 35.0f, qibli.getZ() - 2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 37.0f, qibli.getZ() + 18.0f);
		glTexCoord2f(3.0f, 0.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 37.0f, qibli.getZ() + 32.0f);
		glTexCoord2f(3.0f, 3.0f);
		glVertex3f(qibli.getX() + 13.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 37.0f, qibli.getZ() + 18.0f);
		glTexCoord2f(3.0f, 0.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 37.0f, qibli.getZ() + 32.0f);
		glTexCoord2f(3.0f, 3.0f);
		glVertex3f(qibli.getX() + 87.0f, qibli.getY() + 40.0f, qibli.getZ() + 25.0f);
	glEnd();
	//Topping Windows
	glBindTexture(GL_TEXTURE_2D, qibli_window);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(3.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(3.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 37.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 37.0f, qibli.getZ() + 20.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_window);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 35.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(20.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(20.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 37.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 37.0f, qibli.getZ() + 20.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_window);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 35.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(20.0f, 0.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 35.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(20.0f, 1.0f);
		glVertex3f(qibli.getX() + 15.0f, qibli.getY() + 37.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 37.0f, qibli.getZ() + 30.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_window);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 35.0f, qibli.getZ() + 30.0f);
		glTexCoord2f(3.0f, 0.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 35.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(3.0f, 1.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 37.0f, qibli.getZ() + 20.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 85.0f, qibli.getY() + 37.0f, qibli.getZ() + 30.0f);
	glEnd();
	//SIDE BUILDINGS
	glBindTexture(GL_TEXTURE_2D, side_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() -25.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 0.0f, qibli.getZ() - 25.0f);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 0.0f, qibli.getZ() - 25.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 0.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 15.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() - 25.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 15.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 15.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 15.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 15.0f, qibli.getZ() - 25.0f);
	glEnd();
	//SIDE BUILDING 2
	glBindTexture(GL_TEXTURE_2D, side_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 0.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(2.0f, 2.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 0.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 0.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(4.0f, 2.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_walls);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 0.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(4.0f, 2.0f);
		glVertex3f(qibli.getX() + 80.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(qibli.getX() + 65.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
	glEnd();
	//UNDER SPHERE
	glBindTexture(GL_TEXTURE_2D, qibli_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 25.0f, qibli.getZ() - 0.0f);
		glTexCoord2f(4.0f, 2.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(qibli.getX() + 95.0f, qibli.getY() + 25.0f, qibli.getZ() - 15.0f);
	glEnd();
} 
/*
  void glDrawCharacter() {
	gluLookAt(2 + x, 6 + y, 2 + z, 0, 0, 1, 0, 1, 0);
	if (keys[VK_LEFT]) {
		x -= 0.08f;
	}
	if (keys[VK_RIGHT]) {
		x += 0.08f;
	}
	if (keys[VK_UP]) {
		z -= 0.08f;
	}
	if (keys[VK_DOWN]) {
		z += 0.08f;
	}
	if (keys[VK_NUMPAD8]) {
		y += 0.08f;
	}
	if (keys[VK_NUMPAD2]) {
		y -= 0.08f;
	}
	glPushAttrib(GL_CURRENT_BIT);
	glApplySkybox();
	glPopAttrib();

	glTranslatef(0 + x, 0, 0 + z);

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glDraw3DCube(Point(0.0f, 0.0f, 0.0f), 2, 1, 1); //Left Leg
	glDraw3DCube(Point(3.0f, 0.0f, 0.0f), 2, 1, 1); //Right Leg
	glDraw3DCube(Point(0.0f, 2.0f, 0.0f), 1, 4, 0); //Body
	glDraw3DCube(Point(1.0f, 6.0f, 0.0f), 1, 2, 0); //Face
	glDraw3DCube(Point(-1.0f, 4.0f, 0.0f), 2, 1, 1);//Right Hand
	glDraw3DCube(Point(4.0f, 4.0f, 0.0f), 2, 1, 1); //Left Hand
	glPopMatrix();
	glPopAttrib();
	glApplyFaceTexture();
	glApplyJerseyTexture();
}
*/
void glDrawTopping() {
	glBegin(GL_TRIANGLES);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 37, qibli.getZ() + 18);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 37, qibli.getZ() + 32);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 40, qibli.getZ() + 25);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 37, qibli.getZ() + 18);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 37, qibli.getZ() + 32);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 40, qibli.getZ() + 25);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 37, qibli.getZ() + 18);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 40, qibli.getZ() + 25);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 40, qibli.getZ() + 25);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 37, qibli.getZ() + 18);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 37, qibli.getZ() + 32);
	glVertex3f(qibli.getX() + 13, qibli.getY() + 40, qibli.getZ() + 25);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 40, qibli.getZ() + 25);
	glVertex3f(qibli.getX() + 87, qibli.getY() + 37, qibli.getZ() + 32);
	glEnd();
}
void glDrawBridge(float x , float y ,float z) {

}
void glDrawCylinder(Point base,GLfloat radius,GLfloat height,GLubyte R,GLubyte G,GLubyte B) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3ub(R - 40, G - 40, B - 40);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = base.getX() + radius * cos(angle);
		y = base.getZ() + radius * sin(angle);
		glVertex3f(x,height,y);
		glVertex3f(x, 0.0, y);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, height, 0.0);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3ub(R, G, B);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = base.getX() + radius * cos(angle);
		y = base.getZ() + radius * sin(angle);
		glVertex3f(x, height, y);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, height, 0.0f);
	glEnd();
}
void glDrawCylinderSeries() {
	glDrawCylinder(Point(25, 0, 14),2,200,255,255,255);
	glDrawCylinder(Point(35, 0, 14), 2,200,255,255,255);
}
void Key(bool* keys, float speed)
{
	if (keys['S'])
		MyCamera.RotateX(-0.1 * speed);
	if (keys['C'])
		moving.MoveForward(-0.1 * speed);
	if (keys['W'])
		MyCamera.RotateX(0.1 * speed);
	if (keys['D'])
		MyCamera.RotateY(-0.11 * speed);
	if (keys['T'])
		moving.RotateX(0.1 * speed);
	if (keys['Y']) {
		moving.RotateY(0.1 * speed);
		moving.rrr--;
	}
	if (keys['M'] && !direction)
		direction = true;
	if (keys['M'] && direction)
		direction = false;
	if (keys['Z'])
		MyCamera.RotateZ(0.1 * speed);
	if (keys['X'])
		MyCamera.RotateZ(-0.1 * speed);
	if (keys['A'])
		MyCamera.RotateY(0.1 * speed);

	if (direction) {
		if (keys[VK_UP]) {
			MyCamera.MoveForward(0.3 * speed);
			move += 0.1;
			angle -= 0.30;

			if (abs(z) == 25) {
				dz = -dz;
			}
			z += dz;
		}
		if (keys[VK_DOWN]) {

			MyCamera.MoveForward(-0.3 * speed);
			move -= 0.1;
			angle += 0.30;
			if (abs(z) == 25) {
				dz = -dz;
			}
			z += dz;

		}
	}
	else {
		if (keys[VK_UP]) {
			MyCamera.MoveForward(0.1 * speed);
			move -= 0.1;
		}
		if (keys[VK_DOWN]) {
			MyCamera.MoveForward(-0.1 * speed);
			move += 0.1;
		}
	}
	if (keys['N'])
		MyCamera.MoveForward(0.1 * speed);
	if (keys['B'])
		MyCamera.MoveForward(-0.1 * speed);
	if (keys[VK_RIGHT]) {
		MyCamera.MoveRight(0.3 * speed);
		angle1 += 0.30;

		if (abs(z1) == 10) {
			dz1 = -dz1;
		}
		z1 += dz1;
	}
	if (keys[VK_LEFT]) {
		MyCamera.MoveRight(-0.3 * speed);
		angle1 -= 0.30;
		if (abs(z1) == 10) {
			dz1 = -dz1;
		}
		z1 += dz1;
	}
	if (keys['K'])
		MyCamera.MoveForward(-1 * speed);
	if (keys['I'])
		MyCamera.MoveForward(1 * speed);
	if (keys['L'])
		MyCamera.MoveRight(0.3 * speed);
	if (keys['J'])
		MyCamera.MoveRight(-0.3 * speed);

	if (keys['E'])
		MyCamera.MoveUpward(0.1 * speed);
	if (keys['C'])
		MyCamera.MoveUpward(-0.1 * speed);

}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

bool started = false;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	//SKYBOX TEXTURE

	qibli_dn = LoadTexture(dn, 255);
	qibli_walls = LoadTexture(wl, 255);
	qibli_walls2 = LoadTexture(wl2, 255);
	qibli_road = LoadTexture(rd, 255);
	qibli_roof = LoadTexture(rf,255);
	qibli_window = LoadTexture(wn, 255);
	qibli_walls_window = LoadTexture(wlw, 255);
	side_walls = LoadTexture(sw,255);
	side2_walls = LoadTexture(sw2, 255);
	qibli_door = LoadTexture(qd, 255);
	top_inside = LoadTexture(ti, 255);

	MyCamera = Camera();
	MyCamera.Position.x = 0;
	MyCamera.Position.y = 5;
	MyCamera.Position.z = 0;
	moving = Moving();
	moving.Position.x = 0;
	moving.Position.y = 0;
	moving.Position.z = 0;
	return TRUE;										// Initialization Went OK
}
int colors[3];

int DrawGLScene(GLvoid)                  // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(-1, -1, -8);

	MyCamera.Render();
	Key(keys, 1);

	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	glDraw3DCube(Point(qibli.getX() + 15, qibli.getY() + 0, qibli.getZ() + 0),70 /* X */,35 /* Y */,20 /* Z */, 180 , 150, 100, 1, 0, 0, 1, 1, 0);
	glDraw3DCube(Point(qibli.getX() + 15, qibli.getY() + 0, qibli.getZ() + 20), 70 /* X */, 37 /* Y */, 10 /* Z */, 160, 150, 100, 1, 0, 0, 1, 0, 0);
	glDraw3DCube(Point(qibli.getX() + 15, qibli.getY() + 0, qibli.getZ() + 30), 70 /* X */, 35 /* Y */, 8 /* Z */, 140, 150, 100, 1, 0, 0, 1, 0, 0);
	glDraw3DCube(Point(qibli.getX() + 15, qibli.getY() + 0, qibli.getZ() + 38), 70 /* X */, 35 /* Y */, 22 /* Z */, 120, 150, 100, 1, 0, 0, 1, 0, 1);
	glDraw3DCube(Point(qibli.getX() + 85, qibli.getY() + 0, qibli.getZ() + 0), 25 /* X */, 35 /* Y */, 38 /* Z */, 100, 150, 100, 1, 0, 0, 1, 1, 0);
	glDraw3DCube(Point(qibli.getX() + 85, qibli.getY() + 0, qibli.getZ() + 38), 25 /* X */, 35 /* Y */, 22 /* Z */, 80, 150, 100, 1, 1, 0, 1, 0, 1);
	glDraw3DCube(Point(qibli.getX() + 95 ,qibli.getY() + 35,qibli.getZ() + 20),10,2,10,231,207,137,1,1,1,1,1,1);
	glDraw3DCube(Point(qibli.getX() + 65, qibli.getY() + 0, qibli.getZ() - 15),15,25,15,255,255,255,1,1,1,1,1,1);
	glDraw3DCube(Point(qibli.getX() + 80, qibli.getY() + 0, qibli.getZ() - 25), 15, 15, 25, 255, 255, 255, 1, 1, 1, 1, 1, 1);
	glDrawTopping();
	glTranslatef(100,37,25);
	glDrawSphere(5,200,50,40,40,41);
	//glDraw3DCube(Point(65, 0, -15), 10 /* X */, 15 /* Y */, 15 /* Z */, 80, 150, 100, 1, 1, 1, 1, 1, 1);
	glTranslatef(0, 0, 0);
	glPopMatrix();
	glPopAttrib();
	
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glApplyTexture();
	glPopMatrix();
	glPopAttrib();

	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,								// Message For This Window
	WPARAM	wParam,								// Additional Message Information
	LPARAM	lParam)								// Additional Message Information
{
	float angle = 1.0f;
	if (keys[VK_UP])
	{
		glRotatef(angle, 0, 1, 0);
		angle += 0.1f;
	}

	switch (uMsg)								// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:						// Screensaver Trying To Start?
		case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow(charArray,640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow(charArray, 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
