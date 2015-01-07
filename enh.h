// Erkut Demirhan
//
// Library of functions to be used for enhancing input images for
// corner detection
#ifndef ENH_H
#define ENH_H

// applies gaussian filtering on given input image, using standard deviation
// parameter std_dev, and filter size parameter filter_size.
// Returns resulting image of the gaussian filter
Mat apply_gaussian_filtering(const Mat image,
									  const float std_dev,
								     const int filter_size);

// applies histogram equalization on the grayscale version of the given rgb image
// returns enhanced grayscale image
Mat apply_histeq(const Mat rgb_image); 
#endif
