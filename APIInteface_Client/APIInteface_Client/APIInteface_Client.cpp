


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

	//�жϽӿڵ���
	if (RetValue == SOAP_OK)
	{
		if (result == 0)
		{
			fprintf(stdout,"���óɹ�!\n");
			system("pause");
		}
		else
		{
			fprintf(stdout,"����ʧ��!\n");
		}
	}

	if (APIInterface.error)
		APIInterface.soap_stream_fault(std::cerr);
	else
		printf("result = %g\n", result);
	return 0;
}

