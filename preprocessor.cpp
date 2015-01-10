
#include "preprocessor.hpp"

// The main preprocessing method that hashes the model image into 2D hash map
// Calculates the new coordinates of each corner in the model image according to the reference sets and stores them by hashing the granulated coordinates
void preprocess(std::vector<cv::Point> corners, Multimap2D& modelMap) {
	std::vector<cv::Point> sortedCorners(corners);
	std::sort(sortedCorners.begin(), sortedCorners.end(), cornerSorterAscending);
	std::vector<cv::Point>::iterator lastReference = sortedCorners.end() - 1;
	for (unsigned int itFirst = 0; itFirst < sortedCorners.size(); itFirst++) {
		for (unsigned int itSecond = itFirst + 1; itSecond < sortedCorners.size(); itSecond++) {
			Eigen::Vector2d first(sortedCorners.at(itFirst).x, sortedCorners.at(itFirst).y);
			Eigen::Vector2d second(sortedCorners.at(itSecond).x, sortedCorners.at(itSecond).y);
			Eigen::Vector2d e1 = second - first;
			double distance = e1.norm();
			if (distance <= REFERENCE_SET_DISTANCE) {
				Eigen::Vector2d origin = (first + second) / 2;
				e1.normalize();
				Eigen::Matrix2d rotation90ccw;
				rotation90ccw << 0, -1, 1, 0;
				Eigen::Vector2d e2 = rotation90ccw * e1;
				for (unsigned int it = 0; it < sortedCorners.size(); it++) {
					Eigen::Vector2i result = Eigen::Vector2i::Zero();
					Eigen::Vector2d transformed = Eigen::Vector2d::Zero();
					Eigen::Vector2d coordinates(sortedCorners.at(it).x, sortedCorners.at(it).y);
					findTransformedCoordinates(e1, e2, distance, origin, coordinates, transformed); // Calculate the transformed coordinates of the atom
					// TODO Determine granularity threshold, currently = 1.0
					granulate(result, transformed, GRANULARITY);// Granulate the result
					modelMap.emplace(HashKeyModel(result), HashEntryModel(itFirst, itSecond, it));//insert the transformed coordinates as a key with the value being the itFirst, itSecond and it
				}
			}
			else {
				continue;
			}
		}
	}
}




//void preprocess(Protein& modelProtein, Multimap3D& modelMap) {
//	std::vector<Chain>& chains = modelProtein.getChains();
//	for (std::vector<Chain>::iterator itChain = chains.begin();
//			itChain != chains.end(); itChain++) {// For every chain of the scene protein
//		std::vector<Atom>& atoms = itChain->getAtoms();
//		std::vector<Atom>::iterator lastReference = atoms.end() - 2;
//		if (atoms.size() >= 3) {
//			for (std::vector<Atom>::iterator itAtom = atoms.begin();
//					itAtom < lastReference; itAtom++) {	// For each reference set that are in a chain
//				Atom a1 = *itAtom;// Get 3 consecutive Atoms to create a new basis
//				Atom a2 = *(itAtom + 1);
//				Atom a3 = *(itAtom + 2);
//				Eigen::Vector3d v21 = a2.getPosition() - a1.getPosition();
//				Eigen::Vector3d v23 = a2.getPosition() - a3.getPosition();
//				bool check1 = v21.norm() <= REFERENCE_SET_DISTANCE;	// check for distance between consecutive atoms to prevent jumps in the chain
//				bool check2 = v23.norm() <= REFERENCE_SET_DISTANCE;
//				if (check1 && check2) {
//					Eigen::Vector3d e1 = v21;// Calculations required for new basis transformation
//					Eigen::Vector3d e3 = v21.cross(v23);
//					Eigen::Vector3d e2 = e3.cross(e1);
//					e1.normalize();
//					e2.normalize();
//					e3.normalize();
//					Eigen::Vector3d displacement = a2.getPosition();
//					Eigen::Vector3d origin = a2.getPosition();
//					std::vector<Atom*> atomsInSphere;
//					findAtomsInSphere(modelProtein, origin, SPHERE_RADIUS,
//							atomsInSphere);	// The atoms that are at a certain distance from the origin of the new basis
//					for (std::vector<Atom*>::iterator it =
//							atomsInSphere.begin(); it != atomsInSphere.end();
//							it++) {	// for each atom in the sphere
//						Eigen::Vector3i result = Eigen::Vector3i::Zero();
//						Eigen::Vector3d transformed = Eigen::Vector3d::Zero();
//						Eigen::Vector3d coordinates = (*it)->getPosition();
//						findTransformedCoordinates(e1, e2, e3, displacement,
//								coordinates, transformed);// Calculate the transformed coordinates of the atom
//						// TODO Determine granularity threshold, currently = 1.0
//						granulate(result, transformed, GRANULARITY);// Granulate the result
//						modelMap.emplace(HashKeyModel(result),
//								HashEntryModel3D(a1.getSerial(),
//										a1.getChainID(), *it));	//insert the transformed coordinates as a key with the value being the reference set id and the model atom being considered
//					}
//				} else if (check2) {	//1st distance check failed
//					continue;
//				} else {// 2nd distance check failed, need to move 2 atoms ahead for proper calculation
//					itAtom++;
//					continue;
//				}
//			}
//		}
//	}
//}
