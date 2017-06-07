#include "Common.h"
#include "Session.h"

Session::Session(int fd)
{
	_fd = fd;
}


Session::~Session()
{
}

string Session::Read()
{
	const unsigned int MAX_BUF_LENGTH = 4096;
	std::vector<char> buffer(MAX_BUF_LENGTH);
	std::string rcv;
	ssize_t bytesReceivedSum = 0;
	ssize_t bytesReceived = 0;
	do {
		bytesReceived = recv(_fd, buffer.data(), buffer.size(), 0);
		bytesReceivedSum += bytesReceived;
		
		if (bytesReceived == -1) {
			if (bytesReceivedSum == -1) {
				Logger(ERROR) << "Fail socket bytesReceivedSum: " << bytesReceivedSum <<  " Err: " << strerror(errno) << endl;
			}
			break;
		}
		else {
			//rcv.append(buffer.cbegin(), buffer.cend());
			rcv.append(buffer.data(), bytesReceived);
		}
	} while (bytesReceived == MAX_BUF_LENGTH);

	return rcv;
}

int Session::Write(string data)
{
	return (int)::send(_fd, data.c_str(), data.length(), 0);
	//const unsigned int MAX_BUF_LENGTH = 4096;
	//std::vector<char> buffer(MAX_BUF_LENGTH);
	//std::string rcv;
	//ssize_t bytesReceivedSum = 0;
	//ssize_t bytesReceived = 0;
	//do {
	//	bytesReceived = ::send(_fd, buffer.data(), buffer.size(), 0);
	//	bytesReceivedSum += bytesReceived;

	//	if (bytesReceived == -1) {
	//		if (bytesReceivedSum == -1) {
	//			Logger(INFO) << "Fail socket bytesReceivedSum: " << bytesReceivedSum << " Err: " << strerror(errno) << endl;
	//		}
	//		break;
	//	}
	//	else {
	//		rcv.append(buffer.cbegin(), buffer.cend());
	//	}
	//} while (bytesReceived == MAX_BUF_LENGTH);

	//return rcv;
}