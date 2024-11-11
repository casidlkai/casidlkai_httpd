/********************************************************************************
* @author: casidlkai
* @website: casidlkai.com
* @date: 2024/10/31 
* @version: 1.0
* @description: 
********************************************************************************/

#include "../include/headers.h"

// 打包HTTP标头，状态码为200时将内容返回给客户端
void headers (int client, const char *filename)
{
	char buf[4096];
	strcpy(buf, "HTTP/1.1 200 OK\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: %s\r\n", get_mime_type(filename));
	send(client, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
}