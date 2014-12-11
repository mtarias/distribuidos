/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "diccionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
diccionario_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int init_1_arg;
		data addword_1_arg;
		data verify_1_arg;
		data suggestword_1_arg;
		data readtext_1_arg;
		data show_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case init:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) init_1_svc;
		break;

	case addword:
		_xdr_argument = (xdrproc_t) xdr_data;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) addword_1_svc;
		break;

	case verify:
		_xdr_argument = (xdrproc_t) xdr_data;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) verify_1_svc;
		break;

	case suggestword:
		_xdr_argument = (xdrproc_t) xdr_data;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) suggestword_1_svc;
		break;

	case readtext:
		_xdr_argument = (xdrproc_t) xdr_data;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) readtext_1_svc;
		break;

	case show:
		_xdr_argument = (xdrproc_t) xdr_data;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) show_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (DICCIONARIO, DICCIONARIO_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, DICCIONARIO, DICCIONARIO_VERSION, diccionario_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DICCIONARIO, DICCIONARIO_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, DICCIONARIO, DICCIONARIO_VERSION, diccionario_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DICCIONARIO, DICCIONARIO_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
