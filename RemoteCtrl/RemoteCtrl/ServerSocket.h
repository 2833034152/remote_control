#pragma once
#include "pch.h"
#include "framework.h"
class CServerSocket
{
public :
	static CServerSocket * getInstance() {
		if (m_instance == nullptr) {
			m_instance = new CServerSocket();
		}
		return m_instance;
	}

	bool InitSocket() {
		//�׽��ֳ�ʼ��
		
		if (m_sock == -1) return false;
		sockaddr_in serv_adr;
		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = INADDR_ANY;
		serv_adr.sin_port = htons(9527);

		int res = bind(m_sock, (sockaddr*)&serv_adr, sizeof(serv_adr) );
		if (bind(m_sock, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
			return false;
		}
		if(listen(m_sock, 1) == -1) return false;

		//char buffer[1024];
		//int cli_sz = sizeof(client_addr);
		//closesocket(serv_sock);
		return true;
	}

	bool AcceptClient() {
		sockaddr_in client_adr;
		int cli_sz = sizeof(client_adr);
	    m_client = accept(m_sock, (sockaddr*)&client_adr, &cli_sz);
		if (m_client == -1) return false;
		return true;
	}
	bool DealCommand() {
		if (m_client == -1) return false;
		char buffer[1024] = "";
		while (1) {
			int len = recv(m_client, buffer, sizeof(buffer), 0);
			if (len <= 0) return -1;
		}
		//�������ҵ���߼�
	}

	bool Send(const char* pData, int nSize) {
		return send(m_client, pData, nSize, 0) > 0;
	}
private:
	SOCKET m_sock;
	SOCKET m_client;
	CServerSocket &  operator= (const  CServerSocket & ss){}  //��ֵ����

	CServerSocket(const CServerSocket & ss){
		m_sock = ss.m_sock;
		m_client = ss.m_client;	
	} 
	CServerSocket() {
		m_client = INVALID_SOCKET;
		if (InitSockEnv() == false) {
			MessageBox(NULL, _T("�޷���ʼ���׽��֣��������绷����"), _T("��ʼ������"), MB_OK | MB_ICONERROR);
			exit(-1);
		}
		SOCKET m_sock = socket(PF_INET, SOCK_STREAM, 0);
	}
	~CServerSocket() {
		WSACleanup();
	}
	bool InitSockEnv() {
		WSADATA data;
		
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
			return false;
		}
		return true;
	}
	static void releaseInstance() {
		if (m_instance != NULL) {
			CServerSocket* tmp = m_instance;
			m_instance = nullptr;
			delete tmp;
		}
	}

	static CServerSocket* m_instance;


	class CHelper {
	public:
		CHelper(){
			CServerSocket::getInstance();
		}
		~CHelper() {
			CServerSocket::releaseInstance();
		}

	};
	static CHelper m_helper;
	
};

 //extern CServerSocket server;


 

