#ifndef __CHANNELCONTROLLER_H_
#define __CHANNELCONTROLLER_H_

#include <omnetpp.h>

#ifdef WITH_OSG

#include "OsgScene.h"
#include "Person.h"
#include "GroundStation.h"

#include <osg/Node>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/Vec4>
#include <osgEarth/MapNode>
#include <osgEarthUtil/LinearLineOfSight>

using namespace omnetpp;

class ChannelController : public cSimpleModule
{
  protected:
    static ChannelController *instance;

    std::vector<Person*> persons;
    std::vector<GroundStation*> stations;
    std::vector<osgEarth::Util::LinearLineOfSightNode *> losNodes;

    osg::ref_ptr<osg::Geode> connections = nullptr;
    osg::Group *scene = nullptr;

    // 시각화 설정
    std::string personToPersonColor;
    std::string personToGroundColor;
    double personToPersonWidth = 1.0;
    double personToGroundWidth = 1.0;
    double maxPersonToGroundDistance = 1000;
    double maxPersonToPersonDistance = 1000;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return 3; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void refreshDisplay() const override;

    void addLineOfSight(osg::Node *a, osg::Node *b, int type);
    static osg::ref_ptr<osg::Drawable> createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color);
    static osg::Vec4 parseColorString(const std::string& s);

  public:
    ChannelController();
    virtual ~ChannelController();
    static ChannelController *getInstance();

    void addPerson(Person *p);
    void addGroundStation(GroundStation *p);
};

#endif // WITH_OSG
#endif // __CHANNELCONTROLLER_H_
