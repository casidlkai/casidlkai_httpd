/********************************************************************************
* @author: casidlkai
* @website: casidlkai.com
* @date: 2024/10/31 
* @version: 1.0
* @description: 
********************************************************************************/

#include "../include/server_file.h"

// 向客户端返回文件资源
void server_file (int client, const char *fileName)
{
	FILE *resource = NULL;
	char numchars = 1;
	char buf[1024];
	while (numchars > 0 && strcmp("\n", buf))
		numchars = get_line(client, buf, sizeof(buf));
	resource = fopen(fileName, "rb");
	// 判断客户端请求的资源是否存在
	if (resource == NULL)
	{
		not_found(client, (const char *) fileName);
		cat(client, resource);
		printf("The resource has been sent.\n");
	}
	else
	{
		// 将资源发送给客户端
		headers(client, (const char *) fileName);
		cat(client, resource);
		printf("The resource has been sent.\n");
	}
	fclose(resource);
}