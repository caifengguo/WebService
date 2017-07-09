/* soapService.cpp
   Generated by gSOAP 2.8.22 from APIINTEFACE.H

Copyright(C) 2000-2015, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapService.h"

Service::Service()
{	Service_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

Service::Service(const struct soap &_soap) : soap(_soap)
{ }

Service::Service(soap_mode iomode)
{	Service_init(iomode, iomode);
}

Service::Service(soap_mode imode, soap_mode omode)
{	Service_init(imode, omode);
}

Service::~Service()
{ }

void Service::Service_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "http://tempuri.org/ns.xsd", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void Service::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void Service::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	Service_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
Service *Service::copy()
{	Service *dup = SOAP_NEW_COPY(Service(*(struct soap*)this));
	return dup;
}
#endif

int Service::soap_close_socket()
{	return soap_closesock(this);
}

int Service::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int Service::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int Service::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int Service::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int Service::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void Service::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void Service::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *Service::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void Service::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *Service::soap_header()
{	return this->header;
}

int Service::run(int port)
{	if (soap_valid_socket(this->master) || soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				break;
			soap_destroy(this);
			soap_end(this);
		}
	}
	return this->error;
}

SOAP_SOCKET Service::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET Service::accept()
{	return soap_accept(this);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int Service::ssl_accept()
{	return soap_ssl_accept(this);
}
#endif

int Service::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->max_keep_alive > 0 && !--k)
			this->keep_alive = 0;
#endif

		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if (dispatch() || (this->fserveloop && this->fserveloop(this)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns__startModel(Service*);
static int serve_ns__endModel(Service*);
static int serve_ns__startBd(Service*);
static int serve_ns__endBd(Service*);

int Service::dispatch()
{	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns:startModel"))
		return serve_ns__startModel(this);
	if (!soap_match_tag(this, this->tag, "ns:endModel"))
		return serve_ns__endModel(this);
	if (!soap_match_tag(this, this->tag, "ns:startBd"))
		return serve_ns__startBd(this);
	if (!soap_match_tag(this, this->tag, "ns:endBd"))
		return serve_ns__endBd(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve_ns__startModel(Service *soap)
{	struct ns__startModel soap_tmp_ns__startModel;
	struct ns__startModelResponse soap_tmp_ns__startModelResponse;
	int soap_tmp_int;
	soap_default_ns__startModelResponse(soap, &soap_tmp_ns__startModelResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__startModelResponse.result = &soap_tmp_int;
	soap_default_ns__startModel(soap, &soap_tmp_ns__startModel);
	if (!soap_get_ns__startModel(soap, &soap_tmp_ns__startModel, "ns:startModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->startModel(soap_tmp_ns__startModelResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns__startModelResponse(soap, &soap_tmp_ns__startModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__startModelResponse(soap, &soap_tmp_ns__startModelResponse, "ns:startModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__startModelResponse(soap, &soap_tmp_ns__startModelResponse, "ns:startModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__endModel(Service *soap)
{	struct ns__endModel soap_tmp_ns__endModel;
	struct ns__endModelResponse soap_tmp_ns__endModelResponse;
	int soap_tmp_int;
	soap_default_ns__endModelResponse(soap, &soap_tmp_ns__endModelResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__endModelResponse.result = &soap_tmp_int;
	soap_default_ns__endModel(soap, &soap_tmp_ns__endModel);
	if (!soap_get_ns__endModel(soap, &soap_tmp_ns__endModel, "ns:endModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->endModel(soap_tmp_ns__endModelResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns__endModelResponse(soap, &soap_tmp_ns__endModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__endModelResponse(soap, &soap_tmp_ns__endModelResponse, "ns:endModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__endModelResponse(soap, &soap_tmp_ns__endModelResponse, "ns:endModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__startBd(Service *soap)
{	struct ns__startBd soap_tmp_ns__startBd;
	struct ns__startBdResponse soap_tmp_ns__startBdResponse;
	int soap_tmp_int;
	soap_default_ns__startBdResponse(soap, &soap_tmp_ns__startBdResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__startBdResponse.result = &soap_tmp_int;
	soap_default_ns__startBd(soap, &soap_tmp_ns__startBd);
	if (!soap_get_ns__startBd(soap, &soap_tmp_ns__startBd, "ns:startBd", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->startBd(soap_tmp_ns__startBdResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns__startBdResponse(soap, &soap_tmp_ns__startBdResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__startBdResponse(soap, &soap_tmp_ns__startBdResponse, "ns:startBdResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__startBdResponse(soap, &soap_tmp_ns__startBdResponse, "ns:startBdResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__endBd(Service *soap)
{	struct ns__endBd soap_tmp_ns__endBd;
	struct ns__endBdResponse soap_tmp_ns__endBdResponse;
	int soap_tmp_int;
	soap_default_ns__endBdResponse(soap, &soap_tmp_ns__endBdResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__endBdResponse.result = &soap_tmp_int;
	soap_default_ns__endBd(soap, &soap_tmp_ns__endBd);
	if (!soap_get_ns__endBd(soap, &soap_tmp_ns__endBd, "ns:endBd", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->endBd(soap_tmp_ns__endBdResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns__endBdResponse(soap, &soap_tmp_ns__endBdResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__endBdResponse(soap, &soap_tmp_ns__endBdResponse, "ns:endBdResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__endBdResponse(soap, &soap_tmp_ns__endBdResponse, "ns:endBdResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */