#include <iostream>
#include <gl/glut.h>
#include <cmath>

GLint nNumPoints=5;
GLfloat centerPoints[4][4][3]= {{{  0.0f, 0.0f, -1.0f},
{8.0f, 0.0f, -1.0f},
{16.0f, 0.0f, -1.0f },
{24.0f, 0.0f, -1.0f }},

{{0.0f, 8.0f, -1.0f},
{8.0f, 8.0f, -1.0f},
{16.0f, 8.0f, -1.0f },
{24.0f, 8.0f, -1.0f }},

{{ 0.0f, 16.0f, -1.0f},
{8.0f, 16.0f, -1.0f},
{16.0f, 16.0f, -1.0f },
{24.0f, 16.0f, -1.0f }},

{{ 0.0f, 24.0f, -1.0f},
{8.0f, 24.0f, -1.0f},
{16.0f, 24.0f, -1.0f },
{24.0f, 24.0f, -1.0f }}
};


GLfloat ctrlPoints[4][4][3]= {{{  0.0f, 0.0f, -1.0f},
{8.0f, 0.0f, -1.0f},
{16.0f, 0.0f, -1.0f },
{24.0f, 0.0f, -1.0f }},

{{0.0f, 8.0f, -1.0f},
{8.0f, 8.0f, -1.0f},
{16.0f, 8.0f, -1.0f },
{24.0f, 8.0f, -1.0f }},

{{ 0.0f, 16.0f, -1.0f},
{8.0f, 16.0f, -1.0f},
{16.0f, 16.0f, -1.0f },
{24.0f, 16.0f, -1.0f }},

{{ 0.0f, 24.0f, -1.0f},
{8.0f, 24.0f, -1.0f},
{16.0f, 24.0f, -1.0f },
{24.0f, 24.0f, -1.0f }}
};



GLfloat step[4][4][3] = {
	{{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f}},

	{{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 20.0f},
	{ 0.0f, 0.0f, -20.0f},
	{ 0.0f, 0.0f, 0.0f}},


	{{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, -20.0f},
	{ 0.0f, 0.0f, 20.0f},
	{ 0.0f, 0.0f, 0.0f}},
	
	{{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f, 0.0f}},
};

//GLfloat step[4][3][3] = {{
//	{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f}},
//	//{ -1.0f, 0.1f, 1.0f}},
//
//	{{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f}},
//	//{ 0.7f, 0.9f, -1.0f}},
//
//
//	{{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f},
//	{ 0.0f, 0.0f, 0.0f}},
//	//{ 1.0f, 3.0f, -2.0f}},
//};

//variable for timer function
GLfloat angle=45.0;
GLfloat radius=5.0;
const float DEG2RAD=3.14159/180;

GLfloat redC=1.0, blueC=0.0, greenC=0.0; //3 variables for changing color
bool colorPlus=true;



GLfloat rot=36.0;
int count=0;
//This functions is used to super impose the control points over the curve
void DrawPoints(void)
{

	glColor3f(1.0f, 1.0f, 0.0f);
	int i,j;  //Counting variables

	//Set point size larger to make more visible
	glPointSize(5.0f);

	//Loop through all control points for this example
	glBegin(GL_POINTS);
	for(i=0; i<nNumPoints; i++)
		for(j=0; j<4; j++)
			glVertex3fv(ctrlPoints[i][j]);
	glEnd();
}



void 
initlights(void)
{
    GLfloat ambient[] =
    {0.2, 0.2, 0.2, 1.0};
    GLfloat position[] =
    {0.0, 0.0, 2.0, 1.0};
    GLfloat mat_diffuse[] =
    {0.6, 0.6, 0.6, 1.0};
    GLfloat mat_specular[] =
    {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] =
    {50.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

//Called to draw scene
void RenderScene(void)
{
	//Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(redC, greenC, blueC);
	//Save the modelview matrix stack
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//Rotate the mesh around to make it easier to see
	//if(count%3==0)
	//glRotatef(rot++, 1.0f, 1.0f, 0.0f);
	//else if (count%3==1)
	//glRotatef(rot++, 0.0f, 1.0f, 0.0);
//	else
//		glRotatef(rot++, 0.0f, 0.0f, 1.0f);

	//if(rot>=100) rot=0;
	//if(count>=30) count=0;

	//glRotatef(10.0f, 1.0f, 1.0f, 1.0f);


	//Sets up the Bezier
	//This actually only needs to be called once and could go in
	//the setup function
	glMap2f(GL_MAP2_VERTEX_3, //tYPE OF data generated
		0.0f,   //lower u range
		10.0f, //upper u range
		3,   //distance between points in the data
		4,   //dimension in u direction (order)
		0.0f,   //Lower v range
		10.0f, //Upper v range
		12,    //Distance betwen points in the data
		4,   //Dimension in v direction(order)
		&ctrlPoints[0][0][0]);   //array of control points
		
	//Enable the evaluator
	glEnable(GL_MAP2_VERTEX_3);
	glRotatef(10.0f, 1.0f, 1.0f, 0.0f);
	//use higher level functions to mapto a grid, then evaluate the entire thing.

	//Map a grid of 10 points from 0 to 10
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);

	
	//Evaluate the grid, using lines
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);
	//glEnable(GL_AUTO_NORMAL);

	//Draw the control points
	DrawPoints();

	glPopMatrix();

	//Display the image
	glutSwapBuffers();
}


void SetupRC()
{
	int i,j;
		
	//calculate initial control points from center points
	//assumes that z=0 y=0,
	//for (i=0; i<nNumPoints; i++)
	//	for(j=0; j<4; j++)
	//		ctrlPoints[i][j][0]=centerPoints[i][j][0];


	
	//Clear window to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	
	glColor3f(0.0f, 0.0f, 1.0f);

	glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    //initlights();       /* for lighted version only */

    
    initlights();       /* for lighted version only */
}


void ChangeSize(int w, int h)
    {
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-20.0f, 40.0f, -20.0f, 40.0f, -40.0f, 40.0f); // Larger magnitudes means a smaller object

    // Modelview matrix reset
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

/////////////////////////////
// timer functions for animation
void TimerFunction(int value)
{

	int i,j; //counters

	if(colorPlus){ //it's actually color minus for red
		redC-=0.01;
		greenC+=0.01;
	}
	else{
		redC+=0.01;
		greenC-=0.01;
	}


		if(redC>=1.0f) {
			redC=1.0f;
			colorPlus=true;
		}
			if(redC<=0.0f){ 
				redC=0.0;
				colorPlus=false;
			}
	if(greenC>=1.0f) greenC-=0.01;
	if(greenC<0.0f) greenC+=0.01;


	if(angle<360) angle+=0.5;
	else angle=0;

	angle++;

	for(i=0; i<nNumPoints; i++){

		
		for(j=0; j<4; j++)
		{
			if( i==1 && j==1 || i==1 && j==2 || i==2 && j==1 || i==2 && j==2){
				ctrlPoints[i][j][0]=centerPoints[i][j][0]+step[i][j][0]*radius;//*cos(angle*DEG2RAD)*sin(angle*DEG2RAD);
				ctrlPoints[i][j][1]=centerPoints[i][j][1]+step[i][j][0]*radius;//*cos(angle*DEG2RAD);
				ctrlPoints[i][j][2]=centerPoints[i][j][2]+step[i][j][2]*radius*sin(angle*DEG2RAD);//*sin(angle*DEG2RAD);
			}
			/*else{
			//if(i!=0 || i!=nNumPoints-1 || j!=0 || j!=nNumPoints-1){
			ctrlPoints[i][j][0]=centerPoints[i][j][0]+step[i][j][0]*radius;//*cos(angle*DEG2RAD)*sin(angle*DEG2RAD);
			ctrlPoints[i][j][1]=centerPoints[i][j][1]+step[i][j][0]*radius;//*cos(angle*DEG2RAD);
			ctrlPoints[i][j][2]=centerPoints[i][j][2]+step[i][j][2]*radius;//*sin(angle*DEG2RAD);//*sin(angle*DEG2RAD);
			//}
			}*/

		}
	}

	glutPostRedisplay();
	glutTimerFunc(66, TimerFunction, 1);
}


//////////////
// Main functions
void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Bezier 3D");
		SetupRC();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(66, TimerFunction,1);


	glutMainLoop();


}