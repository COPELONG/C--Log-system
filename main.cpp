#include<iostream>
#include "Logger.h"

using namespace std;
using namespace tool;


int main() {
	tool::Logger::instance()->open("log.txt");
	tool::Logger::instance()->max(200);
	
	//tool::Logger::instance()->log(tool::Logger::Level::DEBUG, __FILE__, __LINE__,"hello");
	//tool::Logger::instance()->log(tool::Logger::Level::DEBUG, __FILE__, __LINE__, "name is %s,age is %d","jack",18);
	//tool::Logger::instance()->level(Logger::INFO);
	debug("hello");
	debug("name is %s,age is %d", "jack", 20);
	info("hello");
	warn("world");
	error("devign");
	fatal("OK");
	return 0;
}