#pragma once
#include <Windows.h>
#include <ezlogger_headers.hpp>
#include <boost/lexical_cast.hpp>
#define ERROR_LOGGING_LEVEL axter::ezlogger<>::set_verbosity_level_tolerance(axter::log_often)
#define INFO_LOGGING_LEVEL axter::ezlogger<>::set_verbosity_level_tolerance(axter::log_regularly)
#define DEBUG_LOGGING_LEVEL axter::ezlogger<>::set_verbosity_level_tolerance(axter::log_rarely)
#define NELSK_LOG_ERROR EZLOGGERVL(axter::log_always) << "ERROR: "
#define NELSK_LOG_INFO EZLOGGERVL(axter::log_regularly) << "INFO: "
#define NELSK_LOG_DEBUG EZLOGGERVL(axter::log_rarely) << "DEBUG: "