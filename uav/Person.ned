//
//
//
//




import inet.node.inet.AdhocHost;
import inet.routing.aodv.Aodv;
import inet.routing.dsdv.Dsdv;
import inet.routing.gpsr.Gpsr;

import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.aodv.AodvRouter;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;

import inet.node.inet.Router;
import inet.node.inet.WirelessHost;
import inet.node.inet.StandardHost;
import inet.node.inet.AdhocHost;
import inet.node.gpsr.GpsrRouter;
import inet.node.dymo.DymoRouter;
import inet.node.dsdv.DsdvRouter;

module Person extends GpsrRouter {
    parameters:
        @class(Person);
        @display("i=misc/drone");


        string modelURL;                          // 3D 모델 파일 (osg)
        double modelScale = default(20);
        string labelColor = default("#000000ff"); // 라벨 색상
        double timeStep @unit("s") = default(33ms); // 위치 갱신 간격
        double startTime @unit("s") = default(0s);  // 이동 시작 시간

        // 궤도 이동을 위한 파라미터들 ↓
        string orbitCenter;                       // 중심점: "x y"
        double radius @unit("m") = default(1000m);        // 궤도 반지름
        double altitude @unit("m") = default(1.5m);        // 모델 z 위치
        double startingPhase @unit("deg") = default(0deg); // 시작 각도
        double rotationPeriod @unit("s") = default(60s);   // 한 바퀴 도는 데 걸리는 시간
}







