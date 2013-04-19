#include "StdAfx.h"
#ifndef CALENDARIO_H
#define CALENDARIO_H

class Calendario: public wxFrame
{
public:
    Calendario(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void Movimiento(wxMouseEvent& event);
	void Paint(wxPaintEvent& event);
	void Render(wxDC& dc);
	void SeleccionarDia(wxCalendarEvent& event);
	void SeleccionarEventos(short unsigned int dia,int elmes,int ano);
	void CrearEvento(wxCommandEvent& event);
	void CrearRecordatorio(wxCommandEvent& event);
	void Guardar(wxCommandEvent& event);
	void ObtenerRSS(wxTimerEvent& event);
	void VerEvento(wxCommandEvent& event);
	void BorrarEvento(wxCommandEvent& event);
	void Options(wxCommandEvent& event);
	void NuevoRSS(wxCommandEvent& event);
	void DivelChat(wxCommandEvent& event);
	void DivEvents(wxCommandEvent& event);
	void DivNotes(wxCommandEvent& event);

private:
	wxPanel* panel;
	wxPanel* calendar;
	wxStaticText* desc;
	int fondo;
	unsigned short diadelmes;
	int ano;
	int mes;
    DECLARE_EVENT_TABLE()
};

#endif
