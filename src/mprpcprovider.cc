#include "mrpcprovider.h"
#include "mprpcapplication.h"
#include <string>
#include <iostream>
using google::protobuf::Service;

void RpcProvider::NotifyService(Service *service) {
  
}

void RpcProvider::Run() {
  std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
  uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
  muduo::net::InetAddress address(ip, port);

  muduo::net::TcpServer server(&m_eventLoop, address, "RpcProvider");

  server.setConnectionCallback(std::bind(&RpcProvider::OnConnection, this, std::placeholders::_1));
  server.setMessageCallback(std::bind(&RpcProvider::OnMessage, this,
    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

  server.setThreadNum(4); // 1 for I/O, 3 for working threads

  std::cout << "RpcProvider start service at ip: " << ip << " port: " << port << std::endl;

  server.start();
  m_eventLoop.loop(); // epoll_wait, wait for connections
}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn) {

}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &conn,
  muduo::net::Buffer *buffer, muduo::Timestamp) {

}