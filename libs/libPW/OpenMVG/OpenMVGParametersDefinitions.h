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
#ifndef OPENMVGPARAMETERSDEFINITIONS_H
#define OPENMVGPARAMETERSDEFINITIONS_H

#define OPENMVGPARAMETERSDEFINITIONS_TRUE                             "TRUE"
#define OPENMVGPARAMETERSDEFINITIONS_FALSE                            "FALSE"

#define OPENMVGPARAMETERSDEFINITIONS_MATCHES_PATH                     "KPM_EPIPOLAR"

#define OPENMVGPARAMETERSDEFINITIONS_FEATURES_FILE_EXTENSION          ".feat"
#define OPENMVGPARAMETERSDEFINITIONS_DESCRIPTORS_FILE_EXTENSION       ".desc"

#define OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_KEYPOINTS        "lists.txt"
#define OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_FOCAL_PRECISION    2

#define OPENMVGPARAMETERSDEFINITIONS_MATCHES_GEOMFILTER               "e"

#define OPENMVGPARAMETERSDEFINITIONS_NO_ERROR                         1
#define OPENMVGPARAMETERSDEFINITIONS_ERROR                            0

#define OPENMVGPARAMETERSDEFINITIONS_MODE_QPARAMS_TAG                "OPENMVG_KPM_MODE"
#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_QPARAMS_TAG    "OPENMVG_KPM_TIEPOINTSDENSITY"

#define OPENMVGPARAMETERSDEFINITIONS_MODE_ALL                        "All"
#define OPENMVGPARAMETERSDEFINITIONS_MODE_FILE                       "File"

#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW            "Low"
#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW_VALUE      0.04

#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH           "High"
#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH_VALUE     0.01

#define OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_PRECISION      2

#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_TAG_PAIR                         "pair"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_FIRST_IMAGE            "first"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_SECOND_IMAGE           "second"

#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_TAG_POINT                        "pnt"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_X1_COORDINATE          "x1"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_Y1_COORDINATE          "y1"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_X2_COORDINATE          "x2"
#define OPENMVG_KPM_PROGRAM_XMLMATCHESFILE_ATTRIBUTE_Y2_COORDINATE          "y2"

#endif // ASIFTPARAMETERSDEFINITIONS_H
