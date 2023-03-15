#include "Logger.h"
#include<string>
#include<time.h>
#include<iostream>
#include<stdexcept>
#include<ctime>
using namespace tool;


void tool::Logger::log(Level level, const char* file, int line, const char* format, ...)
{
	
	if (m_leve > level) {
		return;
	}
	if (m_fout.fail()) {
		throw new logic_error(m_filename + "error open");
	}
	time_t ticks = time(NULL);
	struct tm ptm;
	localtime_s(&ptm, &ticks);
	char timestamp[32];
	memset(timestamp, 0, sizeof(timestamp));
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ptm);
	
	const char* fmt = "%s %s %s:%d";
	int size = snprintf(NULL, 0, fmt, timestamp, m_level[level], file, line);
	if (size > 0) {
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, fmt, timestamp, m_level[level], file, line);
		buffer[size] = 0;
		
		m_fout << buffer;
		m_len += size;
		delete buffer;
	}
	va_list arg_ptr;
	va_start(arg_ptr, format);
	size = vsnprintf(NULL, 0, format, arg_ptr);
	va_end(arg_ptr);
	if (size > 0) {
		char* content = new char[size + 1];
		va_start(arg_ptr, format);
		vsnprintf(content, size + 1, format, arg_ptr);
		va_end(arg_ptr);
		content[size] = 0;
		m_fout << content;
		m_len += size;
		delete content;
	}
	
	m_fout << "\n";
	m_fout.flush();
	if (m_len > m_max && m_max > 0) {
		rotate();
	}
	
}

void Logger::open(const string& filename)
{
	m_filename = filename;
	m_fout.open(filename);
	if (m_fout.fail()) {
		throw new logic_error(filename + "error open");
	}
	m_fout.seekp(0, ios::end);
	m_len = m_fout.tellp();
	
}

void Logger::close()
{
	m_fout.close();
}



Logger* Logger::instance()
{
	if (m_instance == NULL) {
		m_instance = new Logger();
	}
	return m_instance;
}



Logger::Logger():m_leve(DEBUG),m_max(0),m_len(0) {

}
Logger::~Logger() {
	close();
}

void tool::Logger::rotate()
{
	close();
	string path = "D://C++Project//C++ - Log - system/";
	time_t ticks = time(NULL);
	struct tm ptm;
	localtime_s(&ptm, &ticks);
	char timestamp[32];
	memset(timestamp, 0, sizeof(timestamp));
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ptm);
	 string M_filename=m_filename;
	string newfilename =path+ M_filename.insert(3,timestamp);
	//string test = "newnewnewnew.txt";
	m_filename = path + m_filename;
	int a = rename(m_filename.c_str(), newfilename.c_str());
	if (a != 0)
	{
		//string old = m_filename;
		//string new1 = filename;
		cout << "error rename" << endl;
		exit;
	}
	open(m_filename);
}

const char* Logger::m_level[LEVEL_COUNT] = {
	
	        "DEBUG",
			"INFO",
			"WARN",
			"ERROR",
			"FATAL",
};
Logger* Logger::m_instance = NULL;