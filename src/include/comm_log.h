// Copyright 2021 Horizon Robotics
// Created by jiangkuan.liu on 08/25/2021

// This is communication log definition.

#ifndef COMMUNICATION_COMMON_COMM_LOG_H_
#define COMMUNICATION_COMMON_COMM_LOG_H_

#include <cstdarg>
#include <string>
#include <memory>

#define LEFT_BRACKET "["
#define RIGHT_BRACKET "]"

#ifndef MODULE_NAME
#define MODULE_NAME "communication"
#endif

#define LOG_FATAL 5
#define LOG_ERROR 4
#define LOG_WARN 3
#define LOG_INFO 2
#define LOG_DEBUG 1
#define LOG_VERBOSE 0

#ifndef DLLEXPORT
#if defined(_MSC_VER)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#endif

#ifndef DLLIMPORT
#if defined(_MSC_VER)
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLIMPORT
#endif
#endif

#ifndef VALUEXPORT
#if defined(VALUE_EXPORT_WIN)
#define VALUEXPORT DLLEXPORT
#elif !defined(VALUE_EXPORT_WIN)
#define VALUEXPORT DLLIMPORT
#else
#define VALUEXPORT
#endif
#endif

namespace hobot {
namespace communication {
extern VALUEXPORT int comm_colog_level;
void DLLEXPORT SetLogLevel(int level);

class CommLogImpl;

class DLLEXPORT CommLog {
 public:
  CommLog(const char *file, int line, int log_level);
  CommLog(CommLog &&);
  CommLog& operator=(CommLog&&);

  CommLog &operator<<(const char *);
  CommLog &operator<<(const std::string &);
  CommLog &operator<<(int32_t);
  CommLog &operator<<(uint32_t);
  CommLog &operator<<(int64_t);
  CommLog &operator<<(uint64_t);
  CommLog &operator<<(float);
  CommLog &operator<<(double);

  ~CommLog();

  static CommLogImpl* Instance();
  static void CleanUp();

 private:
  std::unique_ptr<CommLogImpl> impl_;
};

}  // namespace communication
}  // namespace hobot

// #define COMM_DEBUG_MODULE(module)
//  LOG(INFO) << LEFT_BRACKET << module << RIGHT_BRACKET << "[DEBUG] "
#define COLOGV if (LOG_VERBOSE >= hobot::communication::comm_colog_level) \
      COMM_LOG_MODULE(MODULE_NAME, INFO)
#define COLOGD if (LOG_DEBUG >= hobot::communication::comm_colog_level)  \
      COMM_LOG_MODULE(MODULE_NAME, INFO_S)
#define COLOGI if (LOG_INFO >= hobot::communication::comm_colog_level)    \
      COMM_LOG_MODULE(MODULE_NAME, INFO_S)
#define COLOGW if (LOG_WARN >= hobot::communication::comm_colog_level)    \
      COMM_LOG_MODULE(MODULE_NAME, WARN_S)
#define COLOGE if (LOG_ERROR >= hobot::communication::comm_colog_level)   \
      COMM_LOG_MODULE(MODULE_NAME, ERROR_S)
#define COLOGF if (LOG_FATAL >= hobot::communication::comm_colog_level)   \
      COMM_LOG_MODULE(MODULE_NAME, FATAL_S)

#ifndef COMM_LOG_MODULE
#define COMM_LOG_MODULE(module, log_severity) \
  COMM_LOG_MODULE_STREAM(log_severity)(module)
#endif

#ifndef COMM_LOG_MODULE_STREAM
#define COMM_LOG_MODULE_STREAM(log_severity) \
     COMM_LOG_MODULE_STREAM_##log_severity
#endif

#define COMM_LOG_MODULE_STREAM_INFO_S(module)                         \
  hobot::communication::CommLog(__FILE__, __LINE__, LOG_INFO) \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define COMM_LOG_MODULE_STREAM_WARN_S(module)                            \
  hobot::communication::CommLog(__FILE__, __LINE__, LOG_WARN) \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define COMM_LOG_MODULE_STREAM_ERROR_S(module)                         \
  hobot::communication::CommLog(__FILE__, __LINE__, LOG_ERROR) \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define COMM_LOG_MODULE_STREAM_FATAL_S(module)                         \
  hobot::communication::CommLog(__FILE__, __LINE__, LOG_FATAL) \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#endif  // COMMUNICATION_COMMON_COMM_LOG_H_
