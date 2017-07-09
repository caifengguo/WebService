


#include "soapProxy.h"
#include "ns.nsmap"

const char server[] = "http://192.168.128.209:8080/";

int main(int argc, char **argv)
{ 
	int result;
	Proxy  APIInterface;
	APIInterface.soap_endpoint = server;
	int RetValue = -1;

	RetValue = APIInterface.startModel(&result);
	//RetValue = APIInterface.endModel(&result);
	//RetValue = APIInterface.startBd(&result);
	//RetValue = APIInterface.endBd(&result);

	//判断接口调用
	if (RetValue == SOAP_OK)
	{
		if (result == 0)
		{
			fprintf(stdout,"调用成功!\n");
			system("pause");
		}
		else
		{
			fprintf(stdout,"调用失败!\n");
		}
	}

	if (APIInterface.error)
		APIInterface.soap_stream_fault(std::cerr);
	else
		printf("result = %g\n", result);
	return 0;
}

