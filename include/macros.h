#ifndef CASIDLKAI_HTTPD_MACROS_H
#define CASIDLKAI_HTTPD_MACROS_H
#endif //CASIDLKAI_HTTPD_MACROS_H

// 本文件用于宏定义一些内容
// 定义服务器版本
#define SERVER_STRING "Server: cikhttpd/1.0.0\r\n"
// 用于调试打印输出
#define PRINTF(str) printf("[%s - %d]\t= %s\n", __func__, __LINE__, str)
