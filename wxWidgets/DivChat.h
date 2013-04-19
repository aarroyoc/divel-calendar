#include "StdAfx.h"
#ifndef DIVCHAT_H
#define DIVCHAT_H
#define SOCKET int


class DivChat : public wxFrame
{
public:
	DivChat(const wxString& title);
	~DivChat(void);
	void Servidor(wxCommandEvent& event);
	void Cliente(wxCommandEvent& event);
	void Enviar(wxCommandEvent& event);
private:
	wxTextCtrl* chat;
	wxTextCtrl* input;
	bool online;
	SOCKET DivServer;
	SOCKET DIVCliente[10];
	long amigos;
};

#endif
