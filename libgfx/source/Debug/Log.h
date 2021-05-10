#pragma once
#include <string>
#include <fstream>
#include <iostream>
namespace Core
{	//TODO: Next Versiom
	//Category = Maths, Physics, Resources, Shader
	//Severity = INFO, WARNING, ERROR, FATAL, ASSERT
	//SourceInfo = file name, function name, line number;
	namespace Debug
	{
		//#ifdef DEBUG
		//		class Log
		//		{
		//		public:
		//			enum Priority
		//			{
		//				DEBUG,
		//				CONFIG,
		//				INFO,
		//				WARNING,
		//				ERROR
		//			};
		//
		//			static void Start(Priority minPriority, const std::string& file);
		//			static void Stop();
		//
		//			static void Write(Priority priority, const std::string& msg);
		//
		//		private:
		//			//singleton
		//			Log();
		//			Log(const Log& log) {}
		//			Log& operator=(const Log& log) {}
		//			~Log() = default;
		//
		//			bool m_active = false;
		//			std::ofstream	m_fileStream;//TODO: ajouter un commentaire explicatif
		//			Priority m_minPriority;
		//
		//			//String for Priority
		//			static const std::string PRIORITY_NAMES[];
		//
		//			//Log instance(singleton)
		//			static Log m_instance;
		//
		//	};
		//#endif // DEBUG
	}
}