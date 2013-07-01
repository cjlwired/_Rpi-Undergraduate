#include "GripControl.h"
#include <math.h>

//-------------------------------------------------------------------------

GripControl::GripControl()
{ 
	force[0] = 0;
	force[1] = 0;
	force[2] = 0;
	pdEnabled = false;
	pdTarget[0] = 0;
	pdTarget[1] = 0;

	// Set default K and C values
	K = 500;
	C = sqrt(K);
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

// Set PD controller's target location
// X position in world frame
// Y position in world frame
void GripControl::SetPDTarget(REAL x, REAL y)
{
	pdTarget[0] = x;
	pdTarget[1] = y;
}

//-------------------------------------------------------------------------

// Set controller constant K
void GripControl::SetK(REAL K)
{
	this->K = K;
}

//-------------------------------------------------------------------------

// Set controller constant C
void GripControl::SetC(REAL C)
{
	this->C = C;
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

	outForce[0] = 0;	// X force
	outForce[1] = 0;	// Y force
	outForce[2] = 0;	// theta angular force

	// If PD controller is enabled, add the PD control force.
	// The PD controller is implemented as a spring with damping.
	if (pdEnabled)
	{
		double springForce[2];
		double dampingForce[2];
		double springRestLength = 0;

		double springEndX = pdTarget[0];
		double springEndY = pdTarget[1];
		double posX = pos[0];
		double posY = pos[1];

		double springLength = dist(posX, posY, springEndX, springEndY);
		double stretch = springLength - springRestLength;
		double sinT = 0;
		double cosT = 0;

		if (springLength != 0)  // Don't divide by zero!
		{
			// sinT and cosT set the spring force in the direction
			// from the body's center of gravity to the spring's end point.
			sinT = (posX - springEndX)/springLength;
			cosT = (posY - springEndY)/springLength;
		}

		springForce[0] = -K*stretch*sinT;
		springForce[1] = -K*stretch*cosT;
		dampingForce[0] = -C*nu[0];
		dampingForce[1] = -C*nu[1];
			
		
		outForce[0] = springForce[0] + dampingForce[0];
		outForce[1] = springForce[1] + dampingForce[1];
	}
}

//-------------------------------------------------------------------------

double GripControl::dist(double x1, double y1, double x2, double y2) const {
	double dx = x2-x1, dy = y2-y1;
	return sqrt(dx*dx + dy*dy);
}


