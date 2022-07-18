#pragma once
#include "google/protobuf/service.h"

// Interface接口库，给外部使用的
class RpcProvider {
  public:
    // 发布rpc方法的接口
    void NotifyService(google::protobuf::Service *service);
    // 给一个基类google::protobuf::Service的指针，指向具体业务

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
};
