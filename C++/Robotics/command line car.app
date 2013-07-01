#include "App.h"
#include "GripControl.h"
#include "SDL_opengl.h"
#include "DVC_Graphics.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace std;

int timeInterval = 4;

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
	ground3 = NULL;

	gravel = NULL;
	gravel2 = NULL;
	gravel3 = NULL;

	// Choose which scenario you are intending on loading.

	//cout << "Please enter which scenario you wish to load:" << endl << endl;

	//cin >> choice;
	choice = atoi(argv[1]);
	//cout << endl;

	// Scenario 1 = Regular, flat plane with a normal car.

	if (choice == 0)
	{
		partName   = "car_Normal";
		groundName = "S1_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	// Scenario 2 = Ramp jump with a normal car.

	else if (choice == 1)
	{
		partName   = "car_Normal";
		groundName = "S2_ground-1";
		ground2Name = "S2_ground-2";
		ground3Name = "S2_ground-3";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 2)
	{
		partName   = "car_Big_Wheel";
		groundName = "S2_ground-1";
		ground2Name = "S2_ground-2";
		ground3Name = "S2_ground-3";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 3)
	{
		partName   = "car_Weird_Wheel";
		groundName = "S2_ground-1";
		ground2Name = "S2_ground-2";
		ground3Name = "S2_ground-3";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 4)
	{
		partName   = "car_Normal";
		groundName = "S3_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 5)
	{
		partName   = "car_Big_Wheel";
		groundName = "S3_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 6)
	{
		partName   = "car_Weird_Wheel";
		groundName = "S3_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";

		gravelName = "gravel";
		gravel2Name = "gravel2Name";
		gravel3Name = "gravel3Name";
	}

	else if (choice == 7)
	{
		partName   = "car_Normal";
		groundName = "S4_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 8)
	{
		partName   = "car_Big_Wheel";
		groundName = "S4_ground";

		grip1Name = "grip1";
		grip2Name = "grip2";
	}

	else if (choice == 9)
	{
		partName   = "car_Weird_Wheel";
		groundName = "S4_ground";

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

	//cout << "Enter time limit for each run: ";

	//cin >> timeLimit;
	timeLimit = atoi(argv[2]);
	timeLimit *= timeInterval;

	//cout << endl;

	for (int i=0;i<timeLimit;i++)
		controlPlan.push_back(true);


	lastTimeStep = -1;
	lastX = -1; // NEW

	//cout << "Enter X-Position of Goal: ";
	//cin  >> goal;
	goal = atoi(argv[3]);
	//cout << endl;

	/// SUPER NEW
	//cout << "Choose simulation mode: ";
	//cin >> mode;
	mode = atoi(argv[4]);
	//cout << endl;

	//cout << "Enter name of output file: ";
	//cin >> filename;
	filename = argv[5];
	//cout << endl;
	if(filename=="none")
		outputon = false;
	else{
		outputon = true;
		file.open( string(filename).c_str() );
		file << "Car Simulation Output File" << endl << endl;
		file << "Scenario " << choice << endl;
		file << "Run time limit: " << timeLimit/timeInterval << endl;
		file << "Total control plan steps: " << timeLimit << endl;
		file << "Goal X-position: " << goal << endl << endl;
	}

	runnum = 1;
	bestTime = 1000000;
	bestDist = 1000000;
	bestRun = 0;

	simDone = false;

	argc_ = 0;

	//DVC_AppGL::SelectScene(choice);
}

//-------------------------------------------------------------------------

// The destructor.
App::~App()
{
	DeleteControllers();
}

//-------------------------------------------------------------------------

// Step Function (for graphicless sims).
int App::Step()
{
	return sim.StepForward();
}

/*bool App::Init()
{

	if ( !ReadPrefs())	//read the preferences, check for error
	{
		return false;
	}
				
	if (!sim.Init(prefs))	//initialize the simulator, check for error
	{
		return false;
	}
	
	FlushSimSettings();		//flush sim settings
	return true;
}*/


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
	//cout<<"Ben";

	double carX = part->GetQ()[0];
	double carY = part->GetQ()[1];

	//cout<<carX;

	int t = (int) (timeInterval * sim.GetSimTime());	// current second
	
	// Goal-Met Recognizer //
	if (carX >= goal){ 
		cout << "\nGOAL MET in " << sim.GetSimTime() << " seconds!\n\n";
		if(sim.GetSimTime()<bestTime){
			bestRun = runnum;
			bestTime = sim.GetSimTime();
			bestControlPlan = controlPlan;
		}
		if(mode == 1){	// stop simulation if in "Stop at First Success Mode"
			SimDone();
		}
		if(mode == 2){ // set new timelimit equal to one after step of succes
			timeLimit = t+1;
		}
		if(IncrementControlPlan(t)){ // increment control plan starting from success point
			if((t+1)<timeLimit)
				FillWithForward(t+1); 
			DVC_AppGL::KeyDown('l'); // restart sim with new control plan 
			runnum++;
		}		 
		else{ // otherwise, control plan overflowed (all plans tried)
			SimDone();
		} 
	}

	// Car-Falling Recognizer //
	else if (carY < 0)
	{ 
		cout << "\nCar is doomed! Starting next run. Died at X-position " << carX <<" during step " << t <<"\n\n"; if(outputon){file << "\nCar fell to its death at X-position "<< carX <<" during control step " << t <<"\n\n";}

		if(IncrementControlPlan(t)){			// increment control plan starting from fail point
			if((t+1)<timeLimit)
				FillWithForward(t+1);
			DVC_AppGL::KeyDown('l');		// restart sim with new control plan
			runnum++;
		}
		else{							// otherwise, control plan overflowed (all plans tried)
			SimDone();
		}
	}
	
	// This is entered once per control interval, at the beginning of the interval
	else if(t != lastTimeStep){	// if current second changed since last step
		//cout<<"X-position: "<<carX<<endl;
		lastTimeStep = t;
		//cout<<t<<"\n";

		// Time-Limit-Reached Recognizer //
		if(t>=timeLimit){			// if time limit met
			cout<<"\nTime limit reached! Died at X-position: "<< carX <<"\n\n"; if(outputon){file<<"\nTime limit met at X-position: "<< carX <<"\n\n";}
			if(IncrementControlPlan(timeLimit-1)){		// if increment doesn't overflow
				DVC_AppGL::KeyDown('l');	// restart sim with new control plan
				runnum++;
			}
			else{							// otherwise, control plan overflowed (all plans tried)
				SimDone();
			}
		}

		// Car-Stuck Recognizer //
		//cout<<"X Difference: "<<abs(carX - lastX)<<endl;
		else if ( abs(carX - lastX) < .003)
		{ 
			cout << "\nCar is stuck at X-position "<< carX <<"  Starting next run. Died during step " << t <<"\n\n"; if(outputon){file<< "\nCar got stuck at step: " << t <<"\n\n";} 
	
			if(IncrementControlPlan(t)){			// increment control plan starting from fail point
				if((t+1)<timeLimit)
					FillWithForward(t+1);
				DVC_AppGL::KeyDown('l');		// restart sim with new control plan
				runnum++;
			}
			else{							// otherwise, control plan overflowed (all plans tried)
				SimDone();
			}
		}
		
		// otherwise, if time limit not met yet and car's not stuck...
		else{
			if (t==0){	// if time 0, we just started a new run, print the new control plan
				if(!(runnum%20) && bestRun != 0){
					cout << "\n*Best So Far Update*\n"; if(outputon){file<< "\n*Best Control Plan so far*\n";}
					cout<<"Best Run: "<<bestRun<<endl; if(outputon) {file<<"Best Run: "<<bestRun <<endl;}
					cout<<"Time: "<<bestTime<<endl; if(outputon){ file << "Best Time: "<<bestTime<<endl;}
					cout<<"Control Plan: "; if(outputon){file<<"Control Plan: ";}
					PrintControlPlan(bestControlPlan);
					cout << "\n\n"; if(outputon){file<< "\n\n";}
				}
				cout << "Run " << runnum << endl; if(outputon){file<< "Run " << runnum << endl;}
				cout << "Control Plan: "; if(outputon){file<< "Control Plan: " << endl;}
				PrintControlPlan(controlPlan); 
			}
			if (controlPlan[t]){	// if control plan says go forward at this time
				if (grip1Controller && grip2Controller) 
				{
				  grip1Controller->EnablePD();	// set grip 1 to go forward
				  grip2Controller->EnablePD();	// set grip 2 to go forward
				}
			}
			else
			{	// else, the grips go backward
				grip1Controller->DisablePD();
				grip2Controller->DisablePD();
			}
		}
		lastX = carX;
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

	DVC_AppGL::SelectScene(choice);	// Load appropriate scene

	return true;
}

bool App::Init2()
{
	if ( !ReadPrefs())	//read the preferences, check for error
	{
		return false;
	}
				
	if (!sim.Init(prefs))	//initialize the simulator, check for error
	{
		return false;
	}
	
	FlushSimSettings();		//flush sim settings
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

	if ( !sim.GetBodyByNameMutable(ground3Name, ground3) )
	{
		//std::cout << "Error finding body in simulation: " << ground3Name << std::endl;
		//return false;
	}

	return true;
}

//-------------------------------------------------------------------------

////  Ben's Code

/// Increment Control Plan (though technically it's decrementing)///
/// if CP overflows (i.e. all plans exhausted) return FALSE
/// else, return TRUE
bool App::IncrementControlPlan(int index)
{
	for(int i=index;i>-1;i--)
	{
		if(controlPlan[i])
		{
			controlPlan[i]=false;
			return(true);
		}
		else
		{
			controlPlan[i]=true;
		}
	}
	return(false);
}

void App::FillWithForward(int index)
{
	for(int i=index;i<timeLimit;i++)
	{
		controlPlan[i]=true;
	}
}

void App::PrintControlPlan(vector<bool> cp)
{ 
	cout<<"["; if(outputon){file<<"[";} 

	cout << cp[0]; if(outputon){file<<cp[0];} 

	for(int i=1;i<timeLimit;i++)
	{ 
		cout <<" " << cp[i];if(outputon){file<<" " <<cp[i];} 
	} 

	cout << "]\n";  if(outputon){file<<"]\n";} 
}

void App::SimDone()
{
	DVC_AppGL::KeyDown('p'); // pause simulation
	cout << "\nSimulation Done!\n"; if(outputon){ file << "\nSimulation Done!\n"; }
	if(bestTime!=1000000){
		cout<<"Best Run: "<<bestRun<<endl; if(outputon) {file<<"Best Run: "<<bestRun <<endl;}
		cout<<"Time: "<<bestTime<<endl; if(outputon){ file << "Best Time: "<<bestTime<<endl;}
		cout<<"Control Plan: "; if(outputon){file<<"Control Plan: ";}
		PrintControlPlan(bestControlPlan);
	}
	//else{
	//	cout<<"Best Distance: ";
	//}
	simDone = true;
}

bool App::DoneCheck()
{
	return(simDone);
}