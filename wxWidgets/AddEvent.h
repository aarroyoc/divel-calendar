#ifndef ADDEVENT_H
#define ADDEVENT_H
#include "StdAfx.h"
class AddEvent :
	public wxDialog
{
public:
	AddEvent(const wxString& title,int diadelano2,int mes2,int ano2);
	virtual ~AddEvent(void);
	void Cancelar(wxCommandEvent& event);
	void OK(wxCommandEvent& event);
	int ano;
	int mes;
	int diadelano;
private:
	
	wxStaticText* idia;
	wxTextCtrl* comentario;
	wxTextCtrl* titulo;
	wxTextCtrl* lugar;
	wxTextCtrl* duracion;
};
#endif
