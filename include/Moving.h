//***************************************************************************
//  Camera based on Vectors
//***************************************************************************

#define PI 3.141592653589
#define PIdiv180 (PI/180.0)

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct Vector3dMove
{
	GLfloat x, y, z;
};
Vector3dMove Vector3dCr(GLfloat x, GLfloat y, GLfloat z);
Vector3dMove NormalizeVector3d(Vector3dMove v);
class Moving
{
public:

	Vector3dMove View;
	Vector3dMove RightVector;
	Vector3dMove Up;
	Vector3dMove Position;

	GLfloat RotatedX, RotatedY, RotatedZ;

public:
	Moving();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render( int tex, int tex1, int tankwheel, int wheel, int wheelout, bool* keys);	//executes some glRotates and a glTranslate command
	//Note: You should call glLoadIdentity before using Render

	void Move(Vector3dMove Direction);
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);

	void MoveForward(GLfloat Distance);
	void MoveUpward(GLfloat Distance);
	void MoveRight(GLfloat Distance);

	void SetRotateX(GLfloat Angle);

	double rrr ;

	void MoveCircular(GLfloat radius, int tex, int tex1, int tankwheel, int wheel, int wheelout, bool* keys);
};


