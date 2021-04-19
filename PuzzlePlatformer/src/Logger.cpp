#include "Logger.h"
#include <iostream>

void* Logger::m_outputHandle = nullptr;

void Logger::Log(std::string message)
{
	// if (m_outputHandle == nullptr)
	// {
	// 	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	// }

	// SetConsoleTextAttribute(m_outputHandle, 15);
	std::cout << "[LOG] " << message << std::endl;
}

void Logger::Warn(std::string message)
{
	// if (m_outputHandle == nullptr)
	// {
	// 	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	// }

	// SetConsoleTextAttribute(m_outputHandle, 14);
	std::cout << "[WARN] " << message << std::endl;
}

void Logger::Error(std::string message)
{
	// if (m_outputHandle == nullptr)
	// {
	// 	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	// }

	// SetConsoleTextAttribute(m_outputHandle, 12);
	std::cout << "[ERROR] " << message << std::endl;
}
