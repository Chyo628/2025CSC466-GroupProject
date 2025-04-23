#include "ChannelController.h"

#ifdef WITH_OSG

#include <osgEarthUtil/LinearLineOfSight>
#include <osgUtil/UpdateVisitor>
#include <osg/ValueObject>
#include <osg/LineWidth>
#include <osg/Depth>

using namespace omnetpp;
using namespace osgEarth;
using namespace osgEarth::Annotation;

Define_Module(ChannelController);

ChannelController *ChannelController::instance = nullptr;

template<typename T>
bool contains(const std::vector<T>& vector, T item) {
    return std::find(vector.begin(), vector.end(), item) != vector.end();
}

osg::Vec4 ChannelController::parseColorString(const std::string& s)
{
    unsigned int r, g, b, a;
    if (s.size() == 9 && s[0] == '#') {
        sscanf(s.c_str() + 1, "%2x%2x%2x%2x", &r, &g, &b, &a);
        return osg::Vec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
    }
    return osg::Vec4(1.0, 1.0, 1.0, 1.0); // fallback: white opaque
}

ChannelController::ChannelController()
{
    if (instance)
        throw cRuntimeError("Only one ChannelController instance allowed");
    instance = this;
}

ChannelController::~ChannelController()
{
    instance = nullptr;
}

ChannelController *ChannelController::getInstance()
{
    if (!instance)
        throw cRuntimeError("ChannelController::getInstance(): no instance in network");
    return instance;
}

void ChannelController::initialize(int stage)
{
    switch (stage) {
    case 0:
        personToPersonColor = par("personToPersonColor").stringValue();
        personToGroundColor = par("personToGroundColor").stringValue();
        personToPersonWidth = par("personToPersonWidth").doubleValue();
        personToGroundWidth = par("personToGroundWidth").doubleValue();
        maxPersonToPersonDistance = par("maxPersonToPersonDistance").doubleValue();
        maxPersonToGroundDistance = par("maxPersonToGroundDistance").doubleValue();
        break;
    case 1:
        scene = OsgScene::getInstance()->getScene()->asGroup();
        connections = new osg::Geode();
        scene->addChild(connections);
        break;
    case 2:
        for (int i = 0; i < (int)persons.size(); ++i) {
            for (int j = i + 1; j < (int)persons.size(); ++j)
                addLineOfSight(persons[i]->getLocatorNode(), persons[j]->getLocatorNode(), 0);
            for (int j = 0; j < (int)stations.size(); ++j)
                addLineOfSight(persons[i]->getLocatorNode(), stations[j]->getLocatorNode(), 1);

        }
        break;
    }
}

void ChannelController::addPerson(Person *p)
{
    ASSERT(!contains(persons, p));
    ASSERT(losNodes.empty());
    persons.push_back(p);
}

void ChannelController::addGroundStation(GroundStation *p)
{
    ASSERT(!contains(stations, p));
    ASSERT(losNodes.empty());
    stations.push_back(p);
}

void ChannelController::addLineOfSight(osg::Node *a, osg::Node *b, int type)
{
    auto mapNode = osgEarth::MapNode::findMapNode(scene);
    auto los = new osgEarth::Util::LinearLineOfSightNode(mapNode);
    losNodes.push_back(los);

    los->setGoodColor(osg::Vec4(0, 0, 0, 0));
    los->setBadColor(osg::Vec4(0, 0, 0, 0));

    auto stateSet = los->getOrCreateStateSet();
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    auto depth = new osg::Depth;
    depth->setWriteMask(false);
    stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

    los->setUserValue("type", type);
    los->setUpdateCallback(new osgEarth::Util::LineOfSightTether(a, b));
    los->setTerrainOnly(true);
    scene->addChild(los);
}

void ChannelController::refreshDisplay() const
{
    osgUtil::UpdateVisitor updateVisitor;
    scene->traverse(updateVisitor);
    connections->removeDrawables(0, connections->getNumDrawables());

    for (auto losNode : losNodes) {
        if (losNode->getHasLOS()) {
            auto start = losNode->getStartWorld();
            auto end = losNode->getEndWorld();

            EV << "PatNode start pos: " << a->asTransform()->asPositionAttitudeTransform()->getPosition().x() << "\n";


//            EV << "LOS line: start=(" << start.x() << ", " << start.y() << ", " << start.z()
//               << ") end=(" << end.x() << ", " << end.y() << ", " << end.z() << ")\n";

            double distance = (start - end).length();

            int type;
            losNode->getUserValue("type", type);

            bool withinRange = true;
            switch (type) {
            case 0:
                withinRange = distance <= maxPersonToPersonDistance;
                if (withinRange && !personToPersonColor.empty())
                    connections->addDrawable(
                        createLineBetweenPoints(start, end, personToPersonWidth, parseColorString(personToPersonColor)));
                break;
            case 1:
                withinRange = distance <= maxPersonToGroundDistance;
                if (withinRange && !personToGroundColor.empty())
                    connections->addDrawable(
                        createLineBetweenPoints(start, end, personToGroundWidth, parseColorString(personToGroundColor)));
                break;
            }
        }
    }
}

osg::ref_ptr<osg::Drawable> ChannelController::createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color)
{
    osg::ref_ptr<osg::Geometry> lineGeom = new osg::Geometry;
    osg::ref_ptr<osg::DrawArrays> drawArray = new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP);
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;

    vertices->push_back(start);
    vertices->push_back(end);
    lineGeom->addPrimitiveSet(drawArray);
    lineGeom->setVertexArray(vertices);
    drawArray->setFirst(0);
    drawArray->setCount(vertices->size());

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(color);
    lineGeom->setColorArray(colors, osg::Array::BIND_OVERALL);

    auto stateSet = lineGeom->getOrCreateStateSet();
    stateSet->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON);
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    auto depth = new osg::Depth;
    depth->setWriteMask(false);
    stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

    return lineGeom;
}

void ChannelController::handleMessage(cMessage *msg)
{
    throw cRuntimeError("This module does not process messages");
}

#endif // WITH_OSG
