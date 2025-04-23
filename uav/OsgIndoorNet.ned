//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// The OpenSceneGraph indoor demo.
//


import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;

//import inet.node.aodv.AodvRouter;
//import inet.node.gpsr.GpsrRouter;
//import inet.node.dymo.DymoRouter;
import inet.node.dsdv.DsdvRouter;
import inet.routing.dsdv.Dsdv;
import inet.routing.gpsr.Gpsr;



network OsgIndoorNet
{
    parameters:
        @display("bgb=388,298");
        double playgroundWidth = default(300);
        double playgroundHeight = default(150);
        int numPeople = default(0);
        int numGS = default(0);
        int numUser = default(0);

    submodules:
        osgScene: OsgScene {
            @display("p=37,30");
        }
        man[numPeople]: Person {
            @display("p=144,224");
        }

        gs[numGS]: GroundStation {
            @display("p=240,223");
        }

        user[numUser]: GroundUser {
            @display("p=324,225");
        }

        radioMedium: UnitDiskRadioMedium {
            @display("p=44,167");
        }

        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='145.236.x.x' netmask='255.255.0.0'/></config>");
                @display("p=44,101;is=s");
        }
        routingTableRecorder: RoutingTableRecorder {
            parameters:
                @display("p=44,231;is=s");
        }

        scenarioManager: ScenarioManager {
            parameters:
                script = default(xml("<scenario/>"));
                @display("p=106,30;is=s");
        }

    connections allowunconnected:


}
