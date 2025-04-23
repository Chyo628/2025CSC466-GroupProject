//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// This module is responsible for tracking the distances of mobile nodes,
// and visualizing the connectivity graph via osgEarth.
//


import inet.node.aodv.AodvRouter;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;



simple ChannelController
{
    @display("i=block/network2");

    // 색상과 선 굵기 설정
    string personToPersonColor = default("#00FF00BF");   // 초록색 반투명
    double personToPersonWidth = default(20);

    string personToGroundColor = default("#FFBF00BF");   // 주황색 반투명
    double personToGroundWidth = default(20);

    // 거리 임계값 설정
    double maxPersonToPersonDistance = default(1000);     // meter
    double maxPersonToGroundDistance = default(5000);     // meter
}
