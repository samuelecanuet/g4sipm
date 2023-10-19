/*
 * MaterialFactory.cc
 *
 * @date Mar 15, 2012
 * @author Tim Niggemann, III Phys. Inst. A, RWTH Aachen University
 * @copyright GNU General Public License v3.0
 */

#include "MaterialFactory.hh"

#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4NistManager.hh>

#include "VectorUtil.hh"

double MaterialFactory::LAMBDA_MIN = 200 * CLHEP::nm;
double MaterialFactory::LAMBDA_MAX = 3000 * CLHEP::nm;

MaterialFactory::MaterialFactory() {
	air = NULL;
	boronCarbideCeramic = NULL;
	copper = NULL;
	epoxy = NULL;
	silicon = NULL;
	glass = NULL;
}

MaterialFactory::~MaterialFactory() {
	delete air;
	delete boronCarbideCeramic;
	delete copper;
	delete epoxy;
	delete silicon;
	delete glass;
}

MaterialFactory* MaterialFactory::getInstance() {
	static MaterialFactory* instance = new MaterialFactory;
	return instance;
}

G4Material* MaterialFactory::getVacuum() {
	vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
	return vacuum;
}

G4Material *MaterialFactory::getEJ200() {
	pl = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	
	std::vector<G4double> wavelenght_sc = {
		380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395,
		396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411,
		412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427,
		428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443,
		444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459,
		460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475,
		476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491,
		492, 493, 494, 495, 496, 497, 498, 499};
	std::vector<G4double> energy_sc;
	for (unsigned long int i=1; i <= wavelenght_sc.size(); i++)
	{
		energy_sc.push_back(CLHEP::h_Planck * CLHEP::c_light / (wavelenght_sc[wavelenght_sc.size()-i] * CLHEP::nm));
	}

	std::vector<G4double> sc = {
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0010989, 0.0021978, 0.0032967, 0.0043956, 0.00549451,
		0.00659341, 0.00769231, 0.00879121, 0.00989011, 0.01098901, 0.01831502, 0.02564103, 0.03296703, 0.04599686, 0.07613815,
		0.10686813, 0.14642857, 0.17956044, 0.21355311, 0.25457875, 0.29835165, 0.3467033, 0.39505495, 0.46648352, 0.53479853,
		0.60934066, 0.67948718, 0.74395604, 0.81208791, 0.86813187, 0.92564103, 0.96428571, 0.98626374, 0.99413919, 1.0,
		0.99497645, 0.9899529, 0.98008242, 0.96909341, 0.95673077, 0.94134615, 0.92596154, 0.90879121, 0.89120879, 0.87362637,
		0.85604396, 0.82791209, 0.7978022, 0.77435897, 0.75091575, 0.72747253, 0.70467033, 0.68269231, 0.66071429, 0.63873626,
		0.61675824, 0.5974026, 0.58141858, 0.56543457, 0.54945055, 0.53506494, 0.52067932, 0.50629371, 0.49293564, 0.48037677,
		0.4678179, 0.45525903, 0.44381868, 0.43722527, 0.43063187, 0.42252747, 0.41373626, 0.40494505, 0.39390609, 0.38111888,
		0.36833167, 0.35516484, 0.33934066, 0.32351648, 0.30769231, 0.28815629, 0.26862027, 0.25027473, 0.23708791, 0.2239011,
		0.21071429, 0.1990232, 0.18925519, 0.17948718, 0.17032967, 0.16153846, 0.15274725, 0.14395604, 0.13571429, 0.12912088,
		0.12252747, 0.11608392, 0.10969031, 0.1032967, 0.09752747, 0.09313187, 0.08873626, 0.08434066, 0.07994505, 0.07554945,
		0.07115385, 0.06675824, 0.06236264, 0.05796703};

	G4MaterialPropertiesTable *pl_propreties = new G4MaterialPropertiesTable();
	pl_propreties->AddConstProperty("RINDEX", 1.58, true);
	pl_propreties->AddConstProperty("ABSLENGTH", 380 * CLHEP::cm, true);
	pl_propreties->AddProperty("SCINTILLATIONCOMPONENT1", energy_sc, sc);
	pl_propreties->AddConstProperty("SCINTILLATIONYIELD", 10000 / CLHEP::MeV, true);
	pl_propreties->AddConstProperty("RESOLUTIONSCALE", 2.5, true);
	pl_propreties->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1 * CLHEP::ns, true);
	pl->SetMaterialPropertiesTable(pl_propreties);

	return pl;
}

G4Material* MaterialFactory::getBoronCarbideCeramic() {
	if (boronCarbideCeramic == NULL) {
		boronCarbideCeramic = G4NistManager::Instance()->FindOrBuildMaterial("G4_BORON_CARBIDE");
		// TODO(tim): implement refractive index. This is important for the interaction with light to work (reflection, etc.).
	}
	return boronCarbideCeramic;
}

G4Material* MaterialFactory::getCopper() {
	if (copper == NULL) {
		copper = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
		// TODO(tim): implement refractive index. This is important for the interaction with light to work (reflection, etc.).
	}
	return copper;
}

G4Material* MaterialFactory::getAir() {
	if (air == NULL) {
		air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
		// Refractive index for dry air, 20°C, 1 atm [PDG].
		const double rIndex = 1. + 172. * 1e-6;
		double energies[] = { CLHEP::h_Planck * CLHEP::c_light / LAMBDA_MAX, CLHEP::h_Planck * CLHEP::c_light
				/ LAMBDA_MIN };
		double indices[] = { rIndex, rIndex };
		// Set material properties table.
		G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
		mpt->AddProperty("RINDEX", energies, indices, 2);
		air->SetMaterialPropertiesTable(mpt);
	}
	return air;
}

G4Material* MaterialFactory::getEpoxy() {
	if (epoxy == NULL) {
		// Create Bisphenol A which is the basis of each epoxy [wikipedia].
		epoxy = new G4Material("BisphenolA", 1.2 * CLHEP::g / CLHEP::cm3, 3, kStateSolid);
		epoxy->AddElement(G4NistManager::Instance()->FindOrBuildElement("Si"), 15);
		epoxy->AddElement(G4NistManager::Instance()->FindOrBuildElement("H"), 16);
		epoxy->AddElement(G4NistManager::Instance()->FindOrBuildElement("O"), 2);
		// Refractive index [private com. Hamamatsu].
		// TODO(tim): implement wavelength dependent index of refraction.
		double energies[] = { CLHEP::h_Planck * CLHEP::c_light / LAMBDA_MAX, CLHEP::h_Planck * CLHEP::c_light
				/ LAMBDA_MIN };
		double indices[] = { 1.5, 1.5 };
		// Set material properties table.
		G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
		mpt->AddProperty("RINDEX", energies, indices, 2);
		epoxy->SetMaterialPropertiesTable(mpt);
	}
	return epoxy;
}

G4Material* MaterialFactory::getGlass() {
	if (glass == NULL) {
		// Create Glass
		glass = G4NistManager::Instance()->FindOrBuildMaterial("G4_GLASS_PLATE");
	
		const double B1 = 1.03961212;
		const double B2 = 0.231792344;
		const double B3 = 1.01046945;
		const double C1 = 6.00069867e-3 * (CLHEP::um * CLHEP::um);
		const double C2 = 2.00179144e-2 * (CLHEP::um * CLHEP::um);
		const double C3 = 1.03560653e2 * (CLHEP::um * CLHEP::um);

		std::vector<double> energy;
		std::vector<double> refractiveIndex;
		

		for (double wavelength=LAMBDA_MAX; wavelength >= LAMBDA_MIN; wavelength -= 10.0*CLHEP::nm)
		{
			double photonEnergy = (CLHEP::h_Planck * CLHEP::c_light / (wavelength * CLHEP::nm));
			double n = sqrt(1 + B1 * pow(wavelength, 2) / (pow(wavelength, 2) - C1) +
							B2 * pow(wavelength, 2) / (pow(wavelength, 2) - C2) +
							B3 * pow(wavelength, 2) / (pow(wavelength, 2) - C3));
			energy.push_back(photonEnergy);
			refractiveIndex.push_back(n);
		}
		// Set material properties table.
		
		G4MaterialPropertiesTable *mpt = new G4MaterialPropertiesTable();
		mpt->AddProperty("RINDEX", &energy[0], &refractiveIndex[0], energy.size());
		glass->SetMaterialPropertiesTable(mpt);
	}
	return glass;
}

G4Material* MaterialFactory::getSilicon() {
	if (silicon == NULL) {
		silicon = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
		// Refractive index [http://refractiveindex.info/?group=CRYSTALS&material=Si].
		// Aspnes and Studna 1983: n,k 0.21-0.83 µm [http://refractiveindex.info/?shelf=main&book=Si&page=Aspnes].
		const int kSamples = 236;
		double lambda[kSamples] = { 0.1984, 0.2066, 0.2066, 0.2073, 0.208, 0.2087, 0.2094, 0.2101, 0.2109, 0.2116,
				0.2123, 0.213, 0.2138, 0.2138, 0.2145, 0.2153, 0.216, 0.2168, 0.2175, 0.2183, 0.2191, 0.2198, 0.2206,
				0.2214, 0.2214, 0.2222, 0.223, 0.2238, 0.2246, 0.2254, 0.2254, 0.2263, 0.2271, 0.2279, 0.2288, 0.2296,
				0.2296, 0.2305, 0.2313, 0.2322, 0.2331, 0.2339, 0.2339, 0.2348, 0.2357, 0.2366, 0.2375, 0.2384, 0.2384,
				0.2394, 0.2403, 0.2412, 0.2422, 0.2431, 0.2431, 0.2441, 0.245, 0.246, 0.247, 0.248, 0.248, 0.249, 0.25,
				0.251, 0.252, 0.253, 0.2541, 0.2551, 0.2562, 0.2572, 0.2583, 0.2594, 0.2605, 0.2616, 0.2627, 0.2638,
				0.2649, 0.2661, 0.2672, 0.2684, 0.2695, 0.2707, 0.2719, 0.2731, 0.2743, 0.2755, 0.2768, 0.278, 0.2792,
				0.2805, 0.2818, 0.2831, 0.2844, 0.2857, 0.287, 0.2883, 0.2897, 0.291, 0.2924, 0.2938, 0.2952, 0.2966,
				0.298, 0.2995, 0.3009, 0.3024, 0.3039, 0.3054, 0.3069, 0.3084, 0.31, 0.3115, 0.3131, 0.3147, 0.3163,
				0.3179, 0.3195, 0.3212, 0.3229, 0.3246, 0.3263, 0.328, 0.3297, 0.3315, 0.3333, 0.3351, 0.3369, 0.3388,
				0.3406, 0.3425, 0.3444, 0.3463, 0.3483, 0.3502, 0.3522, 0.3542, 0.3563, 0.3583, 0.3604, 0.3625, 0.3647,
				0.3668, 0.369, 0.3712, 0.3734, 0.3757, 0.378, 0.3803, 0.3827, 0.385, 0.3875, 0.3899, 0.3924, 0.3949,
				0.3974, 0.4, 0.4025, 0.4052, 0.4078, 0.4105, 0.4133, 0.4161, 0.4189, 0.4217, 0.4246, 0.4275, 0.4305,
				0.4335, 0.4366, 0.4397, 0.4428, 0.446, 0.4492, 0.4525, 0.4558, 0.4592, 0.4626, 0.4661, 0.4696, 0.4732,
				0.4769, 0.4806, 0.4843, 0.4881, 0.492, 0.4959, 0.4999, 0.504, 0.5081, 0.5123, 0.5166, 0.5209, 0.5254,
				0.5299, 0.5344, 0.5391, 0.5438, 0.5486, 0.5535, 0.5585, 0.5636, 0.5687, 0.574, 0.5794, 0.5848, 0.5904,
				0.5961, 0.6019, 0.6078, 0.6138, 0.6199, 0.6262, 0.6326, 0.6391, 0.6458, 0.6526, 0.6595, 0.6666, 0.6738,
				0.6812, 0.6888, 0.6965, 0.7045, 0.7126, 0.7208, 0.7293, 0.738, 0.7469, 0.756, 0.7653, 0.7749, 0.7847,
				0.7948, 0.8051, 0.8157, 0.8266 };
		double real[kSamples] = { 0.968, 1.11, 1.01, 1.036, 1.046, 1.066, 1.07, 1.083, 1.088, 1.102, 1.109, 1.119, 1.24,
				1.133, 1.139, 1.155, 1.164, 1.175, 1.18, 1.195, 1.211, 1.222, 1.235, 1.4, 1.247, 1.265, 1.28, 1.299,
				1.319, 1.51, 1.34, 1.362, 1.389, 1.416, 1.445, 1.64, 1.471, 1.502, 1.526, 1.548, 1.566, 1.75, 1.579,
				1.585, 1.59, 1.591, 1.592, 1.78, 1.589, 1.586, 1.582, 1.579, 1.573, 1.72, 1.571, 1.57, 1.569, 1.568,
				1.569, 1.68, 1.57, 1.575, 1.58, 1.584, 1.591, 1.597, 1.608, 1.618, 1.629, 1.643, 1.658, 1.673, 1.692,
				1.713, 1.737, 1.764, 1.794, 1.831, 1.874, 1.927, 1.988, 2.059, 2.14, 2.234, 2.339, 2.451, 2.572, 2.7,
				2.833, 2.974, 3.12, 3.277, 3.444, 3.634, 3.849, 4.086, 4.318, 4.525, 4.686, 4.805, 4.888, 4.941, 4.977,
				4.999, 5.012, 5.02, 5.021, 5.02, 5.018, 5.015, 5.01, 5.009, 5.01, 5.009, 5.012, 5.016, 5.021, 5.029,
				5.04, 5.052, 5.065, 5.079, 5.095, 5.115, 5.134, 5.156, 5.179, 5.204, 5.231, 5.261, 5.296, 5.336, 5.383,
				5.442, 5.515, 5.61, 5.733, 5.894, 6.089, 6.308, 6.522, 6.695, 6.796, 6.829, 6.799, 6.709, 6.585, 6.452,
				6.316, 6.185, 6.062, 5.948, 5.842, 5.744, 5.654, 5.57, 5.493, 5.42, 5.349, 5.284, 5.222, 5.164, 5.109,
				5.058, 5.009, 4.961, 4.916, 4.872, 4.831, 4.791, 4.753, 4.718, 4.682, 4.648, 4.615, 4.583, 4.553, 4.522,
				4.495, 4.466, 4.442, 4.416, 4.391, 4.367, 4.343, 4.32, 4.298, 4.277, 4.255, 4.235, 4.215, 4.196, 4.177,
				4.159, 4.14, 4.123, 4.106, 4.089, 4.073, 4.057, 4.042, 4.026, 4.012, 3.997, 3.983, 3.969, 3.956, 3.943,
				3.931, 3.918, 3.906, 3.893, 3.882, 3.87, 3.858, 3.847, 3.837, 3.826, 3.815, 3.805, 3.796, 3.787, 3.778,
				3.768, 3.761, 3.752, 3.745, 3.736, 3.728, 3.721, 3.714, 3.705, 3.697, 3.688, 3.681, 3.673 };
		double imaginary[kSamples] = { 2.89, 3.05, 2.909, 2.928, 2.944, 2.937, 2.963, 2.982, 2.987, 3.005, 3.015, 3.025,
				3.18, 3.045, 3.061, 3.073, 3.086, 3.102, 3.112, 3.135, 3.15, 3.169, 3.19, 3.33, 3.206, 3.228, 3.245,
				3.267, 3.285, 3.4, 3.302, 3.319, 3.334, 3.35, 3.359, 3.44, 3.366, 3.368, 3.368, 3.364, 3.358, 3.42,
				3.353, 3.346, 3.344, 3.344, 3.347, 3.36, 3.354, 3.363, 3.376, 3.389, 3.408, 3.42, 3.429, 3.451, 3.477,
				3.504, 3.533, 3.58, 3.565, 3.598, 3.632, 3.67, 3.709, 3.749, 3.789, 3.835, 3.88, 3.928, 3.979, 4.031,
				4.088, 4.149, 4.211, 4.278, 4.35, 4.426, 4.506, 4.59, 4.678, 4.764, 4.849, 4.933, 5.011, 5.082, 5.148,
				5.206, 5.257, 5.304, 5.344, 5.381, 5.414, 5.435, 5.439, 5.395, 5.301, 5.158, 4.989, 4.812, 4.639, 4.48,
				4.335, 4.204, 4.086, 3.979, 3.885, 3.798, 3.72, 3.65, 3.587, 3.529, 3.477, 3.429, 3.386, 3.346, 3.31,
				3.275, 3.242, 3.211, 3.182, 3.154, 3.128, 3.103, 3.079, 3.058, 3.039, 3.021, 3.007, 2.995, 2.987, 2.983,
				2.984, 2.989, 2.999, 3.014, 3.026, 3.023, 2.982, 2.881, 2.705, 2.456, 2.169, 1.87, 1.571, 1.321, 1.11,
				0.945, 0.815, 0.714, 0.63, 0.561, 0.505, 0.456, 0.416, 0.387, 0.355, 0.329, 0.313, 0.291, 0.269, 0.255,
				0.244, 0.228, 0.211, 0.203, 0.194, 0.185, 0.185, 0.17, 0.163, 0.149, 0.149, 0.133, 0.131, 0.13, 0.131,
				0.134, 0.12, 0.12, 0.09, 0.094, 0.083, 0.079, 0.077, 0.073, 0.073, 0.066, 0.072, 0.06, 0.06, 0.056,
				0.053, 0.043, 0.045, 0.048, 0.044, 0.044, 0.032, 0.038, 0.032, 0.034, 0.03, 0.027, 0.03, 0.03, 0.027,
				0.025, 0.025, 0.024, 0.022, 0.022, 0.019, 0.018, 0.017, 0.016, 0.016, 0.015, 0.014, 0.013, 0.013, 0.013,
				0.012, 0.011, 0.011, 0.01, 0.01, 0.009, 0.009, 0.008, 0.008, 0.007, 0.007, 0.006, 0.006, 0.005 };
		double absolute[kSamples];
		// Reverse arrays.
		VectorUtil::reverse(real, kSamples);
		VectorUtil::reverse(imaginary, kSamples);
		// Derive energy in ascending order.
		double energies[kSamples];
		// double abslength[kSamples];
		for (int i = 0; i < kSamples; ++i) {
			energies[i] = CLHEP::h_Planck * CLHEP::c_light / (lambda[kSamples - i - 1] * CLHEP::micrometer);
			absolute[i] = std::sqrt(real[i] * real[i] + imaginary[i] * imaginary[i]);
			// abslength[i] = 4 * CLHEP::pi * imaginary[i] / (lambda[kSamples - i - 1] * CLHEP::micrometer);
			// std::cout << lambda[n - i - 1] * micrometer / nm << "\t" << abslength[i] << std::endl;
		}
		// XXX:
		// Snell's law: real part.
		// Fresnel formulas: absolute value since imaginary part is not zero.
		// Geant4 calculates both, refraction angle and the Fresnel formulas in case of dielectric_dielectric
		// by using the real number "RINDEX".
		G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
		mpt->AddProperty("RINDEX", energies, absolute, kSamples);
		//		mpt->AddProperty("REALRINDEX", energies, real, kSamples);
		//		mpt->AddProperty("IMAGINARYRINDEX", energies, imaginary, kSamples);
		//		mpt->AddProperty("ABSLENGTH", energies, abslength, kSamples);
		silicon->SetMaterialPropertiesTable(mpt);
	}
	return silicon;
}
