#include "GroundStation.h"

#ifdef WITH_OSG

#include "omnetpp/osgutil.h"
#include <osgDB/ReadFile>
#include "OsgScene.h"

using namespace omnetpp;

Define_Module(GroundStation);

void GroundStation::initialize(int stage)
{
    if (stage == 0) {
        std::stringstream ss(par("orbitCenter").stringValue());  // 위치: "x y"
        ss >> x >> y;
        z = par("altitude").doubleValue();
        modelURL = par("modelURL").stringValue();
        modelScale = par("modelScale").doubleValue();
    }
    else if (stage == 1) {
        auto scene = OsgScene::getInstance()->getScene();

        auto modelNode = osgDB::readNodeFile(modelURL);
        if (!modelNode)
            throw cRuntimeError("Model file \"%s\" not found or format is not recognized", modelURL.c_str());

        auto objectNode = new cObjectOsgNode(this);
        objectNode->addChild(modelNode);

        patNode = new osg::PositionAttitudeTransform();
        patNode->setScale(osg::Vec3d(modelScale, modelScale, modelScale));
        patNode->addChild(objectNode);
        patNode->setPosition(osg::Vec3d(x, y, z));

        ((osg::Group *)scene)->addChild(patNode);

        // 2D canvas 위치도 설정
        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);
    }
}

#endif // WITH_OSG
