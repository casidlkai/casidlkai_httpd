#include "../include/cat.h"

// 读取服务器上某个文件写到 socket 套接字
void cat(int client, FILE *resource)
{
	char buf[65536];
	int count = 0;
	while (1)
	{
		int ret = fread(buf, sizeof(char), sizeof(buf), resource);
		if (ret <= 0)
			break;
		send(client, buf, ret, 0);
		count += ret;
	}
	printf("%d bytes have been sent to the client\n", count);
}