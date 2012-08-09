#pragma once
#include <Windows.h>
#include <ezlogger_headers.hpp>
#define VERBOSE_LOGGING axter::ezlogger<>::set_verbosity_level_tolerance(axter::log_rarely)
#define TIGHT_LOGGING axter::ezlogger<>::set_verbosity_level_tolerance(axter::log_often)