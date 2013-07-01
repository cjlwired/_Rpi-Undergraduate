
#include "App.h"
#include "GripControl.h"
#include "SDL_opengl.h"
#include "DVC_Graphics.h"
#include <iostream>
#include <sstream>
#include <math.h>

//-------------------------------------------------------------------------

// The constructor.
App::App(int argc, char **argv) : DVC_AppGL(argc, argv)
{
	grip1 = NULL;
	grip2 = NULL;
	part = NULL;
	ground = NULL;

	grip1Name = "grip1";
	grip2Name = "grip2";

	partName = "part";
	groundName = "ground";

	grip1Controller = NULL;
	grip2Controller = NULL;

}

//-------------------------------------------------------------------------

// The destructor.
App::~App()
{
	DeleteControllers();
}

//-------------------------------------------------------------------------

// This method demonstrates how to draw
// debugging information to the screen.
void App::Render()
{
	//First call the super class's render method.
	DVC_AppGL::Render();


}

//-------------------------------------------------------------------------

// This method is called after each timestep, but before rendering.
// This is probably the best place to write your code.
// If you want, you can add a PreStep method and it will be called
// before each timestep.
void App::PostStep()
{

	//this->gfxObj_.ResetCamera();
	double carX = part->GetQ()[0];
	double carY = part->GetQ()[1];

	//this->gfxObj_.MoveCamera(carX,carY);

}

//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

// The method handles key presses from the keyboard.
void App::KeyDown( char key )
{

	// Keys:
	//
	// f - toggle friction on or off
	// v - toggle draw debug lines and points
	// z - select grip 1
	// x - select grip 2
	// y - select grip 3
	// z - select grip 4
	// q - set PD targets to the part's center of gravity,
	//     then enable or disable all PD controllers
	//
	// Note when a grip is selected you can move it around using the arrow keys.
	// 

	if (key == 'f') {
	
	}
	else {
		 //If we have not used the key press, pass the key to the super class
		DVC_AppGL::KeyDown(key);
	}
}

//-------------------------------------------------------------------------

// This method creates and attaches the force controllers
// to the grippers.  You probably won't need to modify this
// method unless you change the arguments to the force
// controller's constructor.  Consider using get/set methods instead.
bool App::AddControllers()
{
	//create and set a force controller for grip1
	grip1Controller = new GripControl();
	if ( !sim.SetBodyControllerByName( grip1Name, *grip1Controller) )
	{
		std::cout << "Error adding force controller to body: " << grip1Name << std::endl;
		delete grip1Controller;
		return false;
	}
	//create and set a force controller for grip2
	grip2Controller = new GripControl();
	if ( !sim.SetBodyControllerByName( grip2Name, *grip2Controller) )
	{
		std::cout << "Error adding force controller to body: " << grip2Name << std::endl;
		delete grip2Controller;
		return false;
	}


	return true;	
}


//-------------------------------------------------------------------------

// The init method.
bool App::Init()
{
	//Call the super class's Init method.
	//Be aware that the super class's Init method will
	//call ReloadScene
	if ( !DVC_AppGL::Init() )
	{
		std::cout << "Error, DVC_AppGL failed to initialize." << std::endl;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------

// This method is called whenever
// the scene is reloaded.  You can reload the
// scene by pressing 'L'.  Note, all the pointers
// to the bodies and controllers are changed
// when the scene reloads, so be careful!
bool App::ReloadScene()
{
	if ( !DVC_AppGL::ReloadScene() ) return false;
	DeleteControllers();
	if ( !FindBodies() ) return false;
	if ( !AddControllers() ) return false;
	return true;
}

//-------------------------------------------------------------------------

// Deletes the controllers
void App::DeleteControllers()
{
	delete grip1Controller;
	delete grip2Controller;
}

//-------------------------------------------------------------------------

// Gets the bodies from the simulator and sets pointers.
bool App::FindBodies()
{
	if ( !sim.GetBodyByNameMutable(grip1Name, grip1) )
	{
		std::cout << "Error finding body in simulation: " << grip1Name << std::endl;
		return false;
	}
	if ( !sim.GetBodyByNameMutable(grip2Name, grip2) )
	{
		std::cout << "Error finding body in simulation: " << grip2Name << std::endl;
		return false;
	}
	if ( !sim.GetBodyByNameMutable(partName, part) )
	{
		std::cout << "Error finding body in simulation: " << partName << std::endl;
		return false;
	}
	if ( !sim.GetBodyByNameMutable(groundName, ground) )
	{
		std::cout << "Error finding body in simulation: " << groundName << std::endl;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------



