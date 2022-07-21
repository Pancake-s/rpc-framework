#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

int main(int argc, char **argv) {
  MprpcApplication::Init(argc, argv);
  
  example::UserServiceRpc_Stub stub(new MprpcChannel());  // TODO: define MprpcChannel class
  example::LoginRequest request;
  request.set_name("Tankaosongzi");
  request.set_pwd("123456");

  example::LoginResponse response;
  // 发起rpc方法调用，发起同步MprpcChannel::CallMethod过程
  stub.Login(nullptr, &request, &response, nullptr);
  if (0 == response.result().errcode()) {
    std::cout << "rpc login success" << std::endl;
  } else {
    std::cout << "rpc login failed: " << response.result().errmsg() << std::endl;
  }

  example::RegisterRequest request1;
  request1.set_id(1);
  request1.set_name("Tankaosongzi");
  request1.set_pwd("123456");
  example::RegisterResponse response1;
  stub.Register(nullptr, &request1, &response1, nullptr);
  if (0 == response1.result().errcode()) {
    std::cout << "rpc register success" << std::endl;
  } else {
    std::cout << "rpc register failed: " << response1.result().errmsg() << std::endl;
  }
  

  return 0;
}
