//#include <cstdio>
#include "Common.h"
#include "HttpServer.h"
#include "NBHttpServer.h"

void block_test()
{
	HttpServer httpServer;

	httpServer.Init(5, NULL);
	httpServer.Run();
}

void nonblock_test(int sec)
{
	NBHttpServer* httpServer = NBHttpServer::getInstance();
	httpServer->Init(5);
	httpServer->Start();
	sleep(sec);
	httpServer->Stop();
}

int main(int argc, char** argv)
{
	cout << "Usage:" << endl;
	cout << "\t`" << argv[0] << "`\t\t: nonblock 5 sec + nonblock 30 sec" << endl;
	cout << "\t`" << argv[0] << " 1`\t\t: block (stop ^c) " << endl;
	cout << "\t`" << argv[0] << " 2 10`\t\t: nonblock 10 sec" << endl;
	cout << "\t`" << argv[0] << " 2 100`\t\t: nonblock 100 sec" << endl << endl;

	if (argc == 1) {
		cout << "START TEST nonblock 5 sec + nonblock 30 sec" << endl << endl;
		nonblock_test(5);
		nonblock_test(10);
	}
	else if (strcmp(argv[1], "1") == 0) {
		cout << "START TEST block (stop ^c)" << endl << endl;
		block_test();
	}
	else if (strcmp(argv[1], "2") == 0) {
		int sec = atoi(argv[2]);
		cout << "START TEST nonblock " << sec << "sec" << endl << endl;
		nonblock_test(sec);
	};

    return 0;
}