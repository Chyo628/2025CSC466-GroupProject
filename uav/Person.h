////
//// This file is part of an OMNeT++/OMNEST simulation example.
////
//// Copyright (C) 2015 OpenSim Ltd.
////
//// This file is distributed WITHOUT ANY WARRANTY. See the file
//// license' for details on this and other legal matters.
////
//
//#ifndef __PERSON_H__
//#define __PERSON_H__
//
//#include <omnetpp.h>
//
//#ifdef WITH_OSG
//
//#include <osg/PositionAttitudeTransform>
//
//using namespace omnetpp;
//
//struct Waypoint
//{
//    Waypoint(double x, double y) {
//        this->x = x;
//        this->y = y;
//    }
//    double x;
//    double y;
//};
//typedef std::vector<Waypoint> WaypointVector;
//
///**
// * A mobile node (with a 3D model) moving around.
// */
//class Person : public cSimpleModule
//{
//  protected:
//    // configuration
//    WaypointVector waypoints;
//
//    double speed;
//    double  wayponitProximity;
//    double angularSpeed;
//    int targetPointIndex;
//
//
//
//    // configuration
//    double timeStep;
//    std::string labelColor;
//    std::string modelURL;
//
//    // OSG node for 3D visualization
//    osg::ref_ptr<osg::PositionAttitudeTransform> patNode = nullptr;
//
//    // node position and heading (speed is constant in this model)
//    double heading;  // in degrees
//    double x, y;  // in meters, relative to playground origin
//
//  public:
//    double getX() { return x; }
//    double getY() { return y; }
//
//  protected:
//    virtual void initialize(int stage) override;
//    virtual int numInitStages() const override { return 2; }
//    virtual void handleMessage(cMessage *msg) override;
//    virtual void refreshDisplay() const override;
//    virtual void move();
//    void readWaypointsFromFile(const char *fileName);
//};
//
//#endif
//#endif




#ifndef __PERSON_H__
#define __PERSON_H__

#include <omnetpp.h>

#ifdef WITH_OSG

#include <osg/PositionAttitudeTransform>




using namespace omnetpp;

class Person : public cSimpleModule
{
  protected:
    // 궤도 이동 파라미터
    cFigure::Point orbitCenter;
    double radius;
    double altitude;
    double startingPhase;
    double rotationPeriod;
    simtime_t lastPositionUpdateTime;
    double modelScale;

    // 시각화
    osg::ref_ptr<osg::PositionAttitudeTransform> patNode = nullptr;
    //osg::ref_ptr<osgEarth::GeoTransform> geoTransform;

    std::string modelURL;

    std::string labelColor;

    double heading;
    double x, y;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return 2; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void refreshDisplay() const override;

  public:
    double getX() { return x; }
    double getY() { return y; }
};

#endif
#endif

