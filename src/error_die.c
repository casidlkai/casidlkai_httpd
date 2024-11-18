#include "../include/error_die.h"

// 调用perror()函数, 对于错误信息报错并退出程序
void error_die (const char *str)
{
	perror(str);
	exit(1);
}