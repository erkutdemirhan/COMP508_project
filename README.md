Computer Vision (COMP-508) Term Project

Koc University, Istanbul

Authors:
Deniz Demircioğlu
Erkut Demirhan

--- Project Proposal ---

For computer vision course project, we’ve decided to implement an efficient object
recognition system for 2D images.

The aim of this project is to identify previously known objects (coming from a set of
images) inside a complex scene. The system should be able to allow identification of
partially occluded objects, objects gone through translation, rotation and scaling.
The system should be fast and accurate.

To achieve these goals, the system will first perform detection of the corners (by
using Harris Detector) in both the object to be recognized and the scene. These
corners will be used as features. The rotation, translation and scaling invariant
transformation of image features will be performed by using geometric hashing
algorithm. Finally, a brief performance and accuracy analysis of the system will be
conducted.

All components of the system will be implemented using C++ programming
language on Linux environment. OpenCV will be used to perform image
enhancement and corner detection. Boost C++ libraries will also be used for its
hashing capabilities.

The project will include the following steps:
1. Image enhancement
2. Corner detection (Harris Detector)
3. Hashing (Preprocessing)
4. Voting (Matching)
5. Alignment
6. Performance tests

We are planning to divide the labour as follows: Erkut Demirhan will be responsible
for tasks 1, 2, 5, and Deniz Demircioğlu will be responsible for the remaining.
