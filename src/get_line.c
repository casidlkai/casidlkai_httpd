/********************************************************************************
* @author: casidlkai
* @website: casidlkai.com
* @date: 2024/10/31 
* @version: 1.0
* @description: 
********************************************************************************/

#include "../include/get_line.h"

// 返回实际读取到的字节数
int get_line (int sock, char *buf, int size)
{
	int i = 0;
	char c = '\0';
	int n;

	// 实际情况下, 网络中获取到的数据繁杂, 为保证程序健壮性, 增加字符检测范围
	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);
		if (n > 0)
		{
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				if ((n > 0) && (c == '\n'))
					recv(sock, &c, 1, 0);
				else
					c = '\n';
			}
			buf[i++] = c;
		}
		else
			c = '\n';
	}
	buf[i] = '\0';
	return i;
}