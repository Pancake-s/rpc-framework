#pragma once

class MprpcApplication {
  public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance() {
        static MprpcApplication app;
        return app;
    }
  protected:
    MprpcApplication() { };
    ~MprpcApplication() = default;
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    MprpcApplication& operator=(MprpcApplication&&) = delete;
};
