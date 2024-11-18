#include "../include/get_mime_type.h"

// 分析请求资源的格式，将资源按照该格式发送给客户端
const char *get_mime_type (const char *filename)
{
	if (strstr(filename, ".html") || strstr(filename, ".htm"))
		return "text/html";
	if (strstr(filename, ".jpg") || strstr(filename, ".jpeg"))
		return "image/jpeg";
	if (strstr(filename, ".png"))
		return "image/png";
	if (strstr(filename, ".gif"))
		return "image/gif";
	if (strstr(filename, ".css"))
		return "text/css";
	if (strstr(filename, ".js"))
		return "application/javascript";
	return "application/octet-stream"; // default
}