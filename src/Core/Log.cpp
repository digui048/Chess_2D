#include "Log.h"

std::vector<Log::LogEntry> Log::s_LogEntries;

void Log::Init()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    console_sink->set_pattern("%^[%T][Chess-%l]: %v%$");

    auto logger = std::make_shared<spdlog::logger>("ChessLogger", console_sink);
    spdlog::set_default_logger(logger);
}