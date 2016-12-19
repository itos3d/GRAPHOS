#ifndef CCVIEWERWRAPPER_H
#define CCVIEWERWRAPPER_H

#include <cc2DViewportLabel.h>
#include <cc2DLabel.h>
#include <ccPointCloud.h>

#include "cc/ccViewer/ccviewer.h"
#include "cc/qCC/ccGLWindow.h"

class ccViewerWrapper : public ccViewer
{
     Q_OBJECT

public:
    ccViewerWrapper();
    ~ccViewerWrapper();

    ccGLWindow *    getGLWindow();
    QMenu *         getOptionsMenu();
    void            activateDistanceDisplay();
    void            activateTriangleDisplay();
    void            activatePointDisplay();
    void            activatePointListDisplay();
    void            activateCenterPickingDisplay();
    void            clearLables();
    void            activateGetDistanceToScale();

    QList<unsigned> getPickedPointsList();
    float getDistToScale();
    void viewToTop();
signals:
    void distanceAvailable();
private slots:
    void processPickedPoint(int cloudID, uint pointIndex, int x, int y);

private:

    //! Picking mode
    enum Mode
    {
        POINT_INFO,
        POINT_POINT_DISTANCE,
        POINTS_ANGLE,
        RECT_ZONE,
        POINT_LIST,
        PICKING_ROTATION_CENTER,
        PICKING_DISTANCE_TO_SCALE
    };

//    //! View orientation
//    enum CC_VIEW_ORIENTATION {	CC_TOP_VIEW,	/**< Top view (eye: +Z) **/
//                                CC_BOTTOM_VIEW,	/**< Bottom view **/
//                                CC_FRONT_VIEW,	/**< Front view **/
//                                CC_BACK_VIEW,	/**< Back view **/
//                                CC_LEFT_VIEW,	/**< Left view **/
//                                CC_RIGHT_VIEW,	/**< Right view **/
//                                CC_ISO_VIEW_1,	/**< Isometric view 1: front, right and top **/
//                                CC_ISO_VIEW_2,	/**< Isometric view 2: back, left and top **/
//    };


    //! Current picking mode
    Mode m_pickingMode;

    //! Associated 3D label
    cc2DLabel* m_label;

    //! Associated 2D label
    cc2DViewportLabel* m_rect2DLabel;

    //! Point list picking
    ccHObject* m_orderedLabelsContainer;

    float mDistanceToScale;
};

#endif // CCVIEWERWRAPPER_H
