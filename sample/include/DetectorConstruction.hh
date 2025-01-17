/*
 * DetectorConstruction.hh
 *
 * @date Sep 12, 2011
 * @author Tim Niggemann, III Phys. Inst. A, RWTH Aachen University
 * @copyright GNU General Public License v3.0
 */

#ifndef DETECTORCONSTRUCTION_HH_
#define DETECTORCONSTRUCTION_HH_

#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VUserDetectorConstruction.hh>

#include "G4Sipm.hh"
#include "housing/G4SipmHousing.hh"


#include <G4Material.hh>
#include <G4VisAttributes.hh>
#include <G4Color.hh>
#include <G4LogicalVolume.hh>
#include <G4OpticalSurface.hh>
#include <G4SurfaceProperty.hh>
#include <G4VPhysicalVolume.hh>

/**
 * User detector construction. Places a single SiPM in the world.
 */
class DetectorConstruction: public G4VUserDetectorConstruction {
private:
	G4SipmHousing* SiPMs_Housing[9]={};
	G4SipmModel* SiPMs[9]={};
	G4bool Condition;

	/**
	 * @param name - the name of the model.
	 * @return G4SipmModel - the new instance.
	 */
	G4SipmModel* createSipmModel(std::string name) const;
	/**
	 * @param name - the name of the housing.
	 * @param sipm - the SiPM instance.
	 * @return G4SipmHousing - the new instance.
	 */
	G4SipmHousing* createHousing(std::string name, G4Sipm* sipm) const;

public:
	/**
	 * Constructor.
	 *
	 * @param modelName - the model name (see G4SipmModelFactory).
	 * @param housingName - the name of the housing ("ceramic", "smd", "plain").
	 */
	DetectorConstruction(std::string modelName, std::string housingName, G4bool pl_condition);
	virtual ~DetectorConstruction();

	G4VPhysicalVolume* Construct();
	/**
	 * @return G4SipmModel - the SiPM model.
	 */
	G4SipmModel* getSipmModel(int i) const;
	/**
	 * @return G4SipmHousing - the housing instance.
	 */
	G4SipmHousing* getSipmHousing(int i) const;

	static void constructOpticalSkinSurface(G4LogicalVolume* lv, G4Material* material, G4OpticalSurfaceModel model =
			unified, G4OpticalSurfaceFinish finish = ground, G4SurfaceType type = dielectric_dielectric,
			G4double value = 1.0);
	static void constructOpticalBorderSurface(G4VPhysicalVolume* pv, G4VPhysicalVolume* parentPv, G4Material* material,
			G4OpticalSurfaceModel model = unified, G4OpticalSurfaceFinish finish = ground, G4SurfaceType type =
					dielectric_dielectric, G4double value = 1.0);


};

#endif /* G4SIPMDETECTORCONSTRUCTION_HH_ */
