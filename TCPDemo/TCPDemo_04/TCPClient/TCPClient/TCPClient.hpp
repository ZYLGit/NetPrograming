//
//  TCPClient.hpp
//  TCPClient
//
//  Created by shenyuanluo on 2018/2/12.
//  Copyright © 2018年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef TCPClient_hpp
#define TCPClient_hpp

#include <iostream>     // cout
#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>     // close


#define BUFF_SIZE 4096
#define HB_INTERVAL 10                  // 心跳时间间隔（单位：秒）


/** 返回值 枚举 */
typedef enum __retValue {
    Ret_error               = -2,       // 出错
    Ret_failed              = -1,       // 失败
    Ret_success             = 0,        // 成功
}RetValue;


void* SendHeartBeat(void *arg);         /** 发送心跳 */
void* SendMsg(void *arg);               /** 发送消息 */
void* RecvMsg(void *arg);               /** 接收消息 */


class TCPClient
{
private:
    struct sockaddr_in serverAddr;      // 服务端地址
    socklen_t serAddrLen;               // 地址长度
    int clientSockfd;                   // 客户端 socket
    
    
    /**
     格式化发送数据
     
     @param buf 数据缓冲区
     @param bufLen 缓冲区长度
     @param cmd 命令类型
     @param userId 用户 ID
     @return > 0：格式化成功（需要发送数据大小）；否则，失败
     */
    int SendDataFormat(char *buf, unsigned int bufLen, unsigned int cmd, const char userId[]);
    
    /**
     解析接收的数据
     
     @param buf 数据缓冲区
     @param msgLen 消息长度
     @param cmd 命令类型
     @param status 用户状态
     @param userId 用户 ID
     @return 解析是否成功；0：成功，否则失败
     */
    int RecvDataParse(char *buf, unsigned int msgLen, unsigned int *cmd, unsigned int *status, char *userId);
    
    /**
     发送心跳
     
     @param arg 线程参数（TCPClient实例指针）
     */
    friend void* SendHeartBeat(void* arg);
    
    /**
     发送消息
     
     @param arg 线程参数（TCPClient实例指针）
     */
    friend void* SendMsg(void* arg);
    
    /**
     接收消息
     
     @param arg 线程参数（TCPClient实例指针）
     */
    friend void* RecvMsg(void* arg);
    
    
public:
    TCPClient(std::string ipStr, unsigned int port);
    ~TCPClient();
    
    /**
     连接 服务端

     @return 参见‘RetValue’
     */
    RetValue Connect();
    
    /**
     运行 客户端

     @return 参见‘RetValue’
     */
    RetValue Run();
    
};

#endif /* TCPClient_hpp */
