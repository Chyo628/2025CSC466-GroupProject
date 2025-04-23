// RgrRouter.cc
#include "RgrRouter.h"
#include "inet/routing/aodv/AodvControlPackets_m.h"
#include "inet/common/INETUtils.h"
namespace inet {
namespace routing {

class RgrRouter : public AodvRouter
{
  protected:
    // 기존에 IMobility* mobility 대신 getCurrentPosition() 함수 사용
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    // RGR 특화 RREQ 처리 함수
    void handleRGRRREQ(AodvControlPacket *ctrlPkt);

    // 데모용: 목적지 주소에 따른 좌표를 반환 (실제 환경에서는 별도 관리 필요)
    Coord getDestinationCoord(const L3Address &destAddr);

    // 노드의 현재 위치를 반환하는 헬퍼 함수 (모빌리티 모듈을 사용하지 않을 경우 모듈 파라미터에서 읽어옴)
    Coord getCurrentPosition() const;
};

Define_Module(RgrRouter);

void RgrRouter::initialize(int stage)
{
    AodvRouter::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        EV << "RGR 라우터 초기화 시작" << endl;
        // 더 이상 mobility 서브모듈을 사용하지 않고, getCurrentPosition()에서 파라미터로부터 위치 정보를 얻음.
    }
}

Coord RgrRouter::getCurrentPosition() const
{
    // 현재 노드를 가져옴
    cModule *node = getContainingNode(this);
    // 만약 노드에 "x", "y", "altitude" 파라미터가 있다면 해당 값을 사용
    if (node->hasPar("x") && node->hasPar("y") && node->hasPar("altitude"))
        return Coord(node->par("x").doubleValue(), node->par("y").doubleValue(), node->par("altitude").doubleValue());
    else {
        // 만약 파라미터가 없으면 기본값(0,0,0)을 반환
        return Coord(0, 0, 0);
    }
}

Coord RgrRouter::getDestinationCoord(const L3Address &destAddr)
{
    // 데모용: destAddr가 "10.0.0.1"이면 목적지 좌표를 (1000, 1000, 0)으로 설정, 그 외에는 (0,0,0) 반환
    if (destAddr == L3Address("10.0.0.1"))
        return Coord(1000, 1000, 0);
    else
        return Coord(0, 0, 0);
}

void RgrRouter::handleRGRRREQ(AodvControlPacket *ctrlPkt)
{
    // 현재 노드의 위치 정보는 getCurrentPosition() 함수를 통해 얻음
    Coord currentPos = getCurrentPosition();
    Coord destCoord = getDestinationCoord(ctrlPkt->getDestAddr());
    double currentDistance = currentPos.distance(destCoord);

    // 첫 번째 RREQ: hopCount가 0이면 현재 거리를 TTL 필드에 저장
    if (ctrlPkt->getHopCount() == 0) {
        ctrlPkt->setTtl(currentDistance);
        EV << "RGR: 초기 minDistance를 " << currentDistance << "로 설정" << endl;
    }
    else {
        double prevMinDistance = ctrlPkt->getTtl(); // 이전 minDistance
        // 현재 노드의 목적지까지 거리가 이전보다 작을 경우에만 패킷 전파
        if (currentDistance < prevMinDistance) {
            ctrlPkt->setTtl(currentDistance); // 갱신
            EV << "RGR: Greedy 포워딩, minDistance 갱신: " << currentDistance << endl;
        }
        else {
            EV << "RGR: RREQ 폐기 (현재 거리 " << currentDistance << " >= 이전 minDistance " << prevMinDistance << ")" << endl;
            delete ctrlPkt;
            return;
        }
    }
    // 결정 후, 기본 AODV 처리를 호출하여 패킷 전파
    AodvRouter::handleMessage(ctrlPkt);
}

void RgrRouter::handleMessage(cMessage *msg)
{
    // AODV 제어 패킷인지 확인
    AodvControlPacket *ctrlPkt = dynamic_cast<AodvControlPacket *>(msg);
    if (ctrlPkt && ctrlPkt->getType() == AODV_RREQ) {
        EV << "RGR: RREQ 수신, 목적지=" << ctrlPkt->getDestAddr() << endl;
        handleRGRRREQ(ctrlPkt);
    }
    else {
        // 다른 패킷은 기본 AODV 라우터 처리
        AodvRouter::handleMessage(msg);
    }
}

} // namespace routing
} // namespace inet
