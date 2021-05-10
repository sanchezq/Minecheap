#include "Debug/Log.h"

namespace Core
{
	namespace Debug
	{
		//
		//
		//		///* Static initialization*/
		//		////--------------------------------------------------------
		//		//const std::string Log::PRIORITY_NAMES[] = {
		//		//	"DEBUG",
		//		//	"CONFIG",
		//		//	"INFO",
		//		//	"WARNING",
		//		//	"ERROR"
		//		//};
		//
		//		//Log Log::m_instance;
		//		////--------------------------------------------------------
		//
		//
		//
		//		//void Log::Start(Priority minPriority, const std::string& file)
		//		//{
		//		//	m_instance.m_active = true;
		//		//	m_instance.m_minPriority = minPriority;
		//
		//		//	if (file != "")
		//		//	{
		//		//		m_instance.m_fileStream.open(file.c_str());
		//		//	}
		//		//}
		//
		//		//void Log::Stop()
		//		//{
		//		//	m_instance.m_active = false;
		//		//	if (m_instance.m_fileStream.is_open())
		//		//	{
		//		//		m_instance.m_fileStream.close();
		//		//	}
		//		//}
		//
		//		//void Log::Write(Priority priority, const std::string& msg)
		//		//{
		//		//	if (m_instance.m_active && priority >= m_instance.m_minPriority)
		//		//	{
		//		//		//TODO:Revise
		//		//		//identifier le flux de sortie actuel
		//
		//		//		std::ostream& stream = m_instance.m_fileStream.is_open() ? m_instance.m_fileStream : std::cout;
		//
		//		//		stream << PRIORITY_NAMES[priority] << ": " << msg << std::endl;
		//		//	}
		//		//}
	}
}