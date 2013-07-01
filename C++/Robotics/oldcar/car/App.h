#pragma once

#include "DVC_AppGL.h"
#include <string>


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

protected:


private:

	bool FindBodies();
	bool AddControllers();
	void DeleteControllers();


	std::string grip1Name;
	std::string grip2Name;
	std::string partName;
	std::string groundName;

	DynamicalBody * grip1;
	DynamicalBody * grip2;
	DynamicalBody * part;
	Obstacle * ground;
	
	GripControl * grip1Controller;
	GripControl * grip2Controller;
};



