#pragma once

#include <string>

class Logger
{
public:
	static void Log(std::string message);
	static void Warn(std::string message);
	static void Error(std::string message);
private:
	static void* m_outputHandle;
};