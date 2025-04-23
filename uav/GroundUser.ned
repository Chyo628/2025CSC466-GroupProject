//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// Represents a satellite ground station at the given longitude/latitude.
//





import inet.node.inet.AdhocHost;
import inet.routing.aodv.Aodv;
import inet.routing.dsdv.Dsdv;
import inet.routing.gpsr.Gpsr;

import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;

import inet.node.aodv.AodvRouter;
import inet.node.inet.Router;
import inet.node.inet.WirelessHost;
import inet.node.inet.StandardHost;
import inet.node.inet.AdhocHost;
import inet.node.gpsr.GpsrRouter;
import inet.node.dymo.DymoRouter;
import inet.node.dsdv.DsdvRouter;



module GroundUser extends GpsrRouter {
    parameters:
        @class(GroundUser);                    		// C++ 클래스 지정
        @display("i=abstract/person");        // 아이콘

        string modelURL;                          // 3D 모델 파일 (osg, obj 등)
        double modelScale = default(20);          // 모델 크기 배율
        string orbitCenter;                       // 고정 위치: "x y"
        double altitude @unit("m") = default(1.5m); // 고도 (z 위치)
}




import inet.routing.aodv.Aodv;
import inet.node.aodv.AodvRouter;
