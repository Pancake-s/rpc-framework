#pragma once
#include <google/protobuf/service.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <unordered_map>
#include <functional>

// Interface接口库，给外部使用的
class RpcProvider {
  public:
    // 发布rpc方法的接口
    void NotifyService(google::protobuf::Service *service);
    // 给一个基类google::protobuf::Service的指针，指向具体业务
    struct ServiceInfo {
      google::protobuf::Service *m_service;
      std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_method_map;
    };
    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
  private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventLoop;
    std::unordered_map<std::string, ServiceInfo> m_service_map;
    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    // 已连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*,
                      muduo::Timestamp);
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
};
