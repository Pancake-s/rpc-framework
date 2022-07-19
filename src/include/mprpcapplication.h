#pragma once
#include "mprpcconfig.h"

class MprpcApplication {
  public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance() {
        static MprpcApplication app;
        return app;
    }
    static MprpcConfig& GetConfig();
  protected:
    MprpcApplication() { };
    ~MprpcApplication() = default;
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    MprpcApplication& operator=(MprpcApplication&&) = delete;
  private:
    static MprpcConfig m_config;
};
