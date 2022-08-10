#include <google/protobuf/service.h>

using google::protobuf::Closure;

class MprpcController : public google::protobuf::RpcController {
 public:
  MprpcController(): fail_status_(false), error_text_("") { }
  // CLIENT SIDE METHODS
  void Reset() override;
  bool Failed() const override;
  std::string ErrorText() const override;
  void StartCancel() override;

  // SERVER SIDE METHODS
  void SetFailed(const std::string& reason) override;
  bool IsCanceled() const override;
  void NotifyOnCancel(Closure* callback) override;
 private:
  bool fail_status_;
  std::string error_text_;
};
