/********************************************************************************
* @author: casidlkai
* @website: casidlkai.com
* @date: 2024/10/31 
* @version: 1.0
* @description: 
********************************************************************************/

#include "../include/accept_request.h"

// 处理用户请求的线程函数
DWORD WINAPI accept_request (LPVOID arg)
{
	char buf[1024] = {0};
	int client = (SOCKET) arg;    // 将传入的参数转换为SOCKET类型,即客户端套接字

	// 从客户端读取一行数据, 并存储到buf中,并返回读取的字符数,保存在 numchars 中
	int numchars = get_line(client, buf, sizeof(buf));
	// PRINTF(buf);

	// method数组用于存储客户端请求方法
	char method[255];
	int i = 0, j = 0;

	// 此处解析到GET，检测到空格时候，结束循环
	while (!isspace(buf[i]) && (i < sizeof(method) - 1))
		method[i++] = buf[j++];
	method[i] = '\0';
	// PRINTF(method);

	// 检查请求的方法是否为GET/POST方法
	if (stricmp(method, "GET") && stricmp(method, "POST"))
	{
		// 向客户端返回请求错误页面
		unimplement(client);
		return 0;
	}

	// 解析资源文件路径
	char url[255] = {0};
	i = 0;
	while (isspace(buf[j]) && (j < numchars))
		j++;
	while (!isspace(buf[j]) && (i < sizeof(url) - 1) && (j < numchars))
		url[i++] = buf[j++];
	url[i] = '\0';
	// PRINTF(url);
	/* 	// 检查读取权限
	    const char *dir_path = "htdocs"; // 要检查的目录路径
	 	if (access(dir_path, R_OK) == 0)
			printf("You have permission to access the directory: %s\n", dir_path);
		else
			perror("access");
	*/
	// 定义文件路径
	char path[512] = {0};
	sprintf(path, "htdocs%s", url);
	if (path[strlen(path) - 1] == '/')
		strcat(path, "index.html");
	// PRINTF(path);
	struct stat status;
	if (stat(path, &status) == -1)
	{
		// 将请求包剩余数据读取完毕
		while (numchars > 0 && strcmp("\n", buf))
			numchars = get_line(client, buf, sizeof(buf));
		char str[] = "htdocs/404.html";
		strcpy(path, str);
		not_found(client, (const char *) path);
		FILE *resource = NULL;
		resource = fopen(path, "r");
		cat(client, resource);
		printf("The resource has been sent.\n");
	}
	else
	{
		if ((status.st_mode & S_IFMT) == S_IFDIR)
			strcat(path, "/index.html");
		server_file(client, path);
	}
	closesocket(client);
	return 0;
}