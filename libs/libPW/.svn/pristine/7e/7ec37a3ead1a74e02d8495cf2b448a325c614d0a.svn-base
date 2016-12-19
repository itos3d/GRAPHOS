
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

#include "msdImgPyramid.h"

ImagePyramid::ImagePyramid(const cv::Mat & im, const int nLevels, const float scaleFactor)
{
	m_nLevels = nLevels;
	m_scaleFactor = scaleFactor;
	m_imPyr.clear();
	m_imPyr.resize(nLevels);

	m_imPyr[0] = im.clone();

	if(m_nLevels > 1)
	{	
		for (int lvl = 1; lvl < m_nLevels; lvl++)
		{
			float scale = 1 / std::pow(scaleFactor, (float)lvl);
			m_imPyr[lvl] = cv::Mat(cv::Size(cvRound(im.cols * scale), cvRound(im.rows * scale)), im.type());
			cv::resize(im, m_imPyr[lvl], cv::Size(m_imPyr[lvl].cols, m_imPyr[lvl].rows), 0.0, 0.0, CV_INTER_AREA);
		}
	}
}

ImagePyramid::~ImagePyramid()
{
}







