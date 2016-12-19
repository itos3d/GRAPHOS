
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


#include "MSD.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace PW;

struct sortByStrength
{
    inline bool operator() (const cv::KeyPoint& struct1, const cv::KeyPoint& struct2)
    {
        return (struct1.response < struct2.response);
    }
};

	void MsdDetector::contextualSelfDissimilarity(cv::Mat &img, int xmin, int xmax, float* saliency)
	{
		int r_s = m_patch_radius;
		int r_b = m_search_area_radius;
		int k = m_kNN;

		int w = img.cols;
		int h = img.rows;

		int side_s = 2 * r_s + 1;
		int side_b = 2 * r_b + 1;
		int border = r_s + r_b;
		int temp;
		int den = side_s * side_s * k;

		std::vector<int> minVals(k);
		int *acc = new int[side_b * side_b];
		int **vCol = new int *[w];
		for (int i = 0; i<w; i++)
			vCol[i] = new int[side_b * side_b];

		//first position
		int x = xmin;
		int y = border;

		int ctrInd = 0;
		for (int kk = 0; kk<k; kk++)
			minVals[kk] = std::numeric_limits<int>::max();

		for (int j = y - r_b; j <= y + r_b; j++)
		{
			for (int i = x - r_b; i <= x + r_b; i++)
			{
				if (j == y && i == x)
					continue;

				acc[ctrInd] = 0;
				for (int u = -r_s; u <= r_s; u++)
				{
					vCol[x + u][ctrInd] = 0;
                    for (int v = -r_s; v <= r_s; v++) //eliminar este =?
					{
						temp = img.at<unsigned char>(j + v, i + u) - img.at<unsigned char>(y + v, x + u);
						vCol[x + u][ctrInd] += (temp*temp);
					}
					acc[ctrInd] += vCol[x + u][ctrInd];
				}

				if (acc[ctrInd]  < minVals[k - 1])
				{
					minVals[k - 1] = acc[ctrInd];

					for (int kk = k - 2; kk >= 0; kk--)
					{
						if (minVals[kk] > minVals[kk + 1])
						{
							std::swap(minVals[kk], minVals[kk + 1]);
						}
						else
							break;
					}
				}

				ctrInd++;
			}
		}
		saliency[y*w + x] = computeAvgDistance(minVals, den);

		for (x = xmin + 1; x<xmax; x++)
		{
			ctrInd = 0;
			for (int kk = 0; kk<k; kk++)
				minVals[kk] = std::numeric_limits<int>::max();

			for (int j = y - r_b; j <= y + r_b; j++)
			{
				for (int i = x - r_b; i <= x + r_b; i++)
				{
					if (j == y && i == x)
						continue;

					vCol[x + r_s][ctrInd] = 0;
					for (int v = -r_s; v <= r_s; v++)
					{
						temp = img.at<unsigned char>(j + v, i + r_s) - img.at<unsigned char>(y + v, x + r_s);
						vCol[x + r_s][ctrInd] += (temp*temp);
					}

					acc[ctrInd] = acc[ctrInd] + vCol[x + r_s][ctrInd] - vCol[x - r_s - 1][ctrInd];

					if (acc[ctrInd] < minVals[k - 1])
					{
						minVals[k - 1] = acc[ctrInd];
						for (int kk = k - 2; kk >= 0; kk--)
						{
							if (minVals[kk] > minVals[kk + 1])
							{
								std::swap(minVals[kk], minVals[kk + 1]);
							}
							else
								break;
						}
					}

					ctrInd++;
				}
			}
			saliency[y*w + x] = computeAvgDistance(minVals, den);
		}

		//all remaining rows...
		for (int y = border + 1; y< h - border; y++)
		{
			//first position of each row
			ctrInd = 0;
			for (int kk = 0; kk<k; kk++)
				minVals[kk] = std::numeric_limits<int>::max();
			x = xmin;

			for (int j = y - r_b; j <= y + r_b; j++)
			{
				for (int i = x - r_b; i <= x + r_b; i++)
				{
					if (j == y && i == x)
						continue;

					acc[ctrInd] = 0;
					for (int u = -r_s; u <= r_s; u++)
					{
						temp = img.at<unsigned char>(j + r_s, i + u) - img.at<unsigned char>(y + r_s, x + u);
						vCol[x + u][ctrInd] += (temp*temp);

						temp = img.at<unsigned char>(j - r_s - 1, i + u) - img.at<unsigned char>(y - r_s - 1, x + u);
						vCol[x + u][ctrInd] -= (temp*temp);

						acc[ctrInd] += vCol[x + u][ctrInd];
					}

					if (acc[ctrInd]  < minVals[k - 1])
					{
						minVals[k - 1] = acc[ctrInd];

						for (int kk = k - 2; kk >= 0; kk--)
						{
							if (minVals[kk] > minVals[kk + 1])
							{
								std::swap(minVals[kk], minVals[kk + 1]);
							}
							else
								break;
						}
					}

					ctrInd++;
				}
			}
			saliency[y*w + x] = computeAvgDistance(minVals, den);

			//all remaining positions
			for (x = xmin + 1; x<xmax; x++)
			{
				ctrInd = 0;
				for (int kk = 0; kk<k; kk++)
					minVals[kk] = std::numeric_limits<int>::max();

				for (int j = y - r_b; j <= y + r_b; j++)
				{
					for (int i = x - r_b; i <= x + r_b; i++)
					{
						if (j == y && i == x)
							continue;

						temp = img.at<unsigned char>(j + r_s, i + r_s) - img.at<unsigned char>(y + r_s, x + r_s);
						vCol[x + r_s][ctrInd] += (temp*temp);

						temp = img.at<unsigned char>(j - r_s - 1, i + r_s) - img.at<unsigned char>(y - r_s - 1, x + r_s);
						vCol[x + r_s][ctrInd] -= (temp*temp);

						acc[ctrInd] = acc[ctrInd] + vCol[x + r_s][ctrInd] - vCol[x - r_s - 1][ctrInd];

						if (acc[ctrInd] < minVals[k - 1])
						{
							minVals[k - 1] = acc[ctrInd];

							for (int kk = k - 2; kk >= 0; kk--)
							{
								if (minVals[kk] > minVals[kk + 1])
								{
									std::swap(minVals[kk], minVals[kk + 1]);
								}
								else
									break;
							}
						}
						ctrInd++;
					}
				}
				saliency[y*w + x] = computeAvgDistance(minVals, den);
			}
		}

		for (int i = 0; i<w; i++)
			delete[] vCol[i];
		delete[] vCol;
		delete[] acc;
	}

	float MsdDetector::computeOrientation(cv::Mat &img, int x, int y, std::vector<cv::Point2f> circle)
	{
		int temp;
		int w = img.cols;
		int h = img.rows;

		int side = m_search_area_radius * 2 + 1;
		int nBins = 36;
		float step = float((2 * M_PI) / nBins);
		std::vector<float> hist(nBins, 0);
		std::vector<int> dists(circle.size(), 0);

		int minDist = std::numeric_limits<int>::max();
		int maxDist = -1;

		for (int k = 0; k<(int)circle.size(); k++)
		{

			int j = y + static_cast <int> (circle[k].y);
			int i = x + static_cast <int> (circle[k].x);

			for (int v = -m_patch_radius; v <= m_patch_radius; v++)
			{
				for (int u = -m_patch_radius; u <= m_patch_radius; u++)
				{
					temp = img.at<unsigned char>(j + v, i + u) - img.at<unsigned char>(y + v, x + u);
					dists[k] += temp*temp;
				}
			}

			if (dists[k] > maxDist)
				maxDist = dists[k];
			if (dists[k] < minDist)
				minDist = dists[k];
		}

		float deltaAngle = 0.0f;
		for (int k = 0; k<(int)circle.size(); k++)
		{
			float angle = deltaAngle;
			float weight = (1.0f*maxDist - dists[k]) / (maxDist - minDist);

			float binF;
			if (angle >= 2 * M_PI)
				binF = 0.0f;
			else
				binF = angle / step;
			int bin = static_cast <int> (std::floor(binF));

			assert(bin >= 0 && bin < nBins);
			float binDist = abs(binF - bin - 0.5f);

			float weightA = weight * (1.0f - binDist);
			float weightB = weight * binDist;
			hist[bin] += weightA;

			if (2 * (binF - bin) < step)
				hist[(bin + nBins - 1) % nBins] += weightB;
			else
				hist[(bin + 1) % nBins] += weightB;

			deltaAngle += step;
		}

		int bestBin = -1;
		float maxBin = -1;
		for (int i = 0; i<nBins; i++)
		{
			if (hist[i] > maxBin)
			{
				maxBin = hist[i];
				bestBin = i;
			}
		}

		//parabolic interpolation
		int l = (bestBin == 0) ? nBins - 1 : bestBin - 1;
		int r = (bestBin + 1) % nBins;
		float bestAngle2 = bestBin + 0.5f * ((hist[l]) - (hist[r])) / ((hist[l]) - 2.0f*(hist[bestBin]) + (hist[r]));
		bestAngle2 = (bestAngle2 < 0) ? nBins + bestAngle2 : (bestAngle2 >= nBins) ? bestAngle2 - nBins : bestAngle2;
		bestAngle2 *= step;
		
		return bestAngle2;
	}

    void MsdDetector::nonMaximaSuppression(std::vector<float *> & saliency, std::vector<cv::KeyPoint> & keypoints, std::vector<cv::Mat > &aux_des)
	{
		cv::KeyPoint kp_temp;
		int side = m_search_area_radius * 2 + 1;
		int border = m_search_area_radius + m_patch_radius;

		//COMPUTE LUT FOR CANONICAL ORIENTATION
		std::vector<cv::Point2f> orientPoints;
		if (m_compute_orientation)
		{
			int nBins = 36;
			float step = float((2 * M_PI) / nBins);
			float deltaAngle = 0.0f;

			for (int i = 0; i<nBins; i++)
			{
				cv::Point2f pt;
				pt.x = m_search_area_radius * cos(deltaAngle);
				pt.y = m_search_area_radius * sin(deltaAngle);

				orientPoints.push_back(pt);

				deltaAngle += step;
			}
		}

		for (int r = 0; r<m_cur_n_scales; r++)
		{
			int cW = m_scaleSpace[r].cols;
			int cH = m_scaleSpace[r].rows;
		
			for (int j = border; j< cH - border; j++)
			{
				for (int i = border; i< cW - border; i++)
				{
					if (saliency[r][j * cW + i] > m_th_saliency)
					{
						bool is_max = true;

						for (int k = cv::max(0, r - m_nms_scale_radius); k <= cv::min(m_cur_n_scales - 1, r + m_nms_scale_radius); k++)
						{
							if (k != r)
							{
								int j_sc = cvRound(j * std::pow(m_scale_factor, r - k));
								int i_sc = cvRound(i * std::pow(m_scale_factor, r - k));

								if (saliency[r][j*cW + i] < saliency[k][j_sc*cW + i_sc])
								{
									is_max = false;
									break;
								}
							}
						}

						for (int v = cv::max(border, j - m_nms_radius); v <= cv::min(cH - border - 1, j + m_nms_radius); v++)
						{
							for (int u = cv::max(border, i - m_nms_radius); u <= cv::min(cW - border - 1, i + m_nms_radius); u++)
							{
								if (saliency[r][j*cW + i] < saliency[r][v*cW + u])
								{
									is_max = false;
									break;
								}
							}

							if (!is_max)
								break;
						}

						if (is_max)
						{
							kp_temp.pt.x = i * std::pow(m_scale_factor, r);
							kp_temp.pt.y = j * std::pow(m_scale_factor, r);
							kp_temp.response = saliency[r][j*cW + i];
                            kp_temp.size = (m_patch_radius*2.0f + 1) * std::pow(m_scale_factor, r);
                            //the size of the patch is fixed to 16
                            cv::Mat aux=cv::Mat((m_patch_radius*2.0f + 1),(m_patch_radius*2.0f + 1),CV_32F);
                            cv::Mat output = cv::Mat::zeros(16,16,CV_32F);

                            int it2=0;
                            //store the delta values around the center point
                            for (int jaux = (j-m_patch_radius);jaux<=j+m_patch_radius;jaux++)

                            {
                                int it1=0;
                                for (int iaux=(i-m_patch_radius);iaux<=i+(m_patch_radius);iaux++)
                                {

                                    aux.at<float>(it1,it2)=saliency[r][jaux*cW + iaux];
                                    it1++;
                                }
                                it2++;
                            }

                            //here i make a log-polar change and i create the quantization


                            if (m_compute_orientation)
                            {
								kp_temp.angle = computeOrientation(m_scaleSpace[r], i, j, orientPoints);
                               //normalize patch with angle and size
                               normalizepatch(16,kp_temp.angle,aux,output);
                            }
                            else{
                           //normalize patch with only size
                               normalizepatch(16,0.0f,aux,output);
                            }


                            aux_des.push_back(output);

							keypoints.push_back(kp_temp);



						}
					}
				}
			}
		}

	}

    void MsdDetector::normalizepatch(int size,float angle, cv::Mat input,cv::Mat& output)
     {


    //    b.y = center.y + M/2;

        output = cv::Mat::zeros(size,size,CV_32F);

        cv::Size outsize;
        outsize.height=size;
        outsize.width =size;

        cv::Point2f pt;

    // here there are a problem with the center, it depends on the value it´s not a trivial thing.
        // solved
        if ((input.cols%4)==1)
        {
            pt.x=cvRound(input.cols/2.0);
            pt.y =cvRound(input.rows/2.0);
        }
        else if((input.cols%4)==0)
        {

            pt.x=(input.cols/2.0)-0.5;
            pt.y =(input.rows/2.0)-0.5;
        }
        else if((input.cols%4)==2)
        {

            pt.x=(input.cols/2.0)-0.5;
            pt.y =(input.rows/2.0)-0.5;
        }
        else if((input.cols%4)==3)
        {

            pt.x=(input.cols/2.0)-0.5;
            pt.y =(input.rows/2.0)-0.5;
        }
        // to calculate the scale, is the size of the keypoint between
        // the scale is related to the diagonal of both pathces
       // float scale = 1.0f*std::sqrt((maskenter.height*maskenter.height)+(maskenter.height*maskenter.height))/std::sqrt((outsize.height*outsize.height)+(outsize.height*outsize.height));

        cv::Mat transform = cv::getRotationMatrix2D(pt,angle,1.0);
        cv::Mat source1;

        //ROTATE
       // warpAffine(fromI, rotI, R, rotI.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(0));
        cv::warpAffine(input,source1,transform,input.size(),cv::INTER_LINEAR+cv::WARP_INVERSE_MAP,cv::BORDER_REPLICATE);//+cv::WARP_INVERSE_MAP
        // works best in 2 steps instead of one.
        if (outsize.height!=input.cols)cv::resize(source1,output,outsize);
        else source1.copyTo(output);

    }

    std::vector<cv::KeyPoint> MsdDetector::detect(cv::Mat &img,int maxTiepoints)
	{
		int border = m_search_area_radius + m_patch_radius;

        //automatic computation of the number of scales
        if (m_n_scales == -1)
			m_cur_n_scales = cvFloor(std::log(cv::min(img.cols, img.rows) / ((m_patch_radius + m_search_area_radius)*2.0 + 1)) / std::log(m_scale_factor));
        else
            m_cur_n_scales = m_n_scales;

		cv::Mat imgG;
		if (img.channels() == 1)
			imgG = img;
		else
			cv::cvtColor(img, imgG, CV_BGR2GRAY);

		ImagePyramid scaleSpacer(imgG, m_cur_n_scales, m_scale_factor);
		m_scaleSpace = scaleSpacer.getImPyr();
		
		std::vector<cv::KeyPoint> keypoints;
		std::vector<float *> saliency;
		saliency.resize(m_cur_n_scales);

		for (int r = 0; r < m_cur_n_scales; r++)
		{
			saliency[r] = new float[m_scaleSpace[r].rows * m_scaleSpace[r].cols];
		}

		for (int r = 0; r<m_cur_n_scales; r++)
		{
			unsigned nThreads = boost::thread::hardware_concurrency();
			unsigned stepThread = (m_scaleSpace[r].cols - 2 * border) / nThreads;

			std::vector<boost::thread*> threads;
			for (unsigned i = 0; i < nThreads - 1; i++)
			{
				threads.push_back(new boost::thread(&MsdDetector::contextualSelfDissimilarity, this, m_scaleSpace[r], border + i*stepThread, border + (i + 1)*stepThread, saliency[r]));
			}
			threads.push_back(new boost::thread(&MsdDetector::contextualSelfDissimilarity, this, m_scaleSpace[r], border + (nThreads - 1)*stepThread, m_scaleSpace[r].cols - border, saliency[r]));

			for (unsigned i = 0; i < threads.size(); i++)
			{
				threads[i]->join();
				delete threads[i];
			}

            //contextualSelfDissimilarity(m_scaleSpace[r], border, m_scaleSpace[r].cols - border, saliency[r]);

		}
        std::vector<cv::Mat > aux_des;
        nonMaximaSuppression(saliency, keypoints,aux_des);

//        descriptormsd= cv::Mat(aux_des.size(),16*16,CV_32FC1);


//         for( int i = 0; i < aux_des.size(); i++ )
//         {
//             int i1=0;
//             for(int j=0;j<aux_des[i].cols;j++)
//             {

//                 for (int k=0;k<aux_des[i].rows;k++)
//                 {
//                        descriptormsd.at<float>(i,i1)=aux_des[i].at<float>(j,k);
//                        i1++;
//                 }

//             }
//         }



		for (int r = 0; r<m_n_scales; r++)
		{
			delete[] saliency[r];
		}

		m_scaleSpace.clear();


        if (maxTiepoints!=-1 && maxTiepoints<keypoints.size()) {
            //Sort tiepoints by response
            std::sort(keypoints.begin(), keypoints.end(), sortByStrength());
            std::vector<cv::KeyPoint>  *keypointsAux = new std::vector<cv::KeyPoint>(keypoints.end() - maxTiepoints, keypoints.end());
            keypoints.clear();
            keypoints.reserve( keypointsAux->size()); // preallocate memory

            keypoints.insert( keypoints.end(), keypointsAux->begin(), keypointsAux->end() );
        }

		return keypoints;
	}
