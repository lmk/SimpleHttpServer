#include "Common.h"
#include "HttpServer.h"
#include "HttpWorker.h"

HttpServer::HttpServer()
{
	_poolSize = 5;
	_listenPort = 0;
	_IsConitnue = NULL;
}


HttpServer::~HttpServer()
{
}

// set maxinum socket count
void HttpServer::Init(int poolSize, funcIsConitnuePtr func)
{
	_poolSize = poolSize;
	_IsConitnue = func;
}

void HttpServer::Run()
{
	Logger(INFO) << "START HTTP SERVER" << endl;

	// 가용한 포트를 찾아서 listen
	int listen_fd = listenPort();
	if (listen_fd == 0) {
		return;
	}

	Logger(INFO) << "Listen Port:" << _listenPort << ", pool:" << _poolSize << endl;

	// 최대 pool 사이즈를 정하고
	sessions.Init(_poolSize);

	fd_set fds_read;
	int result = 0;
	struct timeval to;

	// select 주기
	to.tv_usec = 100;
	to.tv_sec = 0;  
	
	while (true)
	{
		if (_IsConitnue != NULL && _IsConitnue() == false) break;

		FD_ZERO(&fds_read);
		FD_SET(listen_fd, &fds_read);
		sessions.FD_SET_All(&fds_read);

		result = select(FD_SETSIZE, &fds_read, NULL, NULL, &to);
		if (result < 0) {
			Logger(CRITICAL) << "Fail select socket " << strerror(errno) << endl;
			close(listen_fd);
			return;
		}
		else if (result == 0) {
			FD_SET(listen_fd, &fds_read);
			usleep(100);
			continue;
		}

		// listen socket 처리부
		if (FD_ISSET(listen_fd, &fds_read)) {
			int conn_fd = accept(listen_fd, NULL, NULL);
			sessions.Add(conn_fd);
			Logger(INFO) << "Connection new fd: " << conn_fd << endl;
		}

		// connection socket 처리부
		vector<int> all_fd = sessions.GetAllFd();
		for (vector<int>::size_type i = 0; i<all_fd.size(); i++) {
			int conn_fd = all_fd[i];
			if (FD_ISSET(conn_fd, &fds_read)) {
				Session *s = sessions.Get(conn_fd);
				if (s == NULL) {
					Logger(ERROR) << "Error not found connectted fd: " << conn_fd << endl;
					continue;
				}

				string sRequest = s->Read();

				// 읽은 데이터가 없으면 접속 종료
				if (sRequest.length() == 0) {
					sessions.Remove(conn_fd);
					Logger(INFO) << "READ (" << conn_fd << "): Close" << endl;
					continue;
				}

				Logger(INFO) << "REQUEST PACKET START (fd:" << conn_fd  << ")-----------------------------" << endl;
				Logger(INFO) << sRequest << endl;
				Logger(INFO) << "REQUEST PACKET END -----------------------------" << endl;

				stringstream ssResponse;

				HttpWorker worker;
				if (worker.Run(sRequest, ssResponse) == false) {
					continue;
				};

				s->Write(ssResponse.str());

				Logger(INFO) << "RESPONSE PACKET START (fd:" << conn_fd << ")-----------------------------" << endl;
				Logger(INFO) << ssResponse.str() << endl;
				Logger(INFO) << "RESPONSE PACKET END -----------------------------" << endl;

				sessions.Remove(conn_fd);
				Logger(INFO) << "Close (" << conn_fd << ")" << endl;
			}
		}

		usleep(100);
	}

	sessions.Release();

	Logger(INFO) << "END HTTP SERVER" << endl;
}

/**
 @brief listen
 @return listen socket fd
*/
int HttpServer::listenPort()
{
	struct sockaddr_in server_addr;

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		Logger(CRITICAL) << " Fail socket: " << strerror(errno) << endl;
		return 0;
	}

	_listenPort = 8080;
	server_addr.sin_port = htons(_listenPort);
	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0) {
		Logger(CRITICAL) << " Fail bind: " << strerror(errno) << endl;
		return 0;
	}

	listen(socket_fd, 128);

	return socket_fd;
}