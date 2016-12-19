#include "ccviewerwrapper.h"
#include <QMessageBox>
#include "ccGLUtils.h"
ccViewerWrapper::ccViewerWrapper()
    : m_orderedLabelsContainer(0)
{
    //for points picking
    m_label = new cc2DLabel();
    m_label->setSelected(true);

    //for 2D zone picking
    m_rect2DLabel = new cc2DViewportLabel();
    m_rect2DLabel->setVisible(false);	//=invalid
    m_rect2DLabel->setSelected(true);	//=closed
}

ccViewerWrapper::~ccViewerWrapper(){
    if (m_label)
        delete m_label;
    m_label=0;

    if (m_rect2DLabel)
        delete m_rect2DLabel;
    m_rect2DLabel=0;
}

ccGLWindow * ccViewerWrapper::getGLWindow()
{
    return m_glWindow;
}

QMenu * ccViewerWrapper::getOptionsMenu()
{
    for (int i = 0; i<menuBar()->actions().count(); i++)
        if (menuBar()->actions().at(i)->text().compare(QString("Display parameters")))
            return menuBar()->actions().at(i)->menu();
    return NULL;
}

void ccViewerWrapper::activateDistanceDisplay(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = POINT_POINT_DISTANCE;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    m_label->setVisible(true);
    m_label->setSelected(true);

    m_rect2DLabel->setVisible(false);
    m_rect2DLabel->setSelected(true);
    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
}

void ccViewerWrapper::activateTriangleDisplay(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = POINTS_ANGLE;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    m_label->setVisible(true);
    m_label->setSelected(true);

    m_rect2DLabel->setVisible(false);
    m_rect2DLabel->setSelected(true);
    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
}

void ccViewerWrapper::activatePointDisplay(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = POINT_INFO;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    m_label->setVisible(true);
    m_label->setSelected(true);

    m_rect2DLabel->setVisible(false);
    m_rect2DLabel->setSelected(true);
    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
}

void ccViewerWrapper::activatePointListDisplay(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = POINT_LIST;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));

}

void ccViewerWrapper::activateCenterPickingDisplay(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = PICKING_ROTATION_CENTER;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    m_label->setVisible(true);
    m_label->setSelected(true);

    m_rect2DLabel->setVisible(false);
    m_rect2DLabel->setSelected(true);
    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
}

void ccViewerWrapper::clearLables()
{
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    m_label->clear();
    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
//    if(m_orderedLabelsContainer)
//        m_orderedLabelsContainer->removeAllChildren();
    getGLWindow()->redraw();
}

void ccViewerWrapper::processPickedPoint(int cloudID, uint pointIndex, int x, int y)
{
    ccGLWindow * associatedWin = getGLWindow();

    assert(m_label);
    assert(associatedWin);

    ccPointCloud* cloud = 0;

    ccHObject* obj = associatedWin->getSceneDB()->getFirstChild();
    if (obj->isKindOf(CC_POINT_CLOUD))
        cloud = static_cast<ccPointCloud*>(obj);

    if (!cloud)
    {
        return;
    }

    CCVector3 pickedPoint = *cloud->getPoint(pointIndex);
    ccGenericGLDisplay* display = cloud->getDisplay();
    const ccViewportParameters& params = display->getViewportParameters();
    CCVector3 dP = params.pivotPoint - pickedPoint;
    CCVector3 MdP = dP; params.viewMat.applyRotation(MdP);
    CCVector3 newCameraPos = params.cameraCenter + MdP - dP;


    switch(m_pickingMode)
    {
    case POINT_INFO:
        m_label->clear();
        break;
    case PICKING_ROTATION_CENTER:
        obj->getGLTransformation().apply(pickedPoint);
        getGLWindow()->setCameraPos(newCameraPos);
        getGLWindow()->setPivotPoint(pickedPoint);
        return;
    case POINT_POINT_DISTANCE:
        if (m_label->size() >= 2)
            m_label->clear();
        break;
    case PICKING_DISTANCE_TO_SCALE:
        if (m_label->size() >= 2)
            m_label->clear();
        break;
    case POINTS_ANGLE:
        if (m_label->size() >= 3)
            m_label->clear();
        break;
    case RECT_ZONE:
        return; //we don't use this slot for 2D mode
    case POINT_LIST:
        cc2DLabel* newLabel = new cc2DLabel();
        ccGenericGLDisplay* display = cloud->getDisplay();
        newLabel->setDisplay(display);
        newLabel->addPoint(cloud,pointIndex);
        newLabel->setVisible(true);
        newLabel->setDisplayedIn2D(false);
        newLabel->setCollapsed(true);
        newLabel->setName("lolailo");
        if (display)
        {
            int vp[4];
            display->getViewportArray(vp);
            newLabel->setPosition((float)(x+20)/(float)(vp[2]-vp[0]),(float)(y+20)/(float)(vp[3]-vp[1]));
        }
        if (!m_orderedLabelsContainer)
        {
            m_orderedLabelsContainer = new ccHObject();
            cloud->addChild(m_orderedLabelsContainer,true);
            getGLWindow()->addToOwnDB(m_orderedLabelsContainer); //***********************************
        }
        newLabel->setName("P"+QString::number(m_orderedLabelsContainer->getChildrenNumber()+1));
        assert(m_orderedLabelsContainer);
        m_orderedLabelsContainer->addChild(newLabel,true);
        getGLWindow()->addToOwnDB(newLabel); //***********************************
        if (associatedWin)
            associatedWin->redraw();
        return;
    }



    m_label->addPoint(cloud,pointIndex);
    m_label->setVisible(true);
    if (m_label->size()==1 && associatedWin)
        m_label->setPosition((float)(x+20)/(float)associatedWin->width(),(float)(y+20)/(float)associatedWin->height());

    if (m_pickingMode ==PICKING_DISTANCE_TO_SCALE && m_label->size() == 2){
        foreach (QString item, m_label->getLabelContent(ccGui::Parameters().displayedNumPrecision)) {
            if (item.contains("Distance")) {
                mDistanceToScale = item.split("Distance = ").at(1).toFloat();
                m_label->clear();
                emit distanceAvailable();
            }
        }
    }
    //output info to Console
//    QStringList body = m_label->getLabelContent(ccGui::Parameters().displayedNumPrecision);
//    ccLog::Print(QString("[Picked] ")+m_label->getName());
//    for (int i=0;i<body.size();++i)
//        ccLog::Print(QString("[Picked]\t- ")+body[i]);

    if (associatedWin)
        associatedWin->redraw();
}

QList<unsigned> ccViewerWrapper::getPickedPointsList(){
    QList<unsigned> indexes;
    if(m_orderedLabelsContainer)
        for (int i = 0; i<m_orderedLabelsContainer->getChildrenNumber(); i++){
            cc2DLabel* label = (cc2DLabel*)m_orderedLabelsContainer->getChild(i);
            indexes.append( label->getPoint(0).index);
        }
    return indexes;
}

void ccViewerWrapper::activateGetDistanceToScale(){
    disconnect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));
    getGLWindow()->setPickingMode(ccGLWindow::POINT_PICKING);

    m_pickingMode = PICKING_DISTANCE_TO_SCALE;

    m_label->clear();

    getGLWindow()->removeFromOwnDB(m_label);
    getGLWindow()->removeFromOwnDB(m_rect2DLabel);
    getGLWindow()->addToOwnDB(m_label);
    getGLWindow()->addToOwnDB(m_rect2DLabel);

    m_label->setVisible(true);
    m_label->setSelected(true);

    m_rect2DLabel->setVisible(false);
    m_rect2DLabel->setSelected(true);
    getGLWindow()->redraw();
    if (getGLWindow())
    {
        getGLWindow()->setInteractionMode(ccGLWindow::TRANSFORM_CAMERA);
        getGLWindow()->updateGL();
    }
    connect(getGLWindow(), SIGNAL(pointPicked(int,uint,int,int)), this, SLOT(processPickedPoint(int, uint, int, int)));

}

float ccViewerWrapper::getDistToScale(){
    return mDistanceToScale;
}

void ccViewerWrapper::viewToTop(){
    ccGLWindow* win = getGLWindow();
    if (win)
        win->setView(CC_TOP_VIEW);
}
