# C++-Log-system

## 需求：

1.日志存储：文本文件

2.日志内容：时间、级别、文件、行号、内容

3.日志级别：debug<info<warn<error<fatal

4.日志翻滚：设置日志大小

## 知识点：

```cpp
enum Level {
			DEBUG = 0,
			INFO,
			WARN,
			ERROR,
			FATAL,
			LEVEL_COUNT
		};//这个枚举类型中的LEVEL_COUNT会自动计数，它的值将是枚举中定义的元素数量。在这种情况下，LEVEL_COUNT的值将是5，因为它前面定义了5个枚举元素。
//注意，LEVEL_COUNT本身不是枚举类型的一个成员，而是一种用于表示枚举元素数量的技巧。它不会被视为一个有效的枚举元素，并且不会参与到枚举的操作中，如枚举类型的迭代等。
```

```c++
Logger* Logger::m_instance = NULL;
Logger*m_instance = NULL;

//在 C++ 中，类中的静态成员变量需要进行完整的限定符（包括命名空间和类名）才能被正确识别。这是因为在编译时，静态成员变量被视为属于类而不是属于任何对象，因此需要用类名来限定。
//在你的代码中，Logger::m_instance 是 Logger 类的静态成员变量，因此需要使用 Logger:: 来限定。如果省略了 Logger::，编译器将无法识别 m_instance 是哪个类的静态成员变量，从而导致链接错误。
//因此，正确的写法应该是 Logger* Logger::m_instance = NULL;。
//所以不同的类可以定义同名的静态成员变量，因为它们是属于各自类的。
```

```c++
time_t ticks = time(NULL);
	struct tm ptm;
	localtime_s(&ptm, &ticks);
	char timestamp[32];
	memset(timestamp, 0, sizeof(timestamp));//填充为0
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ptm);
	cout << timestamp << endl;
//struct tm 结构体类型提供了一种易于处理和理解时间的方式，它包含了年、月、日、时、分、秒等时间信息，并且可以根据本地时区进行调整。因此，将 Unix 时间戳转换为 struct tm 结构体类型可以更方便地对时间进行格式化和操作。

//在代码示例中，通过将 Unix 时间戳转换为 struct tm 结构体类型，然后使用 strftime() 函数将其格式化成一个字符串形式的时间戳，更方便地输出或处理时间。

```

```
__FILE__表示当前代码所在的文件名，它是在预处理阶段被替换成一个字符串常量，例如："main.cpp"。

而__LINE__表示当前代码所在的行号，也是在预处理阶段被替换成一个整数常量，例如：42。
直接使用即可。
```

```c++
const char* fmt = "%s %s %s:%d"; 

//声明一个常量字符串变量fmt，其中包含一个格式字符串，指定了所需的输出格式。％s是一个字符串的占位符，％d是一个整数的占位符。

int size = snprintf(NULL, 0, fmt, timestamp, m_level[level], file, line);
//- 使用snprintf函数计算需要的字符数量。第一个参数是指向输出字符的缓冲区的指针，由于我们只需要计算所需的字符数量，因此这里传入NULL。第二个参数是输出字符的最大数量，由于我们只需要计算所需的字符数量，因此这里传入0。第三个参数是格式化字符串，后面的参数是格式化字符串中的替换字符串。计算完成后，该函数返回输出字符串的长度。
snprintf(buffer, size + 1, fmt, timestamp, m_level[level], file, line);
//使用snprintf函数将格式化后的字符串写入buffer中。
```

```c++
	va_list arg_ptr;
	va_start(arg_ptr, format);
	size = vsnprintf(NULL, 0, format, arg_ptr);
	va_end(arg_ptr);
vsnprintf(content, size + 1, format, arg_ptr);
//arg_ptr 是一个指向参数列表的指针，它的作用是在调用 vsnprintf() 函数时，提供格式化字符串 format 中所需的所有可变参数。通过使用 va_start() 和 va_end() 函数来初始化和结束对 arg_ptr 的访问，可以确保在调用 vsnprintf() 函数时访问参数列表的正确性和安全性。在函数调用期间，vsnprintf() 函数使用 arg_ptr 来访问参数列表中的每个参数，并将其根据格式化字符串 format 中的指定格式进行格式化，最后将格式化后的结果写入到指定的输出缓冲区（这里是 content 数组）中。
```

```c++
	m_fout.seekp(0, ios::end);
	m_len = m_fout.tellp();
//将文件指针移动到文件结尾，第一个参数0表示相对于文件开头的偏移量为0，第二个参数ios::end表示相对于文件结尾进行偏移。
//m_len = m_fout.tellp()获取当前文件指针的位置，即文件结尾的位置，同时将该位置的值赋值给变量m_len。这样，m_len就保存了文件的长度（以字节为单位）。
```

debug("hello");

#define debug(format, ...) \
Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__,format,##__VA_ARGS__)
//采用宏定义的方式定义此函数，调用单例，format自动识别转换为const char* 类型。
