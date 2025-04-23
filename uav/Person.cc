#include "Person.h"

#ifdef WITH_OSG

#include "omnetpp/osgutil.h"
#include <osgDB/ReadFile>
#include "OsgScene.h"


#include <osg/Vec4>
#include <osg/Geometry>



#include <osgEarthUtil/LinearLineOfSight>
#include <osgUtil/UpdateVisitor>
#include <osg/ValueObject>
#include <osg/LineWidth>
#include <osg/Depth>
#include <osgText/Text>  // 추가
#include <osg/Geode>     // 추가



using namespace osgEarth;
using namespace osgEarth::Annotation;


using namespace omnetpp;



Define_Module(Person);


void Person::initialize(int stage)
{
    switch (stage) {
    case 0: {
        WATCH(x);
        WATCH(y);

        std::stringstream ss(par("orbitCenter").stringValue());
        double cx, cy;
        ss >> cx >> cy;
        orbitCenter = cFigure::Point(cx, cy);
        radius = par("radius").doubleValue();
        altitude = par("altitude").doubleValue();
        startingPhase = par("startingPhase").doubleValueInUnit("deg") * M_PI / 180.0;
        rotationPeriod = par("rotationPeriod").doubleValue();

        modelURL = par("modelURL").stringValue();
        modelScale = par("modelScale").doubleValue();  // 추가
        //labelColor = par("labelColor").stringValue();


        lastPositionUpdateTime = -1;
        heading = 0;
        break;
    }

    case 1: {
        auto scene = OsgScene::getInstance()->getScene();

        auto modelNode = osgDB::readNodeFile(modelURL);
        if (!modelNode)
            throw cRuntimeError("Model file \"%s\" not found or format is not recognized", modelURL.c_str());

        auto objectNode = new cObjectOsgNode(this);
        objectNode->addChild(modelNode);

        patNode = new osg::PositionAttitudeTransform();
        patNode->setScale(osg::Vec3d(modelScale, modelScale, modelScale));  // 추가
        patNode->addChild(objectNode);

        ((osg::Group *)scene)->addChild(patNode);

        std::string orbitColor = par("labelColor").stringValue(); // 궤적 색상을 labelColor 재활용

        if (!orbitColor.empty()) {
            osg::ref_ptr<osg::Geometry> orbitGeom = new osg::Geometry;
            osg::ref_ptr<osg::DrawArrays> drawArrayLines = new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP);
            osg::ref_ptr<osg::Vec3Array> vertexData = new osg::Vec3Array;

            for (int i = 0; i <= 100; ++i) {
                double angle = i / 100.0 * 2 * M_PI;
                double x = orbitCenter.x + std::cos(angle) * radius;
                double y = orbitCenter.y + std::sin(angle) * radius;
                double z = altitude;
                vertexData->push_back(osg::Vec3(x, y, z));
            }

            orbitGeom->addPrimitiveSet(drawArrayLines);
            orbitGeom->setVertexArray(vertexData);
            drawArrayLines->setFirst(0);
            drawArrayLines->setCount(vertexData->size());

            osg::ref_ptr<osg::Vec4Array> colorData = new osg::Vec4Array;
            colorData->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));  // RGBA 노란색
            orbitGeom->setColorArray(colorData, osg::Array::BIND_OVERALL);

            auto stateSet = orbitGeom->getOrCreateStateSet();
            stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
            stateSet->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
            stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
            stateSet->setAttributeAndModes(new osg::LineWidth(1.5), osg::StateAttribute::ON);

            osg::ref_ptr<osg::Geode> orbitGeode = new osg::Geode;
            orbitGeode->addDrawable(orbitGeom);
            ((osg::Group*)scene)->addChild(orbitGeode);
        }

        scheduleAt(simTime(), new cMessage("move"));
        break;
    }
    }
}




void Person::handleMessage(cMessage *msg)
{
    simtime_t t = simTime();
    if (t != lastPositionUpdateTime) {
        double angle = startingPhase + (t.dbl() / rotationPeriod) * 2 * M_PI;
        x = orbitCenter.x + std::cos(angle) * radius;
        y = orbitCenter.y + std::sin(angle) * radius;
        lastPositionUpdateTime = t;
    }

    scheduleAt(simTime() + 0.1, msg);  // 주기적 갱신
    refreshDisplay();
}

void Person::refreshDisplay() const
{
    double modelheading = fmod((360 + 90 + heading), 360) - 180;
    patNode->setPosition(osg::Vec3d(x, y, altitude));
    patNode->setAttitude(osg::Quat(modelheading / 180.0 * M_PI, osg::Vec3d(0, 0, 1)));

    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);
}




#endif // WITH_OSG
