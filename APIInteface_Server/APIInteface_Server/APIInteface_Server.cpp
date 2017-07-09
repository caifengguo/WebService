


#include "soapService.h"
#include "ns.nsmap"



int main(int argc, char **argv)
{ 
	Service server;
	if (argc < 2)
		server.serve();
	else
	{ 
		int port = atoi(argv[1]);
		if (!port)
		{
			fprintf(stderr, "Usage: Service++ <port>\n");
			exit(0);
		}
		/* run iterative server on port until fatal error */
		if (server.run(port))
		{
			server.soap_stream_fault(std::cerr);
			exit(-1);
		}
	}
	return 0;
} 



int Service::startModel(int* result)
{
	fprintf(stdout,"startModel success!\n");
	*result = 0;
	return SOAP_OK;
} 

int Service::endModel(int* result)
{
	fprintf(stdout,"endModel success!\n");
	*result = 0;
	return SOAP_OK;
} 

int Service::startBd(int* result)
{
	fprintf(stdout,"startBd success!\n");
	*result = 0;
	return SOAP_OK;
} 

int Service::endBd(int *result)
{
	fprintf(stdout,"endBd success!\n");
	*result = 0;
	return SOAP_OK;
}
