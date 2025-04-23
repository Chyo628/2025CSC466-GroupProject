#ifndef __GROUNDSTATION_H__
#define __GROUNDSTATION_H__

#include <omnetpp.h>

#ifdef WITH_OSG
#include <osg/PositionAttitudeTransform>

using namespace omnetpp;

class GroundStation : public cSimpleModule
{
  protected:
    osg::ref_ptr<osg::PositionAttitudeTransform> patNode = nullptr;
    std::string modelURL;
    double modelScale;
    double x, y, z;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return 2; }

  public:
    double getX() const { return x; }
    double getY() const { return y; }
};

#endif
#endif
