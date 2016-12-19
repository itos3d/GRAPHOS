/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#ifndef OPENCV_KPM_PARAMETERS_H
#define OPENCV_KPM_PARAMETERS_H

#define OPENCV_KPM_NO_ERROR                                                     0
#define OPENCV_KPM_ERROR                                                        1

#define OPENCV_KPM_DUPLICATED_PIXEL_TOLERANCE_UNIQUE_TH2                        2.0
#define OPENCV_KPM_DUPLICATED_PIXEL_TOLERANCE_MULTIPLE_TO_ONE_TH1               1.0
#define OPENCV_KPM_DUPLICATED_PIXEL_TOLERANCE_MULTIPLE_TO_ONE_TH2               4.0

#define OPENCV_KPM_SAVE_IMAGE_MATCHES_DEFAULT                                   "0" // Por defecto no guarda imágenes de matches

#define OPENCV_KPM_DATABASE_TAG_TRUE                                            "TRUE"
#define OPENCV_KPM_DATABASE_TAG_FALSE                                           "FALSE"

#define OPENCV_KPM_PARAMETERSFILENAME                                           "opencv_kpm_parameters.txt"

#define OPENCV_KPM_ENGINES_INITIAL_TAG                                          "OpenCV: "
//#define OPENCV_KPM_SIFT_SIFT_BRUTEFORCE_ENGINE_TAG                              OPENCV_KPM_ENGINES_INITIAL_TAG+"Sift (key points detector) + Sift (key points descriptors) + Brute-Force (matching)"
#define OPENCV_KPM_SIFT_SIFT_BRUTEFORCE_ENGINE_TAG                              "OpenCV: Sift (key points detector) + Sift (key points descriptors) + Brute-Force (matching)"
#define OPENCV_KPM_SIFT_SIFT_BRUTEFORCE_PATH                                    "kpmSiftSiftBf"

#define OPENCV_KPM_VALUE_STRING_SEPARATOR                                       "#"
#define OPENCV_KPM_TAG_STRING_SEPARATOR                                         "_"
#define OPENCV_KPM_TAG_IMAGES_PATH                                              "IMAGES-PATH"
#define OPENCV_KPM_TAG_IMAGE_PAIRS_FILENAME                                     "IMAGE-PAIRS-FILENAME"
#define OPENCV_KPM_TAG_SAVE_IMAGE_MATCHES                                       "SAVE-IMAGE-MATCHES"
#define OPENCV_KPM_TAG_BIDIRECTIONAL_MATCHES                                    "BIDIRECTIONAL-MATCHES"
#define OPENCV_KPM_TAG_PATH_FOR_MATCHES_FILES                                   "PATH-FOR-MATCHES-FILES"

#define OPENCV_KPM_TAG_DETECTORS                                                "DETECTOR-(FAST,ORB,SIFT,STAR,SURF,BRISK)"
#define OPENCV_KPM_QPARAMS_TAG_DETECTORS                                        "OpenCvKeyPointDetector"
#define OPENCV_KPM_TAG_DESCRIPTORS                                              "DESCRIPTOR-(BRIEF,ORB,SIFT,SURF,BRISK)"
#define OPENCV_KPM_QPARAMS_TAG_DESCRIPTORS                                      "OpenCvKeyPointDescriptor"
#define OPENCV_KPM_TAG_OUTLIERSDETECTORS                                        "OUTLIERSDETECTOR-(OUTLIERS-DHL-KMEANS)"
#define OPENCV_KPM_TAG_MATCHERS                                                 "MATCHER-(BRUTEFORCE,FLANN)"
#define OPENCV_KPM_QPARAMS_TAG_MATCHERS                                         "OpenCvMatcher"
#define OPENCV_KPM_TAG_MATCHINGDISTANCES                                        "MATCHINDISTANCE-(NORM_L2,NORM_HAMMING)"
#define OPENCV_KPM_TAG_DETECTOR                                                 "DETECTOR"
#define OPENCV_KPM_TAG_DESCRIPTOR                                               "DESCRIPTOR"
#define OPENCV_KPM_TAG_MATCHER                                                  "MATCHER"
#define OPENCV_KPM_TAG_OUTLIERSDETECTOR                                         "OUTLIERSDETECTOR"

#define OPENCV_KPM_IMAGE_FILE_EXTENSION_FORMAT_PNG                              ".png"
#define OPENCV_KPM_IMAGE_FILE_WITHOUT_OURLIERS_SUFFIX                           "_sinErrores"
#define OPENCV_KPM_IMAGE_FILE_WITHOUT_DUPLICATES_SUFFIX                         "_sinDuplicados"
#define OPENCV_KPM_PREFIX_FOLDER_IMAGE_MATCHES_FILES                            "Pastis"
#define OPENCV_KPM_PREFIX_IMAGE_MATCHES_FILE_EXTENSION                          ".txt"
#define OPENCV_KPM_IMAGE_MATCHES_PRECISION                                      6

#define OPENCV_KPM_NO_STRING_VALUE                                              "#####"
#define OPENCV_KPM_NO_INTEGER_VALUE                                             -99999
#define OPENCV_KPM_NO_DOUBLE_VALUE                                              -99999.999
#define OPENCV_KPM_TOLERANCE                                                    0.001
#define OPENCV_KPM_PARAMETERS_PRECISION                                         2

#define OPENCV_KPM_TAG_INT                                                      "int"
#define OPENCV_KPM_TAG_DOUBLE                                                   "dbl"
#define OPENCV_KPM_TAG_BOOL                                                     "bool"
#define OPENCV_KPM_TAG_STRING                                                   "str"

#define OPENCV_KPM_DETECTOR_TAG                                                 "DETECTOR"
#define OPENCV_KPM_DETECTOR_TYPE                                                OPENCV_KPM_TAG_STRING

#define OPENCV_KPM_DESCRIPTOR_TAG                                               "DESCRIPTOR"
#define OPENCV_KPM_DESCRIPTOR_TYPE                                              OPENCV_KPM_TAG_STRING

//#define OPENCV_KPM_DETECTOR_DENSE_TAG                                           "Dense"
#define OPENCV_KPM_DETECTOR_FAST_TAG                                            "FAST"
//#define OPENCV_KPM_DETECTOR_GFTT_TAG                                            "GFTT"
//#define OPENCV_KPM_DETECTOR_MSER_TAG                                            "MSER"
#define OPENCV_KPM_DETECTOR_ORB_TAG                                             "ORB"
#define OPENCV_KPM_DETECTOR_SIFT_TAG                                            "SIFT"
#define OPENCV_KPM_DETECTOR_STAR_TAG                                            "STAR"
#define OPENCV_KPM_DETECTOR_SURF_TAG                                            "SURF"
#define OPENCV_KPM_DETECTOR_BRISK_TAG                                           "BRISK"

//#define OPENCV_KPM_DESCRIPTOR_FREAK_TAG                                         "FREAK"
#define OPENCV_KPM_DESCRIPTOR_BRIEF_TAG                                         "BRIEF"
#define OPENCV_KPM_DESCRIPTOR_ORB_TAG                                           "ORB"
#define OPENCV_KPM_DESCRIPTOR_SIFT_TAG                                          "SIFT"
#define OPENCV_KPM_DESCRIPTOR_SURF_TAG                                          "SURF"
#define OPENCV_KPM_DESCRIPTOR_BRISK_TAG                                         "BRISK"

#define OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG                              "OUTLIERS-DHL-KMEANS"

#define OPENCV_KPM_MATCHER_TAG                                                  "MATCHER"  // Para los parámetros generales
#define OPENCV_KPM_MATCHER_BRUTEFORCE_TAG                                       "BRUTEFORCE"
#define OPENCV_KPM_MATCHER_FLANN_LINEAR_TAG                                     "FLANN-LINEAR"
#define OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG                                     "FLANN-KDTREE"
#define OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG                                     "FLANN-KMEANS"
#define OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG                                  "FLANN-COMPOSITE"
#define OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG                                  "FLANN-AUTOTUNED"
#define OPENCV_KPM_MATCHER_FLANN_LSH_TAG                                        "FLANN-LSH"

#define OPENCV_KPM_MATCHINGDISTANCE_DEFAULT_TAG                                 "NORM_L2"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_INF_TAG                                "NORM_INF"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_L1_TAG                                 "NORM_L1"
#define OPENCV_KPM_MATCHINGDISTANCE_NORM_L2_TAG                                 "NORM_L2"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_L2SQR_TAG                              "NORM_L2SQR"
#define OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING_TAG                            "NORM_HAMMING"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING2_TAG                           "NORM_HAMMING2"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_TYPE_MASK_TAG                          "NORM_TYPE_MASK"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_RELATIVE_TAG                           "NORM_RELATIVE"
//#define OPENCV_KPM_MATCHINGDISTANCE_NORM_MINMAX_TAG                             "NORM_MINMAX"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_TAG                       "applyDetection"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_QPARAMS_TAG               "OUTLIERS-DHL-KMEANS_applyDetection"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_TYPE                      OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_DEFAULT                   "1"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_TAG              "azimuthNumberOfClusters"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_QPARAMS_TAG      "OUTLIERS-DHL-KMEANS_azimuthNumberOfClusters"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_TYPE             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_DEFAULT          "8"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_MIN              "4"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_MAX              "100"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_TAG                    "azimuthEpsilonDeg"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_QPARAMS_TAG            "OUTLIERS-DHL-KMEANS_azimuthEpsilonDeg"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_TYPE                   OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_DEFAULT                "20.0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_MIN                    "1.0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_MAX                    "25.0"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_TAG                    "azimuthIterations"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_QPARAMS_TAG            "OUTLIERS-DHL-KMEANS_azimuthIterations"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_TYPE                   OPENCV_KPM_TAG_INT
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_DEFAULT                "100"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_MIN                    "0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_MAX                    "1000"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_TAG             "distanceNumberOfCluster"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_QPARAMS_TAG     "OUTLIERS-DHL-KMEANS_distanceNumberOfCluster"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_TYPE            OPENCV_KPM_TAG_INT
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_DEFAULT         "6"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_MIN             "4"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_MAX             "100"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_TAG                      "distanceEpsilon"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_QPARAMS_TAG              "OUTLIERS-DHL-KMEANS_distanceEpsilon"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_TYPE                     OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_DEFAULT                  "200.0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_MIN                      "1.0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_MAX                      "250.0"

#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_TAG                   "distanceIterations"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_QPARAMS_TAG           "OUTLIERS-DHL-KMEANS_distanceIterations"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_TYPE                  OPENCV_KPM_TAG_INT
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_DEFAULT               "100"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_MIN                   "0"
#define OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_MAX                   "1000"

#define OPENCV_KPM_BRISK_OCTAVES_TAG                            "OCTAVES"
#define OPENCV_KPM_BRISK_OCTAVES_QPARAMS_TAG                    "BRISK_OCTAVES"
#define OPENCV_KPM_BRISK_OCTAVES_TYPE                           OPENCV_KPM_TAG_INT
#define OPENCV_KPM_BRISK_OCTAVES_DEFAULT                        "3"
#define OPENCV_KPM_BRISK_OCTAVES_MIN                            "0"
#define OPENCV_KPM_BRISK_OCTAVES_MAX                            "1000"

#define OPENCV_KPM_BRISK_PATTERSCALE_TAG                        "patternScale"
#define OPENCV_KPM_BRISK_PATTERSCALE_QPARAMS_TAG                "BRISK_patternScale"
#define OPENCV_KPM_BRISK_PATTERSCALE_TYPE                       OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_BRISK_PATTERSCALE_DEFAULT                    "1.0"
#define OPENCV_KPM_BRISK_PATTERSCALE_MIN                        "0.0"
#define OPENCV_KPM_BRISK_PATTERSCALE_MAX                        "1000.0"

#define OPENCV_KPM_BRISK_THRESH_TAG                             "thresh"
#define OPENCV_KPM_BRISK_THRESH_QPARAMS_TAG                     "BRISK_thresh"
#define OPENCV_KPM_BRISK_THRESH_TYPE                            OPENCV_KPM_TAG_INT
#define OPENCV_KPM_BRISK_THRESH_DEFAULT                         "30"
#define OPENCV_KPM_BRISK_THRESH_MIN                             "0"
#define OPENCV_KPM_BRISK_THRESH_MAX                             "1000"

#define OPENCV_KPM_BRIEF_BYTES_TAG                              "bytes"
#define OPENCV_KPM_BRIEF_BYTES_QPARAMS_TAG                      "BRIEF_bytes"
#define OPENCV_KPM_BRIEF_BYTES_TYPE                             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_BRIEF_BYTES_DEFAULT                          "32"
#define OPENCV_KPM_BRIEF_BYTES_MIN                              "0"
#define OPENCV_KPM_BRIEF_BYTES_MAX                              "1000"

//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_TAG                 "featureScaleLevels"
//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_QPARAMS_TAG         "DENSE_featureScaleLevels"
//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_TYPE                OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_DEFAULT             "1"
//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_MIN                 "0"
//#define OPENCV_KPM_DENSE_FEATURESCALELEVELS_MAX                 "1000"

//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_TAG                    "featureScaleMul"
//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_QPARAMS_TAG            "DENSE_featureScaleMul"
//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_TYPE                   OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_DEFAULT                "0.1"
//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_MIN                    "0.0"
//#define OPENCV_KPM_DENSE_FEATURESCALEMUL_MAX                    "1000.0"

//#define OPENCV_KPM_DENSE_INITFEATURESCALE_TAG                   "initFeatureScale"
//#define OPENCV_KPM_DENSE_INITFEATURESCALE_QPARAMS_TAG           "DENSE_initFeatureScale"
//#define OPENCV_KPM_DENSE_INITFEATURESCALE_TYPE                  OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_DENSE_INITFEATURESCALE_DEFAULT               "1.0"
//#define OPENCV_KPM_DENSE_INITFEATURESCALE_MIN                   "0.0"
//#define OPENCV_KPM_DENSE_INITFEATURESCALE_MAX                   "1000.0"

//#define OPENCV_KPM_DENSE_INITIMGBOUND_TAG                       "initImgBound"
//#define OPENCV_KPM_DENSE_INITIMGBOUND_QPARAMS_TAG               "DENSE_initImgBound"
//#define OPENCV_KPM_DENSE_INITIMGBOUND_TYPE                      OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_DENSE_INITIMGBOUND_DEFAULT                   "0"
//#define OPENCV_KPM_DENSE_INITIMGBOUND_MIN                       "0"
//#define OPENCV_KPM_DENSE_INITIMGBOUND_MAX                       "1000"

//#define OPENCV_KPM_DENSE_INITXYSTEP_TAG                         "initXyStep"
//#define OPENCV_KPM_DENSE_INITXYSTEP_QPARAMS_TAG                 "DENSE_initXyStep"
//#define OPENCV_KPM_DENSE_INITXYSTEP_TYPE                        OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_DENSE_INITXYSTEP_DEFAULT                     "6"
//#define OPENCV_KPM_DENSE_INITXYSTEP_MIN                         "0"
//#define OPENCV_KPM_DENSE_INITXYSTEP_MAX                         "10000"

//#define OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_TAG              "varyImgBoundWithScale"
//#define OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_QPARAMS_TAG      "DENSE_varyImgBoundWithScale"
//#define OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_TYPE             OPENCV_KPM_TAG_BOOL
//#define OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_DEFAULT          "0"

//#define OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_TAG                "varyXyStepWithScale"
//#define OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_QPARAMS_TAG        "DENSE_varyXyStepWithScale"
//#define OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_TYPE               OPENCV_KPM_TAG_BOOL
//#define OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_DEFAULT            "1"

// Para retina de ojo
//#define OPENCV_KPM_FREAK_NOCTAVES_TAG                           "nOctaves"
//#define OPENCV_KPM_FREAK_NOCTAVES_QPARAMS_TAG                   "FREAK_nOctaves"
//#define OPENCV_KPM_FREAK_NOCTAVES_TYPE                          OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_FREAK_NOCTAVES_DEFAULT                       "4"
//#define OPENCV_KPM_FREAK_NOCTAVES_MIN                           "0"
//#define OPENCV_KPM_FREAK_NOCTAVES_MAX                           "1000"

//#define OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_TAG              "orientationNormalized"
//#define OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_QPARAMS_TAG      "FREAK_orientationNormalized"
//#define OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_TYPE             OPENCV_KPM_TAG_BOOL
//#define OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_DEFAULT          "1"

//#define OPENCV_KPM_FREAK_PATTERNSCALE_TAG                       "patternScale"
//#define OPENCV_KPM_FREAK_PATTERNSCALE_QPARAMS_TAG               "FREAK_patternScale"
//#define OPENCV_KPM_FREAK_PATTERNSCALE_TYPE                      OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_FREAK_PATTERNSCALE_DEFAULT                   "22.0"
//#define OPENCV_KPM_FREAK_PATTERNSCALE_MIN                       "0.0"
//#define OPENCV_KPM_FREAK_PATTERNSCALE_MAX                       "1000.0"

//#define OPENCV_KPM_FREAK_SCALENORMALIZED_TAG                    "scaleNormalized"
//#define OPENCV_KPM_FREAK_SCALENORMALIZED_QPARAMS_TAG            "FREAK_scaleNormalized"
//#define OPENCV_KPM_FREAK_SCALENORMALIZED_TYPE                   OPENCV_KPM_TAG_BOOL
//#define OPENCV_KPM_FREAK_SCALENORMALIZED_DEFAULT                "1"

#define OPENCV_KPM_FAST_NONMAXSUPPRESSION_TAG                   "nonmaxSuppression"
#define OPENCV_KPM_FAST_NONMAXSUPPRESSION_QPARAMS_TAG           "FAST_nonmaxSuppression"
#define OPENCV_KPM_FAST_NONMAXSUPPRESSION_TYPE                  OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_FAST_NONMAXSUPPRESSION_DEFAULT               "1"

#define OPENCV_KPM_FAST_THRESHOLD_TAG                           "threshold"
#define OPENCV_KPM_FAST_THRESHOLD_QPARAMS_TAG                   "FAST_threshold"
#define OPENCV_KPM_FAST_THRESHOLD_TYPE                          OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FAST_THRESHOLD_DEFAULT                       "10"
#define OPENCV_KPM_FAST_THRESHOLD_MIN                           "0"
#define OPENCV_KPM_FAST_THRESHOLD_MAX                           "1000"

// obsoleto
//#define OPENCV_KPM_GFTT_BLOCKSIZE_TAG                           "blockSize"
//#define OPENCV_KPM_GFTT_BLOCKSIZE_QPARAMS_TAG                   "GFTT_blockSize"
//#define OPENCV_KPM_GFTT_BLOCKSIZE_TYPE                          OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_GFTT_BLOCKSIZE_DEFAULT                       "3"
//#define OPENCV_KPM_GFTT_BLOCKSIZE_MIN                           "0"
//#define OPENCV_KPM_GFTT_BLOCKSIZE_MAX                           "1000"

//#define OPENCV_KPM_GFTT_K_TAG                                   "k"
//#define OPENCV_KPM_GFTT_K_QPARAMS_TAG                           "GFTT_k"
//#define OPENCV_KPM_GFTT_K_TYPE                                  OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_GFTT_K_DEFAULT                               "0.04"
//#define OPENCV_KPM_GFTT_K_MIN                                   "0.0"
//#define OPENCV_KPM_GFTT_K_MAX                                   "1000.0"

//#define OPENCV_KPM_GFTT_MAXCORNERS_TAG                          "maxCorners"
//#define OPENCV_KPM_GFTT_MAXCORNERS_QPARAMS_TAG                  "GFTT_maxCorners"
//#define OPENCV_KPM_GFTT_MAXCORNERS_TYPE                         OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_GFTT_MAXCORNERS_DEFAULT                      "1000"
//#define OPENCV_KPM_GFTT_MAXCORNERS_MIN                          "0"
//#define OPENCV_KPM_GFTT_MAXCORNERS_MAX                          "10000"

//#define OPENCV_KPM_GFTT_MINDISTANCE_TAG                         "minDistance"
//#define OPENCV_KPM_GFTT_MINDISTANCE_QPARAMS_TAG                 "GFTT_minDistance"
//#define OPENCV_KPM_GFTT_MINDISTANCE_TYPE                        OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_GFTT_MINDISTANCE_DEFAULT                     "1.0"
//#define OPENCV_KPM_GFTT_MINDISTANCE_MIN                         "0"
//#define OPENCV_KPM_GFTT_MINDISTANCE_MAX                         "1000.0"

//#define OPENCV_KPM_GFTT_QUALITYLEVEL_TAG                        "qualityLevel"
//#define OPENCV_KPM_GFTT_QUALITYLEVEL_QPARAMS_TAG                "GFTT_qualityLevel"
//#define OPENCV_KPM_GFTT_QUALITYLEVEL_TYPE                       OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_GFTT_QUALITYLEVEL_DEFAULT                    "0.01"
//#define OPENCV_KPM_GFTT_QUALITYLEVEL_MIN                        "0.0"
//#define OPENCV_KPM_GFTT_QUALITYLEVEL_MAX                        "1000.0"

//#define OPENCV_KPM_GFTT_USEHARRISDETECTOR_TAG                   "useHarrisDetector"
//#define OPENCV_KPM_GFTT_USEHARRISDETECTOR_QPARAMS_TAG           "GFTT_useHarrisDetector"
//#define OPENCV_KPM_GFTT_USEHARRISDETECTOR_TYPE                  OPENCV_KPM_TAG_BOOL
//#define OPENCV_KPM_GFTT_USEHARRISDETECTOR_DEFAULT               "0"

// Para gotas
//#define OPENCV_KPM_MSER_AREATHRESHOLD_TAG                       "areaThreshold"
//#define OPENCV_KPM_MSER_AREATHRESHOLD_QPARAMS_TAG               "MSER_areaThreshold"
//#define OPENCV_KPM_MSER_AREATHRESHOLD_TYPE                      OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_MSER_AREATHRESHOLD_DEFAULT                   "1.01"
//#define OPENCV_KPM_MSER_AREATHRESHOLD_MIN                       "0.0"
//#define OPENCV_KPM_MSER_AREATHRESHOLD_MAX                       "1000.0"

//#define OPENCV_KPM_MSER_DELTA_TAG                               "delta"
//#define OPENCV_KPM_MSER_DELTA_QPARAMS_TAG                       "MSER_delta"
//#define OPENCV_KPM_MSER_DELTA_TYPE                              OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_MSER_DELTA_DEFAULT                           "5"
//#define OPENCV_KPM_MSER_DELTA_MIN                               "0"
//#define OPENCV_KPM_MSER_DELTA_MAX                               "1000"

//#define OPENCV_KPM_MSER_EDGEBLURSIZE_TAG                        "edgeBlurSize"
//#define OPENCV_KPM_MSER_EDGEBLURSIZE_QPARAMS_TAG                "MSER_edgeBlurSize"
//#define OPENCV_KPM_MSER_EDGEBLURSIZE_TYPE                       OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_MSER_EDGEBLURSIZE_DEFAULT                    "5"
//#define OPENCV_KPM_MSER_EDGEBLURSIZE_MIN                        "0"
//#define OPENCV_KPM_MSER_EDGEBLURSIZE_MAX                        "1000"

//#define OPENCV_KPM_MSER_MAXAREA_TAG                             "maxArea"
//#define OPENCV_KPM_MSER_MAXAREA_QPARAMS_TAG                     "MSER_maxArea"
//#define OPENCV_KPM_MSER_MAXAREA_TYPE                            OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_MSER_MAXAREA_DEFAULT                         "14400"
//#define OPENCV_KPM_MSER_MAXAREA_MIN                             "0"
//#define OPENCV_KPM_MSER_MAXAREA_MAX                             "100000"

//#define OPENCV_KPM_MSER_MAXEVOLUTION_TAG                        "maxEvolution"
//#define OPENCV_KPM_MSER_MAXEVOLUTION_QPARAMS_TAG                "MSER_maxEvolution"
//#define OPENCV_KPM_MSER_MAXEVOLUTION_TYPE                       OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_MSER_MAXEVOLUTION_DEFAULT                    "200"
//#define OPENCV_KPM_MSER_MAXEVOLUTION_MIN                        "0"
//#define OPENCV_KPM_MSER_MAXEVOLUTION_MAX                        "10000"

//#define OPENCV_KPM_MSER_MAXVARIATION_TAG                        "maxVariation"
//#define OPENCV_KPM_MSER_MAXVARIATION_QPARAMS_TAG                "MSER_maxVariation"
//#define OPENCV_KPM_MSER_MAXVARIATION_TYPE                       OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_MSER_MAXVARIATION_DEFAULT                    "0.25"
//#define OPENCV_KPM_MSER_MAXVARIATION_MIN                        "0.0"
//#define OPENCV_KPM_MSER_MAXVARIATION_MAX                        "10000.0"

//#define OPENCV_KPM_MSER_MINAREA_TAG                             "minArea"
//#define OPENCV_KPM_MSER_MINAREA_QPARAMS_TAG                     "MSER_minArea"
//#define OPENCV_KPM_MSER_MINAREA_TYPE                            OPENCV_KPM_TAG_INT
//#define OPENCV_KPM_MSER_MINAREA_DEFAULT                         "60"
//#define OPENCV_KPM_MSER_MINAREA_MIN                             "0"
//#define OPENCV_KPM_MSER_MINAREA_MAX                             "100000"

//#define OPENCV_KPM_MSER_MINDIVERSITY_TAG                        "minDiversity"
//#define OPENCV_KPM_MSER_MINDIVERSITY_QPARAMS_TAG                "MSER_minDiversity"
//#define OPENCV_KPM_MSER_MINDIVERSITY_TYPE                       OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_MSER_MINDIVERSITY_DEFAULT                    "0.20"
//#define OPENCV_KPM_MSER_MINDIVERSITY_MIN                        "0.0"
//#define OPENCV_KPM_MSER_MINDIVERSITY_MAX                        "10000.0"

//#define OPENCV_KPM_MSER_MINMARGIN_TAG                           "minMargin"
//#define OPENCV_KPM_MSER_MINMARGIN_QPARAMS_TAG                   "MSER_minMargin"
//#define OPENCV_KPM_MSER_MINMARGIN_TYPE                          OPENCV_KPM_TAG_DOUBLE
//#define OPENCV_KPM_MSER_MINMARGIN_DEFAULT                       "0.003"
//#define OPENCV_KPM_MSER_MINMARGIN_MIN                           "0.0"
//#define OPENCV_KPM_MSER_MINMARGIN_MAX                           "10000.0"

#define OPENCV_KPM_ORB_WTA_K_TAG                                "WTA-K"
#define OPENCV_KPM_ORB_WTA_K_QPARAMS_TAG                        "ORB_WTA-K"
#define OPENCV_KPM_ORB_WTA_K_TYPE                               OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_WTA_K_DEFAULT                            "2"
#define OPENCV_KPM_ORB_WTA_K_MIN                                "0"
#define OPENCV_KPM_ORB_WTA_K_MAX                                "1000"

#define OPENCV_KPM_ORB_EDGETHRESHOLD_TAG                        "edgeThreshold"
#define OPENCV_KPM_ORB_EDGETHRESHOLD_QPARAMS_TAG                "ORB_edgeThreshold"
#define OPENCV_KPM_ORB_EDGETHRESHOLD_TYPE                       OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_EDGETHRESHOLD_DEFAULT                    "31"
#define OPENCV_KPM_ORB_EDGETHRESHOLD_MIN                        "0"
#define OPENCV_KPM_ORB_EDGETHRESHOLD_MAX                        "1000"

#define OPENCV_KPM_ORB_FIRSTLEVEL_TAG                           "firstLevel"
#define OPENCV_KPM_ORB_FIRSTLEVEL_QPARAMS_TAG                   "ORB_firstLevel"
#define OPENCV_KPM_ORB_FIRSTLEVEL_TYPE                          OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_FIRSTLEVEL_DEFAULT                       "0"
#define OPENCV_KPM_ORB_FIRSTLEVEL_MIN                           "0"
#define OPENCV_KPM_ORB_FIRSTLEVEL_MAX                           "1000"

#define OPENCV_KPM_ORB_NFEATURES_TAG                            "nFeatures"
#define OPENCV_KPM_ORB_NFEATURES_QPARAMS_TAG                    "ORB_nFeatures"
#define OPENCV_KPM_ORB_NFEATURES_TYPE                           OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_NFEATURES_DEFAULT                        "500"
#define OPENCV_KPM_ORB_NFEATURES_MIN                            "0"
#define OPENCV_KPM_ORB_NFEATURES_MAX                            "10000"

#define OPENCV_KPM_ORB_NLEVELS_TAG                              "nLevels"
#define OPENCV_KPM_ORB_NLEVELS_QPARAMS_TAG                      "ORB_nLevels"
#define OPENCV_KPM_ORB_NLEVELS_TYPE                             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_NLEVELS_DEFAULT                          "8"
#define OPENCV_KPM_ORB_NLEVELS_MIN                              "0"
#define OPENCV_KPM_ORB_NLEVELS_MAX                              "1000"

#define OPENCV_KPM_ORB_PATCHSIZE_TAG                            "patchSize"
#define OPENCV_KPM_ORB_PATCHSIZE_QPARAMS_TAG                    "ORB_patchSize"
#define OPENCV_KPM_ORB_PATCHSIZE_TYPE                           OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_PATCHSIZE_DEFAULT                        "31"
#define OPENCV_KPM_ORB_PATCHSIZE_MIN                            "0"
#define OPENCV_KPM_ORB_PATCHSIZE_MAX                            "1000"

#define OPENCV_KPM_ORB_SCALEFACTOR_TAG                          "scaleFactor"
#define OPENCV_KPM_ORB_SCALEFACTOR_QPARAMS_TAG                  "ORB_scaleFactor"
#define OPENCV_KPM_ORB_SCALEFACTOR_TYPE                         OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_ORB_SCALEFACTOR_DEFAULT                      "1.20"
#define OPENCV_KPM_ORB_SCALEFACTOR_MIN                          "0.0"
#define OPENCV_KPM_ORB_SCALEFACTOR_MAX                          "1000.0"

#define OPENCV_KPM_ORB_SCORETYPE_TAG                            "scoreType"
#define OPENCV_KPM_ORB_SCORETYPE_QPARAMS_TAG                    "ORB_scoreType"
#define OPENCV_KPM_ORB_SCORETYPE_TYPE                           OPENCV_KPM_TAG_INT
#define OPENCV_KPM_ORB_SCORETYPE_DEFAULT                        "0"
#define OPENCV_KPM_ORB_SCORETYPE_MIN                            "0"
#define OPENCV_KPM_ORB_SCORETYPE_MAX                            "1000"

#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_TAG                   "contrastThreshold"
#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_QPARAMS_TAG           "SIFT_contrastThreshold"
#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_TYPE                  OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_DEFAULT               "0.04"
#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_MIN                   "0.0"
#define OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_MAX                   "1.0"

#define OPENCV_KPM_SIFT_EDGETHRESHOLD_TAG                       "edgeThreshold"
#define OPENCV_KPM_SIFT_EDGETHRESHOLD_QPARAMS_TAG               "SIFT_edgeThreshold"
#define OPENCV_KPM_SIFT_EDGETHRESHOLD_TYPE                      OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_SIFT_EDGETHRESHOLD_DEFAULT                   "10.0"
#define OPENCV_KPM_SIFT_EDGETHRESHOLD_MIN                       "0.0"
#define OPENCV_KPM_SIFT_EDGETHRESHOLD_MAX                       "100.0"

#define OPENCV_KPM_SIFT_NOCTAVELAYERS_TAG                       "nOctaveLayers"
#define OPENCV_KPM_SIFT_NOCTAVELAYERS_QPARAMS_TAG               "SIFT_nOctaveLayers"
#define OPENCV_KPM_SIFT_NOCTAVELAYERS_TYPE                      OPENCV_KPM_TAG_INT
#define OPENCV_KPM_SIFT_NOCTAVELAYERS_DEFAULT                   "3"
#define OPENCV_KPM_SIFT_NOCTAVELAYERS_MIN                       "0"
#define OPENCV_KPM_SIFT_NOCTAVELAYERS_MAX                       "100"

#define OPENCV_KPM_SIFT_NFEATURES_TAG                           "nFeatures"
#define OPENCV_KPM_SIFT_NFEATURES_QPARAMS_TAG                   "SIFT_nFeatures"
#define OPENCV_KPM_SIFT_NFEATURES_TYPE                          OPENCV_KPM_TAG_INT
#define OPENCV_KPM_SIFT_NFEATURES_DEFAULT                       "0"
#define OPENCV_KPM_SIFT_NFEATURES_MIN                           "0"
#define OPENCV_KPM_SIFT_NFEATURES_MAX                           "100000"

#define OPENCV_KPM_SIFT_SIGMA_TAG                               "sigma"
#define OPENCV_KPM_SIFT_SIGMA_QPARAMS_TAG                       "SIFT_sigma"
#define OPENCV_KPM_SIFT_SIGMA_TYPE                              OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_SIFT_SIGMA_DEFAULT                           "1.6"
#define OPENCV_KPM_SIFT_SIGMA_MIN                               "0"
#define OPENCV_KPM_SIFT_SIGMA_MAX                               "10.0"

#define OPENCV_KPM_SURF_EXTENDED_TAG                            "extended"
#define OPENCV_KPM_SURF_EXTENDED_QPARAMS_TAG                    "SURF_extended"
#define OPENCV_KPM_SURF_EXTENDED_TYPE                           OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_SURF_EXTENDED_DEFAULT                        "1"

#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_TAG                    "hessianThreshold"
#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_QPARAMS_TAG            "SURF_hessianThreshold"
#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_TYPE                   OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_DEFAULT                "600.0"
#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_MIN                    "0.0"
#define OPENCV_KPM_SURF_HESSIANTHRESHOLD_MAX                    "10000.0"

#define OPENCV_KPM_SURF_NOCTAVELAYERS_TAG                       "nOctaveLayers"
#define OPENCV_KPM_SURF_NOCTAVELAYERS_QPARAMS_TAG               "SURF_nOctaveLayers"
#define OPENCV_KPM_SURF_NOCTAVELAYERS_TYPE                      OPENCV_KPM_TAG_INT
#define OPENCV_KPM_SURF_NOCTAVELAYERS_DEFAULT                   "2"
#define OPENCV_KPM_SURF_NOCTAVELAYERS_MIN                       "0"
#define OPENCV_KPM_SURF_NOCTAVELAYERS_MAX                       "1000"

#define OPENCV_KPM_SURF_NOCTAVES_TAG                            "nOctaves"
#define OPENCV_KPM_SURF_NOCTAVES_QPARAMS_TAG                    "SURF_nOctaves"
#define OPENCV_KPM_SURF_NOCTAVES_TYPE                           OPENCV_KPM_TAG_INT
#define OPENCV_KPM_SURF_NOCTAVES_DEFAULT                        "4"
#define OPENCV_KPM_SURF_NOCTAVES_MIN                            "0"
#define OPENCV_KPM_SURF_NOCTAVES_MAX                            "1000"

#define OPENCV_KPM_SURF_UPRIGHT_TAG                             "upright"
#define OPENCV_KPM_SURF_UPRIGHT_QPARAMS_TAG                     "SURF_upright"
#define OPENCV_KPM_SURF_UPRIGHT_TYPE                            OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_SURF_UPRIGHT_DEFAULT                         "0"

#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_TAG              "lineThresholdBinarized"
#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_QPARAMS_TAG      "STAR_lineThresholdBinarized"
#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_TYPE             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_DEFAULT          "8"
#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_MIN              "0"
#define OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_MAX              "1000"

#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_TAG              "lineThresholdProjected"
#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_QPARAMS_TAG      "STAR_lineThresholdProjected"
#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_TYPE             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_DEFAULT          "10"
#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_MIN              "0"
#define OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_MAX              "1000"

#define OPENCV_KPM_STAR_MAXSIZE_TAG                             "maxSize"
#define OPENCV_KPM_STAR_MAXSIZE_QPARAMS_TAG                     "STAR_maxSize"
#define OPENCV_KPM_STAR_MAXSIZE_TYPE                            OPENCV_KPM_TAG_INT
#define OPENCV_KPM_STAR_MAXSIZE_DEFAULT                         "45"
#define OPENCV_KPM_STAR_MAXSIZE_MIN                             "0"
#define OPENCV_KPM_STAR_MAXSIZE_MAX                             "1000"

#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_TAG                   "responseThreshold"
#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_QPARAMS_TAG           "STAR_responseThreshold"
#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_TYPE                  OPENCV_KPM_TAG_INT
#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_DEFAULT               "30"
#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_MIN                   "0"
#define OPENCV_KPM_STAR_RESPONSETHRESHOLD_MAX                   "1000"

#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_TAG                  "suppressNonmaxSize"
#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_QPARAMS_TAG          "STAR_suppressNonmaxSize"
#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_TYPE                 OPENCV_KPM_TAG_INT
#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_DEFAULT              "5"
#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_MIN                  "0"
#define OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_MAX                  "1000"

#define OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TAG                    "crossCheck"
#define OPENCV_KPM_BRUTEFORCE_CROSSCHECK_QPARAMS_TAG            "BRUTEFORCE_crossCheck"
#define OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TYPE                   OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_BRUTEFORCE_CROSSCHECK_DEFAULT                "1"

// 20140222

#define OPENCV_KPM_MATCHER_KBESTMATCHES_TAG                     "kBestMatches"
#define OPENCV_KPM_MATCHER_KBESTMATCHES_QPARAMS_TAG             "MATCHER_kBestMatches"
#define OPENCV_KPM_MATCHER_KBESTMATCHES_TYPE                    OPENCV_KPM_TAG_INT
#define OPENCV_KPM_MATCHER_KBESTMATCHES_DEFAULT                 "2"
#define OPENCV_KPM_MATCHER_KBESTMATCHES_MIN                     "1"
#define OPENCV_KPM_MATCHER_KBESTMATCHES_MAX                     "2"

#define OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_TAG           "applyRatioTestDistance"
#define OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_QPARAMS_TAG   "MATCHER_applyRatioTestDistance"
#define OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_TYPE          OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_DEFAULT       "1"

#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_TAG                "ratioTestDistance"
#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_QPARAMS_TAG        "MATCHER_ratioTestDistance"
#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_TYPE                OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_DEFAULT             "0.75"
#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_MIN                 "0.0"
#define OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_MAX                 "2.0"

#define OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_TAG         "applyMinimumTestDistance"
#define OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_QPARAMS_TAG "MATCHER_applyMinimumTestDistance"
#define OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_TYPE        OPENCV_KPM_TAG_BOOL
#define OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_DEFAULT     "1"

#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_TAG              "minimumTestDistance"
#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_QPARAMS_TAG      "MATCHER_minimumTestDistance"
#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_TYPE             OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_DEFAULT          "1.6"
#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_MIN              "0.0"
#define OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_MAX              "2.0"

#define OPENCV_KPM_FLANN_KDTREE_TREES_TAG                       "trees"
#define OPENCV_KPM_FLANN_KDTREE_TREES_QPARAMS_TAG               "FLANN-KDTREE_trees"
#define OPENCV_KPM_FLANN_KDTREE_TREES_TYPE                      OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_KDTREE_TREES_DEFAULT                   "4"
#define OPENCV_KPM_FLANN_KDTREE_TREES_MIN                       "1"
#define OPENCV_KPM_FLANN_KDTREE_TREES_MAX                       "16"

#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_TAG                   "branching"
#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_QPARAMS_TAG           "FLANN-KMEANS_branching"
#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_TYPE                  OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_DEFAULT               "32"
#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_MIN                   "10"
#define OPENCV_KPM_FLANN_KMEANS_BRANCHING_MAX                   "150"

#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_TAG                     "cbIndex"
#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_QPARAMS_TAG             "FLANN-KMEANS_cbIndex"
#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_TYPE                    OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_DEFAULT                 "0.20"
#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_MIN                     "0.0"
#define OPENCV_KPM_FLANN_KMEANS_CBINDEX_MAX                     "1000.0"

#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_TAG                 "centersInit(1:RANDOM,2:GONZALES,3:KMEANSPP)"
#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_QPARAMS_TAG         "FLANN-KMEANS_centersInit(1:RANDOM,2:GONZALES,3:KMEANSPP)"
#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_TYPE                OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_DEFAULT             "2"
#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_MIN                 "1"
#define OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_MAX                 "3"

#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_TAG                 "iterations"
#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_QPARAMS_TAG         "FLANN-KMEANS_iterations"
#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_TYPE                OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_DEFAULT             "11"
#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_MIN                 "-1"
#define OPENCV_KPM_FLANN_KMEANS_ITERATIONS_MAX                 "100"

#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_TAG               "branching"
#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_QPARAMS_TAG       "FLANN-COMPOSITE_branching"
#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_TYPE              OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_DEFAULT           "32"
#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_MIN               "10"
#define OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_MAX               "150"

#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_TAG                 "cbIndex"
#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_QPARAMS_TAG         "FLANN-COMPOSITE_cbIndex"
#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_TYPE                OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_DEFAULT             "0.20"
#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_MIN                 "0.0"
#define OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_MAX                 "1000.0"

#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_TAG             "centersInit(1:RANDOM,2:GONZALES,3:KMEANSPP)"
#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_QPARAMS_TAG     "FLANN-COMPOSITE_centersInit(1:RANDOM,2:GONZALES,3:KMEANSPP)"
#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_TYPE            OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_DEFAULT         "2"
#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_MIN             "1"
#define OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_MAX             "3"

#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_TAG              "iterations"
#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_QPARAMS_TAG      "FLANN-COMPOSITE_iterations"
#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_TYPE             OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_DEFAULT          "11"
#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_MIN              "-1"
#define OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_MAX              "100"

#define OPENCV_KPM_FLANN_COMPOSITE_TREES_TAG                   "trees"
#define OPENCV_KPM_FLANN_COMPOSITE_TREES_QPARAMS_TAG           "FLANN-COMPOSITE_trees"
#define OPENCV_KPM_FLANN_COMPOSITE_TREES_TYPE                  OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_COMPOSITE_TREES_DEFAULT               "4"
#define OPENCV_KPM_FLANN_COMPOSITE_TREES_MIN                   "1"
#define OPENCV_KPM_FLANN_COMPOSITE_TREES_MAX                   "16"

#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_TAG             "buildWeight"
#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_QPARAMS_TAG     "FLANN-AUTOTUNED_buildWeight"
#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_TYPE            OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_DEFAULT         "0.01"
#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_MIN             "0.00"
#define OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_MAX             "100.00"

#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_TAG             "memoryWeight"
#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_QPARAMS_TAG     "FLANN-AUTOTUNED_memoryWeight"
#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_TYPE            OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_DEFAULT         "0.00"
#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_MIN             "0.00"
#define OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_MAX             "100.00"

#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_TAG           "sampleFraction"
#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_QPARAMS_TAG   "FLANN-AUTOTUNED_sampleFraction"
#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_TYPE          OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_DEFAULT       "0.1"
#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_MIN           "0.0"
#define OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_MAX           "1.0"

#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_TAG          "targetPrecision"
#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_QPARAMS_TAG  "FLANN-AUTOTUNED_targetPrecision"
#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_TYPE         OPENCV_KPM_TAG_DOUBLE
#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_DEFAULT      "0.9"
#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_MIN          "0.0"
#define OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_MAX          "1.0"

#define OPENCV_KPM_FLANN_LSH_KEYSIZE_TAG                        "keySize"
#define OPENCV_KPM_FLANN_LSH_KEYSIZE_QPARAMS_TAG                "FLANN-LSH_keySize"
#define OPENCV_KPM_FLANN_LSH_KEYSIZE_TYPE                       OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_LSH_KEYSIZE_DEFAULT                    "20"
#define OPENCV_KPM_FLANN_LSH_KEYSIZE_MIN                        "10"
#define OPENCV_KPM_FLANN_LSH_KEYSIZE_MAX                        "28"

#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_TAG                "multiProbeLevel"
#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_QPARAMS_TAG        "FLANN-LSH_multiProbeLevel"
#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_TYPE               OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_DEFAULT            "2"
#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_MIN                "0"
#define OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_MAX                "2"

#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_TAG                    "tableNumber"
#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_QPARAMS_TAG            "FLANN-LSH_tableNumber"
#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_TYPE                   OPENCV_KPM_TAG_INT
#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_DEFAULT                "12"
#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_MIN                    "10"
#define OPENCV_KPM_FLANN_LSH_TABLENUMBER_MAX                    "30"


#endif // OPENCV_KPM_PARAMETERS_H
