#include "mprpcconfig.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void MprpcConfig::LoadConfigFile(const char *config_file) {
  std::ifstream ifile(config_file);
  if (ifile) {
    std::cout << config_file << " open success." << std::endl;
    std::string line;
    while (getline(ifile, line)) {
      if (!line.empty() && line[0] != '#') {
        std::istringstream is(line);
        std::string key;
        std::string val;
        getline(is, key, '=');
        getline(is, val, '\n');
        key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
        val.erase(std::remove_if(val.begin(), val.end(), isspace), val.end());
        std::cout << key << "=" << val << std::endl;
        m_config_map.insert({key, val});
      }
    }
  }
}

std::string MprpcConfig::Load(const std::string &key) {
  auto it = m_config_map.find(key);
  if (it != m_config_map.end()) {
    return it->second;
  }
  return "";
}