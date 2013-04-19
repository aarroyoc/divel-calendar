//#pragma once
//GUID {917BDFD2-0425-45D6-A495-5AA24EFD2C03}
//#include "resource.h"
#ifndef DIVCALENDAR_H
#define DIVCALENDAR_H

class DivCalendar: public wxApp
{
    virtual bool OnInit();
	virtual int OnExit();
private:
	wxTaskBarIcon* icono;
};






enum
{
    ID_Quit = 1,
    ID_About,
	ID_ADDEVT,
	ID_ADDEVTOK,
	ID_ADDEVTCANCEL,
	ID_ADDREC,
	ID_SAVE,
	ID_OPEN,
	ID_CHAT,
	ID_EVENTS,
	ID_NOTES,
	ID_PICKUPCAL,
	ID_EDIT,
	ID_DELETE,
	ID_SHARE,
	ID_ADDRSS,
	ID_OPT,
	ID_CAL,
	ID_VER,
	ID_JOIN,
	ID_HOST,
	ID_ENVIAR,
};



#endif
