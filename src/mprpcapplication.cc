#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>
// 这个Init函数需要用户传一个命令行参数
// 我们希望这么去写 provider -i config.conf

MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp() {
    std::cout << "format: command -i <configfile>" << std::endl;
}

void MprpcApplication::Init(int argc, char **argv) {
  if (argc < 2) {
    ShowArgsHelp();
    exit(EXIT_FAILURE);
  }

  int o = 0;
  std::string config_file;
  while ((o = getopt(argc, argv, "i:")) != -1) {
    switch (o) {
    case 'i':
      config_file = optarg;
      std::cout << "Loading " << config_file << std::endl;
      break;
    default:
      ShowArgsHelp();
      exit(EXIT_FAILURE);
      break;
    }
  }
  // 加载配置文件
  m_config.LoadConfigFile(config_file.c_str());
}

MprpcConfig& MprpcApplication::GetConfig() {
    return m_config;
}