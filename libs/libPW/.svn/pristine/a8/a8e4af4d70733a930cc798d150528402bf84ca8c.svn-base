
//This file is part of the MSD-Detector project (github.com/fedassa/msdDetector).
//
//The MSD-Detector is free software : you can redistribute it and / or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//The MSD-Detector is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with the MSD-Detector project.If not, see <http://www.gnu.org/licenses/>.
// 
// AUTHOR: Federico Tombari (fedassa@gmail.com)
// University of Bologna, Open Perception

#ifndef IMG_PYRAMID_H_
#define IMG_PYRAMID_H_

#include "opencv/cv.hpp"

class ImagePyramid
{
public:

	ImagePyramid(const cv::Mat &im, const int nLevels, const float scaleFactor = 1.6f);
	~ImagePyramid();

	const std::vector<cv::Mat> getImPyr() const { return m_imPyr; };

private:

	std::vector<cv::Mat> m_imPyr;
	int m_nLevels;
	float m_scaleFactor;
};

#endif
