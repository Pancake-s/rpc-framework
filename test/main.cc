#include <iostream>
#include <string>

#include "test.pb.h"

using test::LoginRequest;

int main() {
    LoginRequest req;
    req.set_name("TankaoSongzi");
    req.set_pwd("123456");

    std::string send_str;
    if (req.SerializeToString(&send_str)) {
        std::cout << send_str.c_str() << std::endl;
    }

    LoginRequest req_b;
    if (req_b.ParseFromString(send_str)) {
        std::cout << req_b.name() << std::endl;
        std::cout << req_b.pwd()  << std::endl;
    }
    return 0;
}
