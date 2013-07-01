#pragma once

#include "DVC_AppGL.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class GripControl; // forward declare GripControl class

class App : public DVC_AppGL {

public:

	App(int argc=0, char **argv=0);	// constructor taking optional command line arguments
	~App();	// destructor


	bool Init();
	void PostStep();
	void Render();
	bool ReloadScene();
	void KeyDown( char key );

	void MouseDown(int x, int y, int button) 
	{ 
		DVC_AppGL::MouseDown(x, y, button); 
		printf("%f %f\n",mouseControl_.worldX_, mouseControl_.worldY_); 
	}

protected:


private:

	bool FindBodies();
	bool AddControllers();
	void DeleteControllers();


	std::string grip1Name;
	std::string grip2Name;
	std::string partName;
	std::string groundName;
	std::string ground2Name;	// Carlos' code

	DynamicalBody * grip1;
	DynamicalBody * grip2;
	DynamicalBody * part;
	Obstacle * ground;
	Obstacle * ground2;			// Carlos' code
	
	GripControl * grip1Controller;
	GripControl * grip2Controller;

	///// Ben's code
	bool IncrementControlPlan();

	int timeLimit;
	vector<bool> controlPlan;
	int lastTimeStep;

	////
	double goal;

};



