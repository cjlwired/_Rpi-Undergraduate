#include "App.h"
#include "GripControl.h"
#include "SDL_opengl.h"
#include "DVC_Graphics.h"
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

//-------------------------------------------------------------------------

// The constructor.

App::App(int argc, char **argv) : DVC_AppGL(argc, argv)
{
	//////////////////
	// CARLOS' CODE //
	//////////////////

	// Set all Dynamical Bodies and Obstacles initially to null.

	grip1 = NULL;
	grip2 = NULL;

	part = NULL;

	ground = NULL;
	ground2 = NULL;

	// Choose which scenario you are intending on loading.

	cout << "Please enter which scenario you wish to load:" << endl << endl;

	int choice;

	cin >> choice;

	cout << endl;

	// Scenario 1 = Regular, flat plane with a normal car.

	if (choice == 1)
	{
		partName   = "car_Normal";
		groundName = "S1_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	// Scenario 2 = Ramp jump with a normal car.

	else if (choice == 2)
	{
		partName   = "car_Normal";
		groundName = "S2_ground-1";
		ground2Name = "S2_ground-2";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	// * Revert to Scenario 1 as a default in case of invalid input.

	else
	{
		partName   = "car_Normal";
		groundName = "S1_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	grip1Controller = NULL;
	grip2Controller = NULL;

	/////////////////
	//  BEN'S CODE //
	/////////////////

	cout << "Enter time limit for each run: ";

	cin >> timeLimit;

	cout << endl;

	for (int i=0;i<timeLimit;i++)
		controlPlan.push_back(true);
	lastTimeStep = -1;

	cout << "Enter X-Position of Goal: ";
	cin  >> goal;
	cout << endl;

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
	double carX = part->GetQ()[0];
	double carY = part->GetQ()[1];

	int t = (int) sim.GetSimTime();	// current second

	////// GOAL CONDITIONS:

	if (carX >= goal)
		cout << "GOAL MET!" << endl;

	//////

	
	if(t != lastTimeStep){			// if current second changed since last step
		lastTimeStep = t;
		cout<<t<<"\n";

		if(t>=timeLimit){			// if time limit met
			if(IncrementControlPlan()){		// if increment doesn't overflow
				DVC_AppGL::KeyDown('l');	// restart sim with new control plan
			}
			else{							// otherwise, control plan overflowed (all plans tried)
				DVC_AppGL::KeyDown('p');	// pause simulations
			}
		}
		else{						// otherwise, if time limit not met yet
			if (controlPlan[t]){			// if control plan says go forward at this time
				if (grip1Controller &&grip2Controller) {
				  grip1Controller->EnablePD();	// set grip 1 to go forward
				  grip2Controller->EnablePD();	// set grip 2 to go forward
				}
			}
			else{							// else, the grips go backward
				grip1Controller->DisablePD();
				grip2Controller->DisablePD();
			}
		}
	}


	// Camera Controller //
	gfxObj_.CenterPoint(carX, carY);
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
	else if (key == 'q') {
		//Enable all or disable all PD controllers
		if (grip1Controller->IsPDEnabled()) grip1Controller->DisablePD();
		else grip1Controller->EnablePD();

		if (grip2Controller->IsPDEnabled()) grip2Controller->DisablePD();
		else grip2Controller->EnablePD();
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
		cout << "Error, DVC_AppGL failed to initialize." << std::endl;
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
	if ( !FindBodies() )
	{
		cout << "Could not find bodies." << endl;
		return false;
	}
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
		//std::cout << "Error finding body in simulation: " << grip1Name << std::endl;
		//return false;
	}
	if ( !sim.GetBodyByNameMutable(grip2Name, grip2) )
	{
		//std::cout << "Error finding body in simulation: " << grip2Name << std::endl;
		//return false;
	}
	if ( !sim.GetBodyByNameMutable(partName, part) )
	{
		//std::cout << "Error finding body in simulation: " << partName << std::endl;
		//return false;
	}
	if ( !sim.GetBodyByNameMutable(groundName, ground) )
	{
		//std::cout << "Error finding body in simulation: " << groundName << std::endl;
		//return false;
	}

	if ( !sim.GetBodyByNameMutable(ground2Name, ground2) )
	{
		//std::cout << "Error finding body in simulation: " << ground2Name << std::endl;
		//return false;
	}

	return true;
}

//-------------------------------------------------------------------------

////  Ben's Code

/// Increment Control Plan (though technically it's decrementing)///
/// if CP overflows (i.e. all plans exhausted) return FALSE
/// else, return TRUE
bool App::IncrementControlPlan(){
	for(int i=timeLimit-1;i>-1;i--){
		if(controlPlan[i]){
			controlPlan[i]=false;
			return(true);
		}
		else{
			controlPlan[i]=true;
		}
	}
	return(false);
}

