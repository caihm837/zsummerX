﻿/*
 * zsummerX License
 * -----------
 * 
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2010-2014 YaweiZhang <yawei_zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */


//! zsummer的测试服务模块(对应zsummer底层网络封装的上层设计测试服务) 可视为服务端架构中的 gateway服务/agent服务/前端服务, 特点是高并发高吞吐量
//! Socket Client头文件

#ifndef ZSUMMER_CLIENT_H_
#define ZSUMMER_CLIENT_H_
#include "header.h"
#include "Process.h"

//! 上层Socekt Client的二次封装
class CClient : public std::enable_shared_from_this<CClient>
{
public:
	CClient(CProcess &proc, CTcpSocketPtr sockptr);
	~CClient();
	void Initialize();
private:
	void OnConnected(zsummer::network::ErrorCode ec);

	void DoRecv();
	void OnRecv(zsummer::network::ErrorCode ec, int nRecvedLen);
	void MessageEntry(zsummer::proto4z::ReadStream<zsummer::proto4z::DefaultStreamHeadTraits> & rs);



	void SendOnce();
	void DoSend(unsigned short protocolID, unsigned long long clientTick, const std::string & text);
	void DoSend(char *buf, unsigned short len);
	void OnSend(zsummer::network::ErrorCode ec,  int nSentLen);

	
	void OnClose();

	CProcess  & m_process;
	CTcpSocketPtr  m_sockptr;
	bool m_bEstablished = false;
	
	//! 读包
	Packet m_recving;
	std::string m_recvTextCache;

	//! 写包队列
	std::queue<Packet *> m_sendque;

	//! 当前写包

	char m_sendBuff[_SEND_BUF_LEN];
	unsigned short m_sendLen = 0;
	unsigned short m_curSendLen = 0;

	unsigned long long m_lastDelayTime = 0; //最后一次收到echo消息的延迟时间
};

#endif


