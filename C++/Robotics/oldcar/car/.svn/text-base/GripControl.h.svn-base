#pragma once

#include "ForceController.h"
using namespace DVC;



class GripControl : public ForceController {
public: 

	GripControl();

	void EnablePD();
	void DisablePD();
	void SetPDTarget(REAL x, REAL y);
	bool IsPDEnabled();
	void SetK(REAL K);
	void SetC(REAL C);
	void GetForce(REAL t, DVC::Vector<REAL> & outForce, const DVC::Vector<REAL> & pos, const DVC::Vector<REAL> & nu) const;

private:


	double dist(double x1, double y1, double x2, double y2) const;

	REAL force[3];
	REAL pdTarget[2];
	REAL K;
	REAL C;
	bool pdEnabled;
	
};



