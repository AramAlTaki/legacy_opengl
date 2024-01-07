#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
//#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>

#include "Moving.h"

#include <stdlib.h>   /* for exit */

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3dCr(0.0f,0.0f,0.0f)

Vector3dMove Vector3dCr(GLfloat x, GLfloat y, GLfloat z)
{
	Vector3dMove tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat LengthVector3d(Vector3dMove * v)
{
	return (GLfloat)(sqrt(SQR(v->x) + SQR(v->y) + SQR(v->z)));
}

Vector3dMove NormalizeVector3d(Vector3dMove v)
{
	Vector3dMove res;
	float L = LengthVector3d(&v);
	if (L == 0.0f) return NULL_VECTOR;
	res.x = v.x / L;
	res.y = v.y / L;
	res.z = v.z / L;
	return res;
}

Vector3dMove operator+ (Vector3dMove v, Vector3dMove u)
{
	Vector3dMove res;
	res.x = v.x + u.x;
	res.y = v.y + u.y;
	res.z = v.z + u.z;
	return res;
}
Vector3dMove operator- (Vector3dMove v, Vector3dMove u)
{
	Vector3dMove res;
	res.x = v.x - u.x;
	res.y = v.y - u.y;
	res.z = v.z - u.z;
	return res;
}


Vector3dMove operator* (Vector3dMove v, float r)
{
	Vector3dMove res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

Vector3dMove CrossProduct(Vector3dMove * u, Vector3dMove * v)
{
	Vector3dMove resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
float operator* (Vector3dMove v, Vector3dMove u)	//dot product
{
	return v.x*u.x + v.y*u.y + v.z*u.z;
}




/***************************************************************************************/

Moving::Moving()
{

	Position = Vector3dCr(0.0, 0.0, 0.0);
	View = Vector3dCr(0.0, 0.0, -1.0);
	RightVector = Vector3dCr(1.0, 0.0, 0.0);
	Up = Vector3dCr(0.0, 1.0, 0.0);


	RotatedX = RotatedY = RotatedZ = 0.0;
}

void Moving::Move(Vector3dMove Direction)
{
	Position = Position + Direction;
}

void Moving::RotateX(GLfloat Angle)
{

	RotatedX += Angle;
	//Rotate viewdir around the right vector:
	View = NormalizeVector3d(View*cosf(Angle*PIdiv180) + Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = CrossProduct(&View, &RightVector)*-1;


}

void Moving::RotateY(GLfloat Angle)
{
	RotatedY += Angle;

	// Calculate the new view direction vector
	Vector3dMove tempView = View;
	View = NormalizeVector3d(tempView*cosf(Angle*PIdiv180) - RightVector*sinf(Angle*PIdiv180));
	// Update the right vector
	RightVector = CrossProduct(&View, &Up);
}

void Moving::RotateZ(GLfloat Angle)
{
	RotatedZ += Angle;
	//Rotate viewdir around the right vector:
	RightVector = NormalizeVector3d(RightVector*cosf(Angle*PIdiv180) + Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = CrossProduct(&View, &RightVector)*-1;
}

void Moving::Render( int tex, int tex1, int tankwheel, int wheel, int wheelout, bool* keys)
{
	//calculate view point
	Vector3dMove ViewPoint = Position + View;
	glTranslated(Position.x, Position.y, Position.z);

	//glRotated(ViewPoint.x, 1, 0, 0);
	glRotated(rrr, 0, 1, 0);

	//glRotated(ViewPoint.z, 0, 0, 1);
	//tankbody->drawWholeTank(tex, tex1, tankwheel, wheel, wheelout, keys);
	

}

void Moving::MoveForward(GLfloat Distance)
{
	Position = Position + (View*Distance);
}

void Moving::MoveRight(GLfloat Distance)
{
	Position = Position + (RightVector*Distance);
}

void Moving::MoveUpward(GLfloat Distance)
{
	Position = Position + (Up*Distance);
}

void Moving::SetRotateX(GLfloat Angle)
{

	View = Vector3dCr(0.0, 0.0, -1.0);
	RightVector = Vector3dCr(1.0, 0.0, 0.0);
	Up = Vector3dCr(0.0, 1.0, 0.0);
	RotatedX = Angle;
}

void Moving::MoveCircular(GLfloat radius, int tex, int tex1, int tankwheel, int wheel, int wheelout, bool* keys)
{
	// Calculate current angle
	GLfloat angle = RotatedX + RotatedY * PIdiv180;

	// Calculate object's position along the circle
	GLfloat x = radius * cosf(angle);
	GLfloat y = radius * sinf(angle);
	Position = Vector3dCr(x, 0.0, y);

	// Calculate view direction towards the center
	View = Vector3dCr(0.0 - x, 0.0 - Position.y, 0.0 - y);

	// Normalize view direction for accurate rendering
	View = NormalizeVector3d(View);

	// Update orientation using the calculated view direction
	RightVector = CrossProduct(&View, &Up);
	Up = CrossProduct(&View, &RightVector)*-1;

	// Render the object using updated position and view direction
	Render( tex, tex1, tankwheel, wheel, wheelout, keys);
}