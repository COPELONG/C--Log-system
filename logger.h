
#pragma once
#include<fstream>
#include<string>
#include<stdarg.h>

using namespace std;
namespace tool {

#define debug(format, ...) \
Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__,format,##__VA_ARGS__)
#define info(format, ...) \
Logger::instance()->log(Logger::INFO, __FILE__, __LINE__,format,##__VA_ARGS__)
#define warn(format, ...) \
Logger::instance()->log(Logger::WARN, __FILE__, __LINE__,format,##__VA_ARGS__)
#define error(format, ...) \
Logger::instance()->log(Logger::ERROR, __FILE__, __LINE__,format,##__VA_ARGS__)
#define fatal(format, ...) \
Logger::instance()->log(Logger::FATAL, __FILE__, __LINE__,format,##__VA_ARGS__)
	class Logger {

	public:
		enum Level {
			DEBUG = 0,
			INFO,
			WARN,
			ERROR,
			FATAL,
			LEVEL_COUNT

		};
		void log(Level level, const char* file, int line, const char* format, ...);
		void open(const string &filename);
		void close();
		void max(int bytes) {
			m_max = bytes;
		}
		void level(Level level) {
			m_leve = level;
		}
		
		static Logger* instance();
	private:
		Logger();
		~Logger();
		void rotate();
	private:
		string m_filename;
		Level m_leve;
		int m_max;
		int m_len;
		ofstream m_fout;
		static const char* m_level[LEVEL_COUNT];
		static Logger* m_instance;
	};


}
