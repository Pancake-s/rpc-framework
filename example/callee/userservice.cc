#include <iostream>
#include <string>

#include "user.pb.h"
#include "mrpcprovider.h" // 有隐藏依赖的问题
#include "mprpcapplication.h"
#include "logger.h"

// 本地服务 Login() GetFriendLists()

// class UserService {
//   public:
//     bool Login(std::string name, std::string pwd) {
//         std::cout << "local service: Login" << std::endl;
//         std::cout << " name = " << name << " pwd = " << pwd << std::endl;
//     }
// };

class UserService : public example::UserServiceRpc {
  public:
    // 本地函数？
    bool Login(std::string name, std::string pwd) {
      std::cout << "local service: Login" << std::endl;
      std::cout << " name = " << name << " pwd = " << pwd << std::endl;
      return false;
    }
    
    bool Register(uint32_t id, std::string name, std::string pwd) {
      std::cout << "local service: Register" << std::endl;
      std::cout << " id: " << id << " name: " << name << " pwd: " << pwd
                << std::endl;
      return true;
    }

    // 重写基类的虚函数，发布为RPC服务？
    // 1. caller RPC -> Login(LoginRequest) -> moduo -> example
    void Login(::google::protobuf::RpcController* controller,
               const ::example::LoginRequest* request,
               ::example::LoginResponse* response,
               ::google::protobuf::Closure* done) {
      std::string name = request->name();
      std::string pwd = request->pwd();

      bool login_result = Login(name, pwd);

      example::ResultCode *code = response->mutable_result();
      code->set_errcode(0);
      code->set_errmsg("");
      response->set_success(login_result);

      // 执行回调操作，重写Closure的Run方法
      done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                  const ::example::RegisterRequest* request,
                  ::example::RegisterResponse* response,
                  ::google::protobuf::Closure* done) {
      uint32_t id = request->id();
      std::string name = request->name();
      std::string pwd = request->pwd();

      bool register_result = Register(id, name, pwd);

      example::ResultCode *code = response->mutable_result();
      code->set_errcode(0);
      code->set_errmsg("");
      response->set_success(register_result);

      done->Run();
    }
};



int main(int argc, char **argv) {
  // Initialisation
  LOG_ERR("this is userservice");

  MprpcApplication::Init(argc, argv);

  // provider是一个rpc网络的服务对象，把UserService对象发布到rpc节点上
  RpcProvider provider;
  provider.NotifyService(new UserService());
  // provider.NotifyService(new ProductService());
  // ... 可以挂多个服务

  provider.Run();
  // Run以后，进程进入阻塞状态，等待远程rpc调用请求

  return 0;
}