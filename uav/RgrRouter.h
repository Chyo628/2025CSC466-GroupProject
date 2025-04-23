#ifndef __INET_RGRROUTER_H
#define __INET_RGRROUTER_H

#include "inet/routing/aodv/Aodv.h"
#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/networklayer/contract/IL3Address.h"

namespace inet {
namespace routing {

/**
 * RgrRouter implements the RGR routing mechanism on top of AODV.
 * Instead of relying on a mobility submodule, it obtains the node's
 * current position from module parameters ("x", "y", "altitude").
 */
class RgrRouter : public AodvRouter
{
  protected:
    // RGR 특화 함수들
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    // RGR 특화 RREQ 처리 함수: 노드의 현재 위치와 목적지 좌표를 비교하여 그리디 포워딩 결정
    void handleRGRRREQ(AodvControlPacket *ctrlPkt);

    // 데모용: 목적지 주소에 따른 좌표를 반환 (실제 환경에서는 별도 관리 필요)
    Coord getDestinationCoord(const L3Address &destAddr);

    // 현재 노드의 위치를 반환하는 헬퍼 함수 (모빌리티 서브모듈을 사용하지 않고, 파라미터로부터 직접 읽음)
    Coord getCurrentPosition() const;

  public:
    RgrRouter() {}
    virtual ~RgrRouter() {}
};

} // namespace routing
} // namespace inet

#endif // __INET_RGRROUTER_H
