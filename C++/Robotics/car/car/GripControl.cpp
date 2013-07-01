#include "GripControl.h"
#include <math.h>

//-------------------------------------------------------------------------

GripControl::GripControl()
{ 
	force[0] = 0;
	force[1] = 0;
	force[2] = 0;
	pdEnabled = false;
}

//-------------------------------------------------------------------------

// Disable the PD controller
void GripControl::EnablePD()
{
	pdEnabled = true;
}

//-------------------------------------------------------------------------

// Disable the PD controller
void GripControl::DisablePD()
{
	pdEnabled = false;
}

//-------------------------------------------------------------------------

// Check if PD controller is enabled or not
bool GripControl::IsPDEnabled()
{
	return pdEnabled;
}

//-------------------------------------------------------------------------



//
// Note, this function is const so it cannot
// modify any of its member variables.  It can
// only call member functions that are also const.
//
// @param t the currect simulation time
// @param outForce the output force vector
// @param pos body's current position x,y,theta
// @param nu body's current velocity x,y,theta
void GripControl::GetForce(REAL t, DVC::Vector<REAL> & outForce, const DVC::Vector<REAL> & pos, const DVC::Vector<REAL> & nu) const
{
	//std::cout<<nu[0]<<"\n";

	outForce[0] = 0;	// X force
	outForce[1] = 0;	// Y force
	outForce[2] = 5;	// theta angular force

	// If PD controller is enabled, add the PD control force.
	// The PD controller is implemented as a spring with damping.
	if (pdEnabled)
	{
		outForce[0] = 0;	// X force
		outForce[1] = 0;	// Y force
		outForce[2] = -5;	// theta angular force
	}
}

//-------------------------------------------------------------------------
