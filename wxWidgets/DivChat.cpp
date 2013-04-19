#include "StdAfx.h"
#include "DivChat.h"
#define SOCKET int

//#pragma comment (lib,"Urlmon.lib")
//#pragma comment (lib,"Ws2_32.lib") 

DivChat::DivChat(const wxString& title) : wxFrame (NULL, wxID_ANY, title, wxDefaultPosition, wxSize(220, 530))
{
	wxPanel* panel=new wxPanel(this);
	wxButton* join=new wxButton(panel,ID_JOIN,"Unirse a sala",wxPoint(1,1),wxSize(100,50));
	wxButton* host=new wxButton(panel,ID_HOST,"Crear sala",wxPoint(101,1),wxSize(100,50));
	chat=new wxTextCtrl(panel,wxID_ANY,"",wxPoint(1,55),wxSize(200,400),wxTE_MULTILINE | wxTE_READONLY);
	delete wxLog::SetActiveTarget(new wxLogTextCtrl(chat));
	input=new wxTextCtrl(panel,wxID_ANY,"",wxPoint(5,460),wxSize(150,20),wxTE_RICH2);
	wxButton* enviar=new wxButton(panel,ID_ENVIAR,"OK",wxPoint(160,460),wxSize(40,30));
	chat->SetFocus();
	Connect(ID_HOST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DivChat::Servidor));
	Connect(ID_JOIN,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DivChat::Cliente));
	Connect(ID_ENVIAR, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DivChat::Enviar));
	online=false;
}


DivChat::~DivChat(void)
{
}
void DivChat::Servidor(wxCommandEvent& event)
{
#ifdef WIN32
	int tipoip=wxMessageBox("¿Deseas IPv6? En caso contrario se usará IPv4","Divel Network",wxYES_NO|wxCANCEL|wxICON_QUESTION);
	long aceptados=0;
	long posicion=0;
	amigos=1L;
	//amigos=wxGetNumberFromUser("¿Cuánta gente se va a conectar?","Introduce un número entre 1 y 10","DivChat",1L,1L,10L);
	if(tipoip==wxYES){
	char Buffer[4096], Hostname[NI_MAXHOST];
    char *Port = "6997"; //6996 es Azpazeta, 6997 es DivChat
	char* Address = NULL;
	int SocketType=SOCK_STREAM;
    int i, NumSocks, RetVal, FromLen, AmountRead;
    SOCKADDR_STORAGE From;
    WSADATA wsaData;
    ADDRINFO Hints, *AddrInfo, *AI;
    SOCKET ServSock[FD_SETSIZE];
    fd_set SockSet;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&Hints, 0, sizeof (Hints));
    Hints.ai_family = AF_UNSPEC;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
    RetVal = getaddrinfo(Address, Port, &Hints, &AddrInfo);
    if (RetVal != 0) {
        fprintf(stderr, "getaddrinfo failed with error %d: %s\n",
                RetVal, gai_strerror(RetVal));
        WSACleanup();
    }
	ServSock[i] = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
	bind(ServSock[i], AI->ai_addr, (int) AI->ai_addrlen);
	 if (SocketType == SOCK_STREAM) {
		 listen(ServSock[i],1);
	 }


	/*while(amigos!=aceptados){
		do{
			DIVCliente[posicion] = accept (ServSock[i], NULL, NULL);
		}while(DIVCliente[posicion]==SOCKET_ERROR);
		aceptados++;
		if(posicion==amigos)
			break;
		else
			posicion++;

	}*/
	 do{
			DIVCliente[0] = accept (ServSock[i], NULL, NULL);
		}while(DIVCliente[0]==SOCKET_ERROR);

	int aux;
	/*for(aux=0;aux!=amigos;aux++){
	send(DIVCliente[aux],dsversion,strlen(dsversion),0);
	}*/

	}else if(tipoip==wxNO){
	//IPv4-Servidor
			char Buffer[4096], Hostname[NI_MAXHOST];
    char *Port = "6997"; //6996 es Azpazeta, 6997 es DivChat
	char* Address = NULL;
	int SocketType=SOCK_STREAM;
    int i, NumSocks, RetVal, FromLen, AmountRead;
    SOCKADDR_STORAGE From;
    WSADATA wsaData;
    ADDRINFO Hints, *AddrInfo, *AI;
    SOCKET ServSock[FD_SETSIZE];
	
    fd_set SockSet;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&Hints, 0, sizeof (Hints));
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
    RetVal = getaddrinfo(Address, Port, &Hints, &AddrInfo);
    if (RetVal != 0) {
        fprintf(stderr, "getaddrinfo failed with error %d: %s\n",
                RetVal, gai_strerror(RetVal));
        WSACleanup();
    }
	ServSock[i] = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
	bind(ServSock[i], AI->ai_addr, (int) AI->ai_addrlen);
	 if (SocketType == SOCK_STREAM) {
		 listen(ServSock[i],1);
	 }


	while(amigos!=aceptados){
		do{
			DIVCliente[posicion] = accept (ServSock[i], NULL, NULL);
		}while(DIVCliente[posicion]==SOCKET_ERROR);
		aceptados++;
		if(posicion==amigos)
			break;
		else
			posicion++;

	}

	 	 
	int aux;
	/*for(aux=0;aux!=amigos;aux++){
	send(DIVCliente[aux],dsversion,1024,0);
	}*/


	
	
	}else{return;//Cancelar
	}
	//Tramo común de Servidor
	int aux;
	char* first="Todos conectados";
	/*for(aux=0;aux!=amigos;aux++){
	send(DIVCliente[aux],first,1024,0);
	}*/
	send(DIVCliente[0],first,1024,0);
	wxLogMessage("Todos conectados");
	int algo=0;
	int result=0;
	char buffer[1024];
	wxLogMessage("Iniciando chat...");
	recv(DIVCliente[0],buffer,1024,0);
	while(algo==0){
	//do{
	result=recv(DIVCliente[0],buffer,1024,0);
	//}while(result>0);
	wxLogMessage(buffer);
	wxString data=wxGetTextFromUser(wxString::Format("Contesta a:\n%s",buffer),"DivChat","");
	wxLogMessage(data);
	send(DIVCliente[0],data,1024,0);

	}
#else
#pragma comment "Linux IPv6"
	int maximo=2;
	fd_set descriptoresLectura;
	
	int numeroClientes; 
	
	char Cadena[2048];
	char nombreCliente1[1024];
	char nombreCliente2[1024];
	struct sockaddr_in6 Direccion;
	struct sockaddr Cliente;
	socklen_t Longitud_Cliente;
	struct servent *Puerto;
	//Direccion.sin6_len = sizeof(Direccion);
	DivServer=socket (AF_INET6, SOCK_STREAM, 0);
	Direccion.sin6_family = AF_INET6;
	Direccion.sin6_port = 6997;
	//Direccion.sin6_addr.s6_addr =INADDR_ANY;
	Direccion.sin6_addr=  in6addr_any;
	bind (DivServer, (struct sockaddr *)&Direccion, sizeof (Direccion));
	listen (DivServer, 1);
	Longitud_Cliente = sizeof (Cliente);
	DIVCliente[0] = accept (DivServer, &Cliente, &Longitud_Cliente);
	int aux;
	char* first="Todos conectados";
	send(DIVCliente[0],first,1024,0);
	wxLogMessage("Todos conectados");
	int algo=0;
	int result=0;
	char buffer[1024];
	wxLogMessage("Iniciando chat...");
	recv(DIVCliente[0],buffer,1024,0);
	while(algo==0){
	result=recv(DIVCliente[0],buffer,1024,0);
	wxLogMessage(buffer);
	wxString data=wxGetTextFromUser(wxString::Format("Contesta a:\n%s",buffer),"DivChat","");
	wxLogMessage(data);
	send(DIVCliente[0],data,1024,0);
	}

#endif




}

void DivChat::Cliente(wxCommandEvent& event)
{
#ifdef WIN32
	struct WSAData wsa;
	int tipoip=wxMessageBox("¿Deseas IPv6? En caso contrario se usará IPv4","Divel Network",wxYES_NO|wxCANCEL|wxICON_QUESTION);
	if(tipoip==wxYES){
	//IPv6-Cliente

	WSAStartup(MAKEWORD(2,0),&wsa);
	char Buffer[4096], AddrName[NI_MAXHOST];
	wxString ipnueva=wxGetTextFromUser("Introduce la IP","DivChat","::1");
	char ip[1024];
	strncpy(ip, (const char*)ipnueva.mb_str(wxConvUTF8), 1023);
    char *Server = ip;
    int Family = AF_UNSPEC;
    int SocketType = SOCK_STREAM;
    char *Port = "6997";

    WSADATA wsaData;

    int i, RetVal, AddrLen, AmountToSend;
    int ExtraBytes = 0;
    unsigned int Iteration, MaxIterations = 1;
    BOOL RunForever = FALSE;

    ADDRINFO Hints, *AddrInfo, *AI;
    struct sockaddr_storage Addr;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&Hints, 0, sizeof (Hints));
    Hints.ai_family = Family;
    Hints.ai_socktype = SocketType;
    RetVal = getaddrinfo(Server, Port, &Hints, &AddrInfo);
    if (RetVal != 0) {
        fprintf(stderr,
                "Cannot resolve address [%s] and port [%s], error %d: %s\n",
                Server, Port, RetVal, gai_strerror(RetVal));
        WSACleanup();
	}
	DivServer = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
	printf("Attempting to connect to: %s\n", Server ? Server : "localhost");
    connect(DivServer, AI->ai_addr, (int) AI->ai_addrlen);
		getnameinfo(AI->ai_addr, (int) AI->ai_addrlen, AddrName,sizeof (AddrName), NULL, 0, NI_NUMERICHOST);
		printf("Conexion establecida");
		
	
	
	}else if(tipoip==wxNO){
	//IPv4-Cliente
	wxString ipnueva=wxGetTextFromUser("Introduce la IP","DivChat","127.0.0.1");
	char ip[1024];
	strncpy(ip, (const char*)ipnueva.mb_str(wxConvUTF8), 1023);
    char *Server = ip;
	char Buffer[4096], AddrName[NI_MAXHOST];
	int Family = AF_INET;
    int SocketType = SOCK_STREAM;
    char *Port = "6997";
	WSAStartup(MAKEWORD(2,0),&wsa);
	 int i, RetVal, AddrLen, AmountToSend;
    int ExtraBytes = 0;
    unsigned int Iteration, MaxIterations = 1;
    BOOL RunForever = FALSE;

    ADDRINFO Hints, *AddrInfo, *AI;
    SOCKET DivServer = INVALID_SOCKET;
    struct sockaddr_storage Addr;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&Hints, 0, sizeof (Hints));
    Hints.ai_family = Family;
    Hints.ai_socktype = SocketType;
    RetVal = getaddrinfo(Server, Port, &Hints, &AddrInfo);
    if (RetVal != 0) {
        fprintf(stderr,
                "Cannot resolve address [%s] and port [%s], error %d: %s\n",
                Server, Port, RetVal, gai_strerror(RetVal));
        WSACleanup();
	}
	DivServer = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
	printf("Attempting to connect to: %s\n", Server ? Server : "localhost");
    connect(DivServer, AI->ai_addr, (int) AI->ai_addrlen);
		getnameinfo(AI->ai_addr, (int) AI->ai_addrlen, AddrName,sizeof (AddrName), NULL, 0, NI_NUMERICHOST);
		printf("Conexion establecida");
	
	}else{
		return;
	//Cancelar
	}
	//Tramo común del Cliente
	char first[1024];
	int estilo=0;
	//do{
	estilo=recv(DivServer,first,1023,0);
	//}while(estilo!=-1);
	wxLogMessage(first); //Todos conectados
	online=true;
	int algo=0;
	int result=0;
	char buffer[1024];
	
	send(DivServer,"Estoy conectado",1024,0);
	
	wxLogMessage("Estoy conectado");
	while(algo==0){
	
	//do{
	result=recv(DivServer,buffer,1024,0);
	//}while(result>0);
	wxLogMessage(buffer);
	wxString data=wxGetTextFromUser(wxString::Format("Contesta a:\n%s",buffer),"DivChat","");
	wxLogMessage(data);
	send(DivServer,data,1024,0);
	}
#else
#pragma comment "Linux IPv6 Cliente"
	char Cadena[1024];
	char ip[1024];
	char nombreCliente1[1024];
	char nombreCliente2[1024];
	wxString wxip=wxGetTextFromUser("Introduce la IPv6 del server de Azpazeta","Divel Network","::1");	
	strncpy(ip, (const char*)wxip.mb_str(wxConvUTF8), 1023);
	struct sockaddr_in6 Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	inet_pton(PF_INET6, ip,&(Direccion.sin6_addr));
	Direccion.sin6_family = AF_INET6;
	Direccion.sin6_port = 6997;
	int DivServer = socket (AF_INET6, SOCK_STREAM, 0);
	connect (DivServer, (struct sockaddr *)&Direccion, sizeof (Direccion));
	char first[1024];
	int estilo=0;
	estilo=recv(DivServer,first,1023,0);
	wxLogMessage(first); //Todos conectados
	online=true;
	int algo=0;
	int result=0;
	char buffer[1024];
	
	send(DivServer,"Estoy conectado",1024,0);
	
	wxLogMessage("Estoy conectado");
	while(algo==0){
	result=recv(DivServer,buffer,1024,0);

	wxLogMessage(buffer);
	wxString data=wxGetTextFromUser(wxString::Format("Contesta a:\n%s",buffer),"DivChat","");
	wxLogMessage(data);
	send(DivServer,data,1024,0);
	}

#endif

}

void DivChat::Enviar(wxCommandEvent& event)
{
	#ifdef WIN32
	if(online==false){wxMessageBox("Antes conéctate a una sala","DivChat",wxICON_ERROR|wxOK);}else{
	//Enviar mensaje
	send(DivServer,input->GetValue(),strlen(input->GetValue()),0);
	//Obtener respuestas
	char* respuesta;
	recv(DivServer,respuesta,1024,0);
	wxLogMessage(respuesta);
	

	
	
	}
	#endif
}
