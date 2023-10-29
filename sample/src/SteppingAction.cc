/*
 * SteppingAction.cc
 *
 *  Created on:
 *      Author:
 */


#include "SteppingAction.hh"

#include <iostream>

#include <G4Track.hh>
#include <G4VProcess.hh>
#include <G4OpticalPhoton.hh>

SteppingAction::SteppingAction() :
		G4UserSteppingAction(), maximumNumberOfSteps(100000) {
	//
}


void SteppingAction::UserSteppingAction(const G4Step* step) {

	// kill track if maximumNumberOfSteps is exceeded
	if ((unsigned int) step->GetTrack()->GetCurrentStepNumber() > maximumNumberOfSteps) {
		std::cerr << "SteppingAction::UserSteppingAction: exceeded maximum number of steps for track \""
				<< step->GetTrack()->GetTrackID() << "\" created by \"";
		if (step->GetTrack()->GetCreatorProcess()) {
			std::cerr << step->GetTrack()->GetCreatorProcess()->GetProcessName();
		} else {
			std::cerr << "unknown";
		}
		std::cerr << "\"." << std::endl;
		step->GetTrack()->SetTrackStatus(fStopAndKill);
	}
}
