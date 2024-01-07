
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>

class SkyBox
{
public:
	SkyBox(void);
	~SkyBox(void);


	
	void drawSkyBox(int back, int front, int right, int left, int top,int road, int bottom,double tall){
	
		glBindTexture(GL_TEXTURE_2D, front);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-tall, -50, -2*tall+50);
	glTexCoord2d(1, 0);
	glVertex3d(tall, -50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(tall, 2*tall-50, -2 * tall + 50);
	glTexCoord2d(0, 1);
	glVertex3d(-tall, 2 * tall - 50, -2 * tall + 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, back);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-tall, -50, 50);
	glTexCoord2d(1, 0);
	glVertex3d(tall, -50, 50);
	glTexCoord2d(1, 1);
	glVertex3d(tall, 2 * tall - 50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(-tall, 2 * tall - 50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, left);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-tall, -50, 50);
	glTexCoord2d(1, 0);
	glVertex3d(-tall, -50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(-tall, 2 * tall - 50, -2 * tall + 50);
	glTexCoord2d(0, 1);
	glVertex3d(-tall, 2 * tall - 50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, right);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);
	glVertex3d(tall, -50, 50);
	glTexCoord2d(0, 0);
	glVertex3d(tall, -50, -2 * tall + 50);
	glTexCoord2d(0, 1);
	glVertex3d(tall, 2 * tall - 50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(tall, 2 * tall - 50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, top);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-tall, 2 * tall - 50, -2 * tall + 50);
	glTexCoord2d(1, 0);
	glVertex3d(tall, 2 * tall - 50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(tall, 2 * tall - 50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(-tall, 2 * tall - 50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bottom);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-40, -50, -2 * tall + 50);
	glTexCoord2d(1, 0);
	glVertex3d(40, -50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(40, -50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(-40, -50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bottom);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-40, -50, -2 * tall + 50);
	glTexCoord2d(1, 0);
	glVertex3d(-tall, -50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(-tall, -50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(-40, -50, 50);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bottom);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(40, -50, -2 * tall + 50);
	glTexCoord2d(1, 0);
	glVertex3d(tall, -50, -2 * tall + 50);
	glTexCoord2d(1, 1);
	glVertex3d(tall, -50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(40, -50, 50);
	glEnd();
}
};

