#ifndef SENSOR_HH
#define SENSOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4OpBoundaryProcess.hh"

struct PlasticScintillatorInfo
{
  G4double EnergyDeposit;
  G4int PhotonNumber;
  G4int ScintillationNumber;
  G4int CerenkovNumber;
  G4int AbsorptionNumber;
  std::vector<G4double> ScintillationTime;
  std::vector<G4double> ScintillationLambda;
  std::vector<G4double> CerenkovLambda;
  G4int ExitNumber;
  G4int EntryNumber;
};

//----------------------------------------------------------------------
// This class is associated with a volume of the geometry to make this
// volume "sensitive"
// When a particle track produces a "hit" in the corresponding volume,
// the ProcessHits function is called
class Sensor : public G4VSensitiveDetector
{

  //------------------------------------------------------------
  // internal variables definition
protected:

  //------------------------------------------------------------
  // class functions definition
public:
  // constructor and destructor
  Sensor();
  virtual ~Sensor();

  // hits processing
  void Initialize(G4HCofThisEvent *);
  G4bool ProcessHits(G4Step *, G4TouchableHistory *);

  G4double edep=0.;
  std::vector<G4double> ScintillationTime;
  std::vector<G4double> ScintillationLambda;
  std::vector<G4double> CerenkovLambda;
  G4int ScintillationNumber = 0;
  G4int CerenkovNumber=0;
  G4int PhotonCreationNumber;
  G4int AbsorptionNumber=0;
  G4int ExitNumber=0;
  G4int EntryNumber=0;
};

#endif