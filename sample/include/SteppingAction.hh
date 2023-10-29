/*
 * SteppingAction.hh
 *
 *  Created on:
 *      Author:
 */


#ifndef STEPPINGACTION_HH_
#define STEPPINGACTION_HH_

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>
#include <iostream>
#include <fstream>
#include <set>

/**
 * Prevents Geant4 from running into infinite loops by limiting the
 * maximum number of bounces of optical photons 100000.
 */
class SteppingAction: public G4UserSteppingAction {
private:
	unsigned int maximumNumberOfSteps;

public:
	SteppingAction();
	virtual void UserSteppingAction(const G4Step* step);


};

#endif /* STEPPINGACTION_HH_ */
