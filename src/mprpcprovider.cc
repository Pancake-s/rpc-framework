#include "mrpcprovider.h"
#include "mprpcapplication.h"
#include "rpcheader.pb.h"
#include <string>
#include <iostream>
using google::protobuf::Service;

void RpcProvider::NotifyService(Service *service) {
  ServiceInfo service_info;

  const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();

  std::string service_name = pserviceDesc->name();

  size_t methodCnt = pserviceDesc->method_count();

  std::cout << "service_name:" << service_name << std::endl;

  for (size_t i = 0; i < methodCnt; ++i) {
    const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
    std::string method_name = pmethodDesc->name();
    service_info.m_method_map.insert({method_name, pmethodDesc}); //插入键值对到map中
    std::cout << "method: " << method_name << std::endl;         //打印
  }
  service_info.m_service = service;                  //记录服务对象
  m_service_map.insert({service_name, service_info}); //存储一下服务及其具体的描述
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
  if (!conn->connected()) {
    conn->shutdown(); //关闭文件描述符 
  }
}


void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &conn,
  muduo::net::Buffer *buffer, muduo::Timestamp) {
  std::string recv_buf = buffer->retrieveAllAsString();
  uint32_t header_length = 0;
  recv_buf.copy((char*)&header_length, 4, 0);
  
  std::string rpc_header_str = recv_buf.substr(4, header_length);

  mprpc::RpcHeader rpcHeader;
  std::string service_name;
  std::string method_name;
  uint32_t args_length;
  if (rpcHeader.ParseFromString(rpc_header_str)) {
    service_name = rpcHeader.service_name();
    method_name = rpcHeader.method_name();
    args_length = rpcHeader.args_length();
  } else {
    std::cout << "rpc_header_str:" << rpc_header_str << " parse error!" << std::endl;
    return;
  }
  
  std::string args_str = recv_buf.substr(4 + header_length, args_length);
  std::cout << "============================================" << std::endl;
  std::cout << "service_name: " << service_name << std::endl; 
  std::cout << "method_name: " << method_name << std::endl; 
  std::cout << "args_str: " << args_str << std::endl; 
  std::cout << "============================================" << std::endl;
    
  //获取service对象和method对象
  auto it = m_service_map.find(service_name);
  if (it == m_service_map.end()) {
    std::cout << "invalid service: " << service_name << std::endl;
    return;
  }

  auto mit = it->second.m_method_map.find(method_name);
  if (mit == it->second.m_method_map.end()) {
    std::cout << "invalid method " << method_name << std::endl;
    return;
  }
  // 获取 service 和 message 对象
  google::protobuf::Service *service = it->second.m_service;
  const google::protobuf::MethodDescriptor *method = mit->second;
  
  google::protobuf::Message *request = service->GetRequestPrototype(method).New();
  
  if (!request->ParseFromString(args_str)) {
    std::cout << "request parse failed, content:" << args_str << std::endl;
    return;
  }
  google::protobuf::Message *response = service->GetResponsePrototype(method).New();
  google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider, 
                                                                  const muduo::net::TcpConnectionPtr&, 
                                                                  google::protobuf::Message*>
                                                                  (this, 
                                                                  &RpcProvider::SendRpcResponse, 
                                                                  conn, response);
  service->CallMethod(method, nullptr, request, response, done);
}

void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message *response)
{
  std::string response_str;
  if (response->SerializeToString(&response_str)) {
    conn->send(response_str);
  } else {
    std::cout << "serialise response_str failed!" << std::endl; 
  }
  conn->shutdown(); //模拟http的短链接服务，由rpcprovider主动断开连接，给更多的rpc调用方提供服务
}
