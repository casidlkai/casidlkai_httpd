#include "../include/not_found.h"

// 向客户端返回 404 状态信息
void not_found (int client, const char *filename)
{
	char buf[1024];
	sprintf(buf, "HTTP/1.1 404 NOT FOUND\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: %s\r\n", get_mime_type(filename));
	send(client, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
}