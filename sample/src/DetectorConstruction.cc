/*
 * DetectorConstruction.cc
 *
 * @date Sep 12, 2011
 * @author Tim Niggemann, III Phys. Inst. A, RWTH Aachen University
 * @copyright GNU General Public License v3.0
 */

#include "DetectorConstruction.hh"

#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>

#include "G4Sipm.hh"
#include "MaterialFactory.hh"
#include "model/G4SipmModelFactory.hh"
#include "housing/G4SipmHousing.hh"
#include "housing/impl/HamamatsuCeramicHousing.hh"
#include "housing/impl/HamamatsuSmdHousing.hh"

#include "G4RunManager.hh"


#include <G4NistManager.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalBorderSurface.hh>

DetectorConstruction::DetectorConstruction(std::string sipmModelName, std::string housingName, G4bool pl_condition) :
		G4VUserDetectorConstruction() {
	// Create SiPM and housing.
	
	for (int i=0; i<9; i++)
	{
		SiPMs[i] = createSipmModel(sipmModelName);
		SiPMs_Housing[i] = createHousing(housingName, new G4Sipm(SiPMs[i]));
	}	
	Condition=pl_condition;

}

DetectorConstruction::~DetectorConstruction() {
	for (int i=0; i<9; i++)
	{
		delete SiPMs_Housing[i];
	}
	
}

G4SipmModel* DetectorConstruction::createSipmModel(std::string name) const {
	if (name == "generic") {
		return G4SipmModelFactory::getInstance()->createGenericSipmModel();
	}
	if (name == "HamamatsuS1036211100") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS1036211100();
	}
	if (name == "HamamatsuS1036233100") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS1036233100();
	}
	if (name == "HamamatsuS10985100") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS10985100();
	}
	if (name == "HamamatsuS12651050") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS12651050();
	}
	if (name == "HamamatsuS1036233050") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS1036233050();
	}
	if (name == "HamamatsuS12573100C") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS12573100C();
	}
	if (name == "HamamatsuS12573100X") {
		return G4SipmModelFactory::getInstance()->createHamamatsuS12573100X();
	}
	return G4SipmModelFactory::getInstance()->createConfigFileModel(name);
}

G4SipmHousing* DetectorConstruction::createHousing(std::string name, G4Sipm* sipm) const {
	if (name == "ceramic") {
		return new HamamatsuCeramicHousing(sipm);
	}
	if (name == "smd") {
		return new HamamatsuSmdHousing(sipm);
	}
	if (name == "default") {
		return new G4SipmHousing(sipm);
	}
	std::cout << "G4SipmDetectorConstruction::createHousingForName(name = \"" << name
			<< "\"): housing type does not exist." << std::endl;
	throw 1;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
	G4ThreeVector worldDimension = G4ThreeVector(1. * CLHEP::m, 1. * CLHEP::m, 1. * CLHEP::m);
	// Create world volume.
	G4Box* world = new G4Box("world", worldDimension.x(), worldDimension.y(), worldDimension.z());
	G4LogicalVolume* worldLv = new G4LogicalVolume(world, MaterialFactory::getInstance()->getVacuum(), "worldLv", NULL,
	NULL, NULL);
	//worldLv->SetVisAttributes(G4VisAttributes::Invisible);
	worldLv->SetVisAttributes(G4VisAttributes::GetInvisible());
	G4VPhysicalVolume* worldPv = new G4PVPlacement(NULL, G4ThreeVector(), worldLv, "worldPv", NULL, false, 0);
	
	

	// add pcb 
	
	G4double fLength_PlasticScintillator = 0;
	G4double fLength_Grease = 0;
	if (Condition)
	{
		fLength_PlasticScintillator = 5 * CLHEP::cm;
		G4double fRadius_PlasticScintillator = 1.5 * CLHEP::cm;
		G4double Teflon_thickness = 1*CLHEP::mm;

		G4Tubs *fSolid_PlasticScintillator = new G4Tubs("PlasticScintillator", 0., fRadius_PlasticScintillator, 0.5 * fLength_PlasticScintillator, 0., 360 * CLHEP::deg); // name, r : 0->1cm, L : 5cm, phi : 0->2pi
		G4LogicalVolume *fLogic_PlasticScintillator = new G4LogicalVolume(fSolid_PlasticScintillator, MaterialFactory::getInstance()->getEJ200(), "PlasticScintillator"); // solid, material, name
		
		G4PVPlacement *fPhys_PlasticScintillator = new G4PVPlacement(0,																									  // rotationMatrix
																	 G4ThreeVector(0., 0., fLength_PlasticScintillator / 2),											  // position
																	 fLogic_PlasticScintillator, "PlasticScintillator",													  // its fLogical volume
																	 worldLv,																							  // its mother volume
																	 false,																								  // no boolean op.
																	 0);

		G4VisAttributes *PlasticScintillator_att = new G4VisAttributes(G4Colour(0.1, 0.1, 0.1, 0.2)); // red
		PlasticScintillator_att->SetForceWireframe(true);
		PlasticScintillator_att->SetForceSolid(true);
		fLogic_PlasticScintillator->SetVisAttributes(PlasticScintillator_att);

		G4Tubs *fSolid_Teflon = new G4Tubs("Teflon", fRadius_PlasticScintillator, fRadius_PlasticScintillator+Teflon_thickness, 0.5 * fLength_PlasticScintillator, 0., 360 * CLHEP::deg); // name, r : 0->1cm, L : 5cm, phi : 0->2pi
		G4LogicalVolume *fLogic_Teflon = new G4LogicalVolume(fSolid_Teflon, MaterialFactory::getInstance()->getTeflon(), "Teflon"); // solid, material, name
		G4PVPlacement *fPhys_Teflon = new G4PVPlacement(0,																									  // rotationMatrix
																	 G4ThreeVector(0., 0., fLength_PlasticScintillator / 2),											  // position
																	 fLogic_Teflon, "Teflon",													  // its fLogical volume
																	 worldLv,																							  // its mother volume
																	 false,																								  // no boolean op.
																	 0);

		G4VisAttributes *Teflon_att = new G4VisAttributes(G4Colour(0.1, 0.1, 0.1, 0.1)); // red
		Teflon_att->SetForceWireframe(true);
		Teflon_att->SetForceSolid(true);
		fLogic_Teflon->SetVisAttributes(Teflon_att);
		
		fLength_Grease = 1 * CLHEP::mm;
		G4Tubs *OpticalGrease = new G4Tubs("OpticalGrease", 0., fRadius_PlasticScintillator, fLength_Grease / 2, 0., 360 * CLHEP::deg); // name, r : 0->1cm, L : 5cm, phi : 0->2pi
		G4LogicalVolume *Logic_OpticalGrease = new G4LogicalVolume(OpticalGrease, MaterialFactory::getInstance()->getGrease(), "OpticalGrease"); // solid, material, name
		G4PVPlacement *phys_OpticalGrease = new G4PVPlacement(0,																									  // rotationMatrix
																	 G4ThreeVector(0., 0., fLength_PlasticScintillator + fLength_Grease / 2 ),											  // position
																	 Logic_OpticalGrease, "OpticalGrease",													  // its fLogical volume
																	 worldLv,																							  // its mother volume
																	 false,																								  // no boolean op.
																	 0);

		G4VisAttributes *Grease_att = new G4VisAttributes(G4Colour(0.1, 0.1, 0.1, 0.4));
		Grease_att->SetForceWireframe(true);
		Grease_att->SetForceSolid(true);
		Logic_OpticalGrease->SetVisAttributes(Grease_att);
	
	}


	G4double SiPMSpacing = 6.75 * CLHEP::mm;
	G4RotationMatrix* myRotation_trSupp = new G4RotationMatrix();
    myRotation_trSupp->rotateY(180.*CLHEP::deg);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			G4double x = (i-1) * SiPMSpacing;
			G4double y = (j-1) * SiPMSpacing;

			SiPMs_Housing[i * 3 + j]->setPosition(G4ThreeVector(x, y, fLength_PlasticScintillator + fLength_Grease + SiPMs_Housing[i]->getPackageDz() / 2));
			SiPMs_Housing[i * 3 + j]->setRotation(myRotation_trSupp);
			SiPMs_Housing[i * 3 + j]->buildAndPlace(worldPv);
		}
	}


	return worldPv;

}

G4SipmModel* DetectorConstruction::getSipmModel(int i) const {
	return SiPMs_Housing[i]->getSipm()->getModel();
}

G4SipmHousing* DetectorConstruction::getSipmHousing(int i) const {
	return SiPMs_Housing[i];
}

void DetectorConstruction::constructOpticalSkinSurface(G4LogicalVolume* lv, G4Material* material, G4OpticalSurfaceModel model,
		G4OpticalSurfaceFinish finish, G4SurfaceType type, G4double value) {
	G4OpticalSurface* surface = new G4OpticalSurface(lv->GetName() + "Surface", model, finish, type, value);
	surface->SetMaterialPropertiesTable(material->GetMaterialPropertiesTable());
	new G4LogicalSkinSurface(lv->GetName() + "Skin", lv, surface);
}

void DetectorConstruction::constructOpticalBorderSurface(G4VPhysicalVolume* pv, G4VPhysicalVolume* parentPv, G4Material* material,
		G4OpticalSurfaceModel model, G4OpticalSurfaceFinish finish, G4SurfaceType type, G4double value) {
	G4OpticalSurface* surface = new G4OpticalSurface(pv->GetName() + "Surface", model, finish, type, value);
	surface->SetMaterialPropertiesTable(material->GetMaterialPropertiesTable());
	new G4LogicalBorderSurface(pv->GetName() + "BorderSurface1", pv, parentPv, surface);
	new G4LogicalBorderSurface(pv->GetName() + "BorderSurface2", parentPv, pv, surface);
}
