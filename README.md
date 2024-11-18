## 概述

本人基于开源项目[Tinyhttpd](https://github.com/EZLippi/Tinyhttpd) ，对源码进行剖析，在此基础上进行改写，以了解C语言网络编程运行原理，实现项目完整构建

[源码](https://github.com/casidlkai/casidlkai_httpd.git) 请点此查看

<!-- more -->

## 目录

- 项目目录结构
- 函数功能描述
- 剖析及改进

### 项目目录结构

~~~
casidlkai_httpd
├── /htdocs/
│  ├── /img/
│  │  └── casidl.jpg
│  ├── 404.html
│  └── index.html
├── /include/
│  └── *.h
├── /src/
│  └── *.c
├── CMakeLists.txt
└── README.md
~~~ 

### 函数功能描述

#### 引用函数库说明

`<sys/stat.h>` 提供与文件属性相关的函数和结构定义，用于在windows上操作文件的元数据

`<winsock2.h>` 提供用于网络通信的函数和数据类型，支持创建套接字、发送和接收数据等，支持 TCP 协议，便于客户端与服务器之间的数据交换

#### 本项目自定义函数

`accept_request:` 处理从套接字上监听到的一个 HTTP 请求

`cat:` 读取服务器上某个文件写到 socket 套接字

`error_die:` 调用perror()函数, 对于错误信息报错并退出程序

`get_line:` 读取套接字的一行，把回车换行等情况都统一为换行符结束

`get_mime_type:` 分析请求资源的格式，将资源按照该格式发送给客户端

`headers:` 打包HTTP标头，请求正常状态码为200时将内容返回给客户端

`main:` 程序主函数

`not_found:` 向客户端返回 404 状态信息

`sever_file:` 调用 cat 把服务器文件返回给浏览器

`startup:` 初始化 httpd 服务，包括建立套接字，绑定端口，进行监听等

`unimplement:` 返回给浏览器表明收到的 HTTP 请求所用的 method 不被支持


### 功能剖析

> 仅在此进行流程分析，函数具体功能实现参见函数内注释

#### 工作流程

(1) 服务器启动，在指定端口或随机选取端口绑定 httpd 服务

(2) 调用startup()，创建并返回套接字

(3) 套接字返回到主函数后，初始化并监听客户端请求

(4) 通过127.0.0.1:8000(命令窗口打印出的端口号)访问

(5) 服务器端调用accept_request()

(6) 在accept_request()中，调用get_line()分析 HTTP 请求数据包内容，即请求方法(method)和文件路径(url)

(7) 解析完路径后，调用server_file()

(8) 调用headers()打包HTTP标头，接着调用cat()将内容返回给客户端

#### 错误处理

- 客户端请求方法错误时，调用unimplement()提示请求错误
- 请求的文件资源不存在时，调用not_found()返回404页面
- 套接字绑定、端口分配、监听队列创建等导致程序无法继续运行时，调用error_die()退出程序

### 项目改进

- 将原项目返回txt文件格式泛化，实现常见文件格式都能返回给客户端
- 使用get_mime_type()分析请求资源的格式，确保能够将客户端请求的资源以请求的文件格式发送给客户端

### 作者

[casidlkai](http://casidlkai.com/)

### 鸣谢

- [Tinyhttpd原项目](https://github.com/EZLippi/Tinyhttpd)
- [Github镜像](https://github.com/EZLippi/Tinyhttpd)
- [程序员Rock](https://www.bilibili.com/video/BV1B24y1d7Vi/?spm_id_from=333.999.0.0&vd_source=59394183657fb7e65b9229418a199e74)
