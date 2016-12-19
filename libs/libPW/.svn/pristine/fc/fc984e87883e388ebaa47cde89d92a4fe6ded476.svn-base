
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

#ifndef LSD_DETECTOR_H_
#define LSD_DETECTOR_H_

#include <vector>
#include "opencv/cv.hpp"

#include "msdImgPyramid.h"


#include "boost\thread.hpp"
namespace PW {

class MsdDetector
{
public:

    MsdDetector()
	{
	
		m_patch_radius = 3;
		m_search_area_radius = 5;

		m_nms_radius = 5;
		m_nms_scale_radius = 0;

		m_th_saliency = 250.0f;
		m_kNN = 4;

		m_scale_factor = 1.25;
		m_n_scales = -1;
		m_compute_orientation = false;

    };

    std::vector<cv::KeyPoint> detect(cv::Mat &img,int maxTiepoints);
	
    void setPatchRadius(int patchRadius){ m_patch_radius = patchRadius; };
    int getPatchRadius(){ return m_patch_radius; };

    void setSearchAreaRadius(int searchAreaRadius){ m_search_area_radius = searchAreaRadius; };
    int getSearchAreaRadius(){ return m_search_area_radius; };

    void setNMSRadius(int nmsRadius){ m_nms_radius = nmsRadius; };
    int getNMSRadius(){ return m_nms_radius; };

    void setNMSScaleRadius(int nmsScaleRadius){ m_nms_scale_radius = nmsScaleRadius; };
    int getNMSScaleRadius(){ return m_nms_scale_radius; };

    void setThSaliency(float thSaliency){ m_th_saliency = thSaliency; };
    float getThSaliency(){ return m_th_saliency; };

    void setKNN(int kNN){ m_kNN = kNN; };
    int getKNN(){ return m_kNN; };

    void setScaleFactor(float scaleFactor){ m_scale_factor = scaleFactor; };
    float getScaleFactor(){ return m_scale_factor; };

    void setNScales(int nScales){ m_n_scales = nScales; };
    int getNScales(){ return m_n_scales; };

    void setComputeOrientation(bool computeOrientation){ m_compute_orientation = computeOrientation; };
    bool getComputeOrientation(){ return m_compute_orientation; };

private: 

	int m_patch_radius;
	int m_search_area_radius;

	int m_nms_radius;
	int m_nms_scale_radius;

	float m_th_saliency;
	int m_kNN;

	float m_scale_factor;
	int m_n_scales;
	int m_cur_n_scales;
	bool m_compute_orientation;

	std::vector<cv::Mat> m_scaleSpace;
	
	inline float computeAvgDistance(std::vector<int> &minVals, int den)
	{
		float avg_dist = 0.0f;
		for (unsigned int i = 0; i<minVals.size(); i++)
			avg_dist += minVals[i];

		avg_dist /= den;
		return avg_dist;
	}

	void contextualSelfDissimilarity(cv::Mat &img, int xmin, int xmax, float* saliency);

	float computeOrientation(cv::Mat &img, int x, int y, std::vector<cv::Point2f> circle);

    void nonMaximaSuppression(std::vector<float *> & saliency, std::vector<cv::KeyPoint> & keypoints, std::vector<cv::Mat> &aux_des);

    void normalizepatch(int size, float angle, cv::Mat input, cv::Mat &output);
};
}

#endif
