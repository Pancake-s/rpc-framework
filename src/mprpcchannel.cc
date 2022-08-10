#include "mprpcchannel.h"
#include "rpcheader.pb.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#include "mprpcapplication.h"

void MprpcChannel::CallMethod(const MethodDescriptor* method,
  RpcController* controller, const Message* request,
  Message* response, Closure* done) {
  // 序列化method和args
  const google::protobuf::ServiceDescriptor *sd = method->service();
  std::string service_name = sd->name();
  std::string method_name = method->name();
  uint32_t args_length = 0;
  std::string args_str;
  if (request->SerializeToString(&args_str)) {
    args_length = args_str.size();
  } else {
    controller->SetFailed("serialise request failed");
    // std::cout << "serialise request failed" << std::endl;
  }
  // 加入rpcheader
  mprpc::RpcHeader rpc_header;
  rpc_header.set_service_name(service_name);
  rpc_header.set_method_name(method_name);
  rpc_header.set_args_length(args_length);
  uint32_t header_size = 0;
  std::string header_str;
  if (rpc_header.SerializeToString(&header_str)) {
    header_size = header_str.size();
  } else {
    // std::cout << "serialise rpc header failed" << std::endl;
    controller->SetFailed("serialise rpc header failed");
  }

  std::string send_rpc_str;
  send_rpc_str.insert(0, (char*)&header_size, 4);  //
  send_rpc_str += header_str;
  send_rpc_str += args_str;
  std::cout << "=================================" << std::endl;
  std::cout << "header_size: " << header_size << std::endl;
  std::cout << "header_str: " << header_str << std::endl; 
  std::cout << "service_name: " << service_name << std::endl; 
  std::cout << "method_name: " << method_name << std::endl; 
  std::cout << "args_str: " << args_str << std::endl; 
  std::cout << "============================================" << std::endl;

  // 发起socket连接
  int clientfd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientfd == -1) {
    std::cout << "create socket error, errno: " << errno << std::endl;
  }

  std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
  uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

  if (-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
    close(clientfd);
    // std::cout << "connect failed, errno: " << errno << std::endl;
    std::ostringstream os;
    os << "connect failed, errno: " << errno;
    controller->SetFailed(os.str());
    return;
  }

  if (-1 == send(clientfd, send_rpc_str.c_str(), send_rpc_str.size(), 0)) {
    close(clientfd);
    // std::cout << "send failed, errno: " << errno << std::endl;
    std::ostringstream os;
    os << "send failed, errno: " << errno;
    controller->SetFailed(os.str());
    return;
  }

  char recv_buf[1024];
  bzero(recv_buf, sizeof(recv_buf));
  int recv_size = 0;
  if (-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0))) {
    close(clientfd);
    // std::cout << "recv failed, errno: " << errno << std::endl;
    std::ostringstream os;
    os << "recv failed, errno: " << errno;
    controller->SetFailed(os.str());
    return;
  }
  // 反序列化response
  if (!response->ParseFromArray(recv_buf, recv_size)) {
    close(clientfd);
    // std::cout << "parse response failed, str = " << recv_buf << std::endl;
    std::ostringstream os;
    os << "parse response failed, str = " << recv_buf;
    controller->SetFailed(os.str());
  }
  
  close(clientfd);
}

// caller端用的简单tcp裸socket处理
// 服务端（callee）用的muduo多线程处理