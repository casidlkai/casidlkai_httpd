#include <string.h>
#include "../include/cat.h"
#include "../include/error_die.h"
#include "../include/get_line.h"
#include "../include/get_mime_type.h"
#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/not_found.h"
#include "../include/server_file.h"
#include "../include/startup.h"
#include "../include/unimplement.h"
#include "../include/accept_request.h"

#pragma comment(lib, "ws2_32.lib")

int main ()
{
	// 低于1024的端口，需要以管理员身份运行
	unsigned short port = 8000;
	int s_sock = startup(&port);    // 服务器端套接字
	// 打印监听到的端口号
	printf("httpd is already, Listening on port %d\n", port);

	// 初始化并监听客户端请求
	struct sockaddr_in c_addr;
	int c_addr_len = sizeof(c_addr);
	while (1)
	{
		// 阻塞式等待用户发起访问
		int c_sock = accept(s_sock, (struct sockaddr *) &c_addr, &c_addr_len);
		// 新线程套接字创建失败则退出程序
		if (c_sock == -1)
			error_die("accept");

		// 多线程接受用户访问
		DWORD threadID = 0;
		// intptr_t 在需要将指针转换为整数时，确保不会出现大小不匹配的问题
		if (CreateThread(0, 0, accept_request, (void *) (intptr_t) c_sock, 0, &threadID) != 0)
			perror("CreateThread");
	}

	// 关闭套接字
	closesocket(s_sock);
	return 0;
}