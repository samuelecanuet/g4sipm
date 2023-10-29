#include "Sensor.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4TrackingManager.hh"

using namespace CLHEP;

//----------------------------------------------------------------------

// constructor of the sensitive detector associated to the Silicon Detector
Sensor::Sensor()
    : G4VSensitiveDetector("Sensor")
{
}

// destructor
Sensor::~Sensor()
{
}

//----------------------------------------------------------------------

// Function called at the beginning of the event processing
// (to initialise the list of "hits" associated to the detector)
void Sensor::Initialize(G4HCofThisEvent *)
{
  edep = 0;
}

// Function called when the track step occurs in the detector
G4bool Sensor::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4Track *track = step->GetTrack();

  if (track->GetParticleDefinition()->GetParticleName() == "e+")
  {
    edep += step->GetTotalEnergyDeposit();
  }

  // Creator Process
  if (step->IsLastStepInVolume())
  {
    const G4TrackVector *secondaryParticles = step->GetSecondary();
    for (size_t i = 0; i < secondaryParticles->size(); ++i)
    {
      G4Track *secondaryTrack = (*secondaryParticles)[i];
      if (secondaryTrack->GetParticleDefinition()->GetParticleName() == "opticalphoton")
      {
        PhotonCreationNumber++;
        G4String ProcessName = secondaryTrack->GetCreatorProcess()->GetProcessName();

        if (ProcessName == "Scintillation")
        {
          ScintillationNumber++;
          ScintillationTime.push_back(secondaryTrack->GetGlobalTime() - track->GetGlobalTime());
          // G4cout << "Time " << secondaryTrack->GetGlobalTime() - track->GetGlobalTime() << G4endl;
          ScintillationLambda.push_back((h_Planck * c_light / secondaryTrack->GetKineticEnergy() / eV));
          // G4cout<< "Lambda" << (h_Planck * c_light / secondaryTrack->GetKineticEnergy()/eV) << G4endl;
        }
        else if (ProcessName == "Cerenkov")
        {
          CerenkovNumber++;
          CerenkovLambda.push_back((h_Planck * c_light / secondaryTrack->GetKineticEnergy() / eV));
          // G4cout<< "Lambda" << (h_Planck * c_light / secondaryTrack->GetKineticEnergy()/eV) << G4endl;
        }
      }
    }
  }

  // Destructor-Exiting Process
  if (track->->GetParticleDefinition()->GetParticleName() == "opticalphoton")
  {
    if (step->GetPostStepPoint()->GetProcessDefinedStep->GetProcessName() == "OpAbsorption")
    {
      AbsorptionNumber++;
    }

    if (preStepPoint->GetStepStatus() == fGeomBoundary)
    {
      EntryNumber++;
    }

    if (postStepPoint->GetStepStatus() == fGeomBoundary)
    {
      ExitNumber++;
    }
  }

  // Reflection
  //TODO;

  //LightPosition
  

  return (true);
}
