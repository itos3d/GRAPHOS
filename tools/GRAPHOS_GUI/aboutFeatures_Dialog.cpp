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
#include "aboutFeatures_Dialog.h"
#include "ui_aboutFeatures_Dialog.h"
#include <QVBoxLayout>
#include <QTextEdit>
aboutFeatures_Dialog::aboutFeatures_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutFeatures_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Feature extraction and matching info");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QTabWidget *tabWidget = new QTabWidget();

    //Tapioca tab
    QFrame *tapiocaFrame = new QFrame();
    QVBoxLayout *tapiocaFrameLayout = new QVBoxLayout();
    QTextEdit *tapiocaTextArea= new QTextEdit();
    tapiocaTextArea->setReadOnly(true);
    tapiocaTextArea->setText("<font size=\"4\">Tiepoint detection and matching on the basis of the sift++. It encloses three different computation approaches, which can be chosen by the user through the variable <strong>\"Search mode\"</strong>:"

                             "<br><strong>\"All\"</strong>: A brute force approach where all possible image pairs are evaluated."
                             "<br><strong>\"Line\"</strong>: For linear images acquisition, the search process could be optimized by the selection of only a subset of image pair candidates. It works under the assumption of the enter photos were acquired at regular interval."
                             "<br>    -\"Range\": For a given photo, number of consecutive photos (in on direction) that can have common tiepoints. It is defined symmetrically forward and backward. By default it is defined as 3 photos (so, 7 consecutive images could share tiepoints), however, it varies gf the capture process."

                             "<br><strong>\"MulScale\"</strong>: a multi-scale optimization to optimize significantly the computational costs for a large set of images. Firstly, the homologous points search is perform on a very low resolution (defined by default as 5% of the original resolution, but can be adjusted by the user with the variable \"Min scale\") version of the input images. Once it finishes, the homologous points search is repeat at a high resolution (set by the user with the variable \"Max scale\") only for pictures connected together by a minimum number of user configurable points (2 by default )."
                             "<br>    -\"Min scale\": Image size for that the first search (low resolution) is performed."
                             "<br>    -\"Max scale\": Image size for that the second search (high resolution) is performed on the basis of the results of the first pass."
                             "<br><strong>\"Minimum matches\"</strong>: Maximum number of keypoints per image. If the detector extract more than this threshold, only the n keypoints with the highest response are kept. It is establishes by the default a max number of 5000 keypoints. If it is set as 0, none is deleted."
                             "<br><strong>\"Downsample images\"</strong>: This Boolean variable de/activates the use of the original images in the feature extraction process. Since this process is time consuming, optimal results could be obtained more efficiently if a low resolution version of the image is analyzed."
                             "<br>    -\"Size\" : This variable, express in pixel units, the size of the downsampled images that would use for the keypoint extraction. The default value of 1500 pixels is used to format the large side of image to this value. This is a very important parameter to speed up the global process.</font>");

    tapiocaFrameLayout->addWidget(tapiocaTextArea);

    tapiocaFrame->setLayout(tapiocaFrameLayout);
    tabWidget->addTab(tapiocaFrame,"Tapioca");


    //ASIFT tab
    QFrame *ASIFTFrame = new QFrame();
    QVBoxLayout *ASIFTFrameLayout = new QVBoxLayout();
    QTextEdit *ASIFTTextArea= new QTextEdit();
    ASIFTTextArea->setReadOnly(true);
    ASIFTTextArea->setText("<font size=\"4\">The strength of the ASIFT algorithm is that it can cope with images displaying a high scale and rotation difference, common in oblique scenes. The result is an invariant algorithm that considers changes in scale, rotations and movements between images. Extracting features in the multiple affine transformations of the image. To improve the results, the process could be tuned-up by a few parameters:"
                           "<br><strong>\"Tilts\"</strong>: Number of the affine transformations to be done. The image is transformed to simulate the perspective distortion by changing the camera optical axis. These are carried out by latitude and longitude rotations. The t (tilt) variable controlled by the user is employed to set, firslty the longitude rotations; defined as 72º/t; and secondly the latitude rotation being t=1/cos(latitude), following the latitude sampling a geometric series  1,a,a2,...,an, where n is the power of 2. By default is set t=4, being an increase of time if the number of transformation is increased."
                           "<br><strong>\"Peak threshold\"</strong>: This is the minimum amount of contrast to accept a keypoint as valid. It filters peaks of the DoG scale space that are too small (in absolute value). The increase of this threshold will imply an elimination of more keypoints."
                           "<br><strong>\"Edge threshold\"</strong>: This is the edge rejection threshold filtering out edge-like features. It is computed on the basis of the Hessian of the DoG scale space, to obtain a score similar to the Harris function. This score (dimensionless) has a minimum value of 4 (curved peak) and increases as one of the eigenvalues grows and the other stays small.  So, the decrease of this threshold will entail an elimination of more keypoints. "
                           "<br><strong>\"Octaves\"</strong>: Set the number of octave of the DoG scale space. It depends of the images size since increasing the scale by an octave means doubling the size of the smoothing kernel, whose effect is roughly equivalent to halving the image resolution. It can be computed automatically to set the maximum number of possible octaves for the image size, or set by the user, as in GRAPHOS. The default value is 4."

                           "Other fixed variable related to the process is the \"Levels\" or number of levels per octave. Each octave is sampled at this given number of intermediate scales (default=3). Increasing this number might in principle return more refined keypoints, but in practice can make their selection unstable due to noise. By this reason it is hidden to the user."

                            "<br><strong>\"Downsample images\"</strong>: This Boolean variable de/activates the use of the original images in the feature extraction process. Since this process is time consuming, optimal results could be obtained more efficiently if a low resolution version of the image is analyzed."
                           "<br>    -\"Size\": This variable, express in pixel units, the size of the downsampled images that would use for the keypoint extraction. The default value of 1500 pixels is used to format the large side of image to this value. This is a very important parameter to speed up the global process."
                           "<br><strong>\"Set tiepoints limit\"</strong>: Maximum number of keypoints per image. If the detector extract more than this threshold, only the n keypoints with the highest response are kept. It is establishes by the default a max number of 5000 keypoints. If it is set as 0, none is deleted.</font>");

    ASIFTFrameLayout->addWidget(ASIFTTextArea);

    ASIFTFrame->setLayout(ASIFTFrameLayout);
    tabWidget->addTab(ASIFTFrame,"ASIFT");


    //MSD_SIFT tab
    QFrame *MSD_SIFTFrame = new QFrame();
    QVBoxLayout *MSD_SIFTFrameLayout = new QVBoxLayout();
    QTextEdit *MSD_SIFTTextArea= new QTextEdit();
    MSD_SIFTTextArea->setReadOnly(true);
    MSD_SIFTTextArea->setText("<font size=\"4\">MSD is an interest point detector stemming from the intuition that image patches which are highly dissimilar over a relatively  large  extent  of  their  surroundings  hold  the  property  of  being repeatable and distinctive. This concept of contextual self-dissimilarity reverses the key paradigm of recent successful techniques, which build upon the presence of similar (rather than dissimilar) patches. The  MSD  detector  is   fired  by  image  patches  that  look  very  dissimilar  from their surroundings, whatever the structure of such patches may be (e.g. corners, edges, blobs, textures..). Despite its simplicity, such an approach inherently conveys remarkable invariance to nuisances such as illumination changes, viewpoint variations and blur. The MSD approach generalizes straightforwardly to detect interest points in any kind of multi-channel images."
                              "Since MSD is only a detector, the tiepoints should be described to carry out the matching process. It was chosen the SIFT descriptor, which is the same employed for the ASIFT detector, being these variables the same."

                              "<br><strong>\"Patch radius\"</strong>: One of the key variables of the MSD detector, specifies the size of the patches under comparison. This variable defines the size of a square image region centered at pixel. By default it is set as 3 pixels."
                              "<br><strong>\"Search area radius\"</strong>: One of the key variables of the MSD detector, indicates the  size  of  the  area  from  which  the  patches  to  be  compared  are drawn. It establishes the spatial support of the saliency criterion. By increasing this variable, the operator moves gradually from a local toward a contextual or even global saliency criterion. The default value of the variable is 5 pixels. "
                              "<br><strong>\"NMS radius\"</strong>: To obtain a manageable and evenly distributed arrangements of points, it is applied a Non-Maxima Suppression (NMS) process for every point with saliency is greater that the threshold. For every point a search areas is established on the basis of the radius indicated by the user. "
                              "<br><strong>\"NMS scale radius\"</strong>: Is the search radius of the Non-Maxima Suppression to mark the evaluated point as a keypoint."
                              "<br><strong>\"Threshold Saliency\"</strong>: Saliency stands for the score which highlights corner-like interest points. The  patch's  saliency  is associated to  the  absence  of  similar patches  in  its  surroundings. Unlike others methods it is not aimed at detecting highly similar patches within the surroundings of a pixel, but instead at determining whether a pixel shows similar patches in its surroundings or not. The saliency  operator  is  characterized  by  two parameters: the size of the patches under comparison  and  the  size  of  the  area  from  which  the  patches  to  be  compared  are drawn. The saliency score is normalized by means of the number of pixels involved in the computation of the self-dissimilarity. According to the empirical research it is established as 250 units."
                              "<br><strong>\"KNN\"</strong>: Instead of finding the most similar patch among a set of candidates, which implies a 1-Nearest Neighbor (1-NN) search problem, MSD detector performs the search task as a  k-NN problem (with k>=1). A higher k yields generally improved repeatability at the expense of a higher computational cost. So, by default is established as 4 as a good trade-off between performance and speed."
                              "<br><strong>\"N scales\"</strong>: To fulfill the detector scale invariance and to associate a characteristic scale to extracted features, it is built simple image pyramid which comprises N levels. It starts from level 1 (original image resolution) and rescaling, at each level, the image of a factor f^N with respect to the base level. By default the variable is set as 18 scales."
                              "<br><strong>\"Scale factor\"</strong>: It is the scale factor for the image scaling in the image pyramid. It is set as default as 1,25."

                              "<br><strong>\"Downsample images\"</strong>: This Boolean variable de/activates the use of the original images in the feature extraction process. Since this process is time consuming, optimal results could be obtained more efficiently if a low resolution version of the image is analyzed. "
                              "<br>    -\"Size\": This variable, express in pixel units, the size of the downsampled images that would use for the keypoint extraction. The default value of 1500 pixels is used to format the large side of image to this value. This is a very important parameter to speed up the global process. "
                              "<br><strong>\"Set tiepoints limit\"</strong>: Maximum number of keypoints per image. If the detector extract more than this threshold, only the n keypoints with the highest response are kept. It is establishes by the default a max number of 5000 keypoints. If it is set as 0, none is deleted.</font>"
);

    MSD_SIFTFrameLayout->addWidget(MSD_SIFTTextArea);

    MSD_SIFTFrame->setLayout(MSD_SIFTFrameLayout);
    tabWidget->addTab(MSD_SIFTFrame,"MSD+SIFT");

    //RobustMatcher tab
    QFrame *RobustMatcherFrame = new QFrame();
    QVBoxLayout *RobustMatcherFrameLayout = new QVBoxLayout();
    QTextEdit *RobustMatcherTextArea= new QTextEdit();
    RobustMatcherTextArea->setReadOnly(true);
    RobustMatcherTextArea->setText("<font size=\"4\">Based on a brute force, its working is easy. It takes the descriptor of one feature in first set and is matched with all other features in second set using some distance calculation (simply sum the absolute value of differences between the descriptor elements ). In short, the feature with the smallest distance is the best candidate to be the right corresponding point. However, some additional filtering can be applied for part of the user to improve the results (see the following variables)."
                                   "<br><strong>\"Ratio\"</strong>: To verify the corresponding point candidate, an additional verification is carried out to accept it as best match. It is computed as the division between the score of the best feature match and the score of the second best feature match. If it is obtained a high distance ratio, the match could be ambiguous or incorrect. According to the Probability Distribution Function, a threshold >0.8 provides a good separation among correct and incorrect matches. Greater the ratio value, greater the amount of matched points."
                                   "<br><strong>\"Threshold  (K)\"</strong>: After the matches are refined by the ratio test, they will be filtered to discard the matches whose descriptor distance (between the two corresponding points) is lower than a threshold. This threshold is established as a percent value in the range [0, 1]. The computation is established as maximum descriptor distance (for the whole matches pairs) multiplied by K factor. The matches pairs whose distance is greater than that value are rejected. This is equivalent to sort all the matches in ascending order of their distances so that best matches (with low distance, or lower than 1-K) come to front. K=1 implies that not refinement is done (all matches are kept)"
                                   "<br><strong>\"Minimum matches\"</strong>: In the matching process it is possible the generation of many false matches, varying immensely from match to match. If the number of matches is very low, these false positives could diverge the solution greatly. So, to avoid their influence in the orientation process, an absolute value is set as threshold.</font>");

    RobustMatcherFrameLayout->addWidget(RobustMatcherTextArea);

    RobustMatcherFrame->setLayout(RobustMatcherFrameLayout);
    tabWidget->addTab(RobustMatcherFrame,"Robust Matcher");


    //FLANNMatcher tab
    QFrame *FLANNMatcherFrame = new QFrame();
    QVBoxLayout *FLANNMatcherFrameLayout = new QVBoxLayout();
    QTextEdit *FLANNMatcherTextArea= new QTextEdit();
    FLANNMatcherTextArea->setReadOnly(true);
    FLANNMatcherTextArea->setText("<font size=\"4\">FLANN stands for Fast Library for Approximate Nearest Neighbors. It contains a collection of algorithms optimized for fast nearest neighbor search in large datasets and for high dimensional features. It works more faster than the brute force approach for large datasets."
                                  "As internal parameters (fixed and hidden), as well as the search structure , it is set the number of times  the trees in the index should be recursively traversed. Higher values gives better precision, but also takes more time. The only parameter controlled by the user is the <strong>\"Minimum matches\"</strong>, which set the condition of at least n matches between the images to avoid wrong correspondences.</font>");

    FLANNMatcherFrameLayout->addWidget(FLANNMatcherTextArea);

    FLANNMatcherFrame->setLayout(FLANNMatcherFrameLayout);
    tabWidget->addTab(FLANNMatcherFrame,"FLANN Matcher");

    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    setFixedSize(1000,600);
}

aboutFeatures_Dialog::~aboutFeatures_Dialog()
{
    delete ui;
}
