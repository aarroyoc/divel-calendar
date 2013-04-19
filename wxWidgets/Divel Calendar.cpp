// Divel Calendar.cpp: define el punto de entrada de la aplicación.
//

#include "StdAfx.h"
#include "Divel Calendar.h"
#include "Calendario.h"


bool DivCalendar::OnInit()
{
	this->SetAppName("Divel Calendar");
	this->SetVendorName("Adrian Arroyo Calle");
	icono=new wxTaskBarIcon();
	//icono->SetIcon(wxICON(ICONOCAL),"Divel Calendar está presente en el sistema");
    Calendario *frame = new Calendario( "Hello World", wxPoint(50,50), wxSize(450,340) );
    frame->Show( true );
    SetTopWindow( frame );
	icono->Destroy();
    return true;
}
int DivCalendar::OnExit()
{
	
	return 0;
}

IMPLEMENT_APP(DivCalendar)


