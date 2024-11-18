#include "../include/startup.h"

/*
 * 实现网络初始化
 * 参数: 端口地址 标准化端口号为短整型
 * 返回值: 服务器端套接字
 *		  若传入的值为0, 就自动分配一个可用端口
 */
int startup (unsigned short *port)
{
	int httpd = 0;
	int on = 1;
	struct sockaddr_in name;

	// 网络通信初始化
	WSADATA data;
	// 定义绑定的未连接的套接字            // 指向 WSADATA 数据结构的指针，用于接收 Windows 套接字实现的详细信息
	if (WSAStartup(MAKEWORD(1, 1), &data))
		error_die("WSAStartup");

	// socket()套接字函数创建绑定到特定传输服务提供程序的套接字
	httpd = socket(    // 定义返回套接字
			AF_INET,        // 套接字类型, 网络套接字
			SOCK_STREAM,    // 数据流型套接字
			IPPROTO_TCP);   // 传输类型
	if (httpd == -1)
		error_die("socket");
	// 配置服务器端网络地址
	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;        // 网络地址类型
	name.sin_port = htons(*port);    // 将主机字节顺序转变成网络字节顺序
	name.sin_addr.s_addr = htonl(INADDR_ANY); // 将主机数转换成无符号长整型的网络字节顺序
	// 设置端口可复用
	if (setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) < 0)
		error_die("setsockopt failed");
	// 绑定套接字
	if (bind(httpd, (struct sockaddr *) &name, sizeof(name)) < 0)
		error_die("bind");
	// 动态分配端口
	if (*port == 0)
	{
		int namelen = sizeof(name);
		if (getsockname(httpd, (struct sockaddr *) &name, &namelen) == -1)
			error_die("getsockname");
		*port = ntohs(name.sin_port);
	}
	// 创建监听队列
	if (listen(httpd, 5) < 0)
		error_die("listen");
	return httpd;
}

