#include "mprpccontroller.h"

void MprpcController::Reset() {
  fail_status_ = false;
  error_text_ = "";
}

bool MprpcController::Failed() const {
  return fail_status_;
}

std::string MprpcController::ErrorText() const {
  return error_text_;
}

void MprpcController::SetFailed(const std::string& reason) {
  fail_status_ = true;
  error_text_ = reason;
}