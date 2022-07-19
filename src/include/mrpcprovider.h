#pragma once
#include <google/protobuf/service.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <functional>

// Interface接口库，给外部使用的
class RpcProvider {
  public:
    // 发布rpc方法的接口
    void NotifyService(google::protobuf::Service *service);
    // 给一个基类google::protobuf::Service的指针，指向具体业务

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
  private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventLoop;
    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    // 已连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*,
                      muduo::Timestamp);
};
