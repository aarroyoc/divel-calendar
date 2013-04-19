#include "StdAfx.h"




BEGIN_EVENT_TABLE(Calendario, wxFrame)
    EVT_MENU(ID_Quit,  Calendario::OnQuit)
    EVT_MENU(ID_About, Calendario::OnAbout)
	EVT_MENU(ID_ADDEVT, Calendario::CrearEvento)
	EVT_MENU(ID_ADDREC, Calendario::CrearRecordatorio)
	EVT_MENU(ID_OPT, Calendario::Options)
	EVT_MENU(ID_CHAT, Calendario::DivelChat)
	EVT_MOTION(Calendario::Movimiento)
	EVT_CALENDAR(ID_CAL, Calendario::SeleccionarDia)
END_EVENT_TABLE()

Calendario::Calendario(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	
	//SetIcon(wxICON(ICONOCAL));
    wxMenu *archivo = new wxMenu;
	wxMenu* ventana=new wxMenu;
	wxMenu* ayuda=new wxMenu;
	this->SetTitle("Divel Calendar");
	this->SetSize(800,600);
	
    ayuda->Append(ID_OPT, "Configuracion","Ajuste las configuraciones");
	ayuda->Append( ID_About, "&Acerca" );
	
	archivo->Append(ID_ADDEVT, "&Anadir evento");
	archivo->Append(ID_ADDREC, "A&nadir recordatorio");
    //archivo->AppendSeparator();
	//archivo->Append(ID_OPEN, "A&brir calendario");
	//archivo->Append(ID_SAVE, "&Guardar calendario");
	archivo->AppendSeparator();
    archivo->Append( ID_Quit, "&Salir" );
	ventana->Append(ID_CHAT,"&DivChat","Abre la ventana de chat");
	//ventana->Append(ID_EVENTS, "D&ivelEvents","Abre la ventana de eventos Divel");
	//ventana->Append(ID_NOTES, "Divel &Notes","Abre la ventana de apuntes");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( archivo, "&Archivo" );
	menuBar->Append(ventana,"&Ventana");
	menuBar->Append(ayuda,"A&yuda");
    SetMenuBar( menuBar );
	//Crear Frame principal
	wxInitAllImageHandlers();
	
	wxString appdata=getenv("HOME");
	if(wxDirExists(appdata+"/Divel/Calendar")==false)
	{
	
		wxMkdir(appdata+"/Divel");
		wxMkdir(appdata+"/Divel/Calendar");
		//wxCopyFile("./conf.cfg",appdata+"\\Divel\\Calendar\\conf.cfg");
	
	
	}else if(wxFileExists(appdata+"/Divel/Calendar/conf.cfg")==true){
		int fuente=0, color=0,posicion=0,premium=0;
		wxString situacionconf=appdata+"/Divel/Calendar/conf.cfg";
		ifstream configfile(situacionconf.mb_str(),ifstream::in);
		if(configfile.good())
		{

			char buffer;
			buffer=configfile.get();
			wxString conffile=buffer;
			while(!configfile.eof())
			{
				buffer=configfile.get();

				if(buffer=='1'){
					printf("Uno detectado");
				switch(posicion){
				case 0: {fondo=1;posicion++;}break;
				case 1: {fuente=1;posicion++;}break;
				case 2: {color=1;posicion++;}break;
				case 3: {premium=1;posicion++;}break;

				}}
				if(buffer=='0'){
					printf("Cero detectado");
				posicion++;
				}
				conffile+=buffer;
			}
			configfile.close();
			
		}
		
		if(fondo==1){
	
		}
		if(premium==1){
			wxMessageBox("Bienvenido usuario premium");
		}
	
	}
	
	panel=new wxPanel(this);
	panel->SetBackgroundColour(wxColour("white"));
	calendar=new wxPanel(panel,1,1,600,400);
	//calendar->SetBackgroundColour(wxColour("red"));
	calendar->Connect(wxEVT_PAINT,wxPaintEventHandler(Calendario::Paint));


	/*this->SetFont(wxFont(14,1,1,3,true));
	this->SetFont(wxFont(12,2,1,3,true));
	panel->SetFont(wxFont(12,3,1,3,true));*/
	//wxFontPickerCtrl* fuentedlg=new wxFontPickerCtrl(panel,wxID_ANY,wxNullFont,wxPoint(-1,-1));


	//Sistema de fuentes
	/*
	wxFontDialog* fuente=new wxFontDialog();
	fuente->ShowModal();
	wxFontData mifuente=fuente->GetFontData();
	wxFont lafuente=mifuente.GetChosenFont();
	panel->SetFont(lafuente);
	this->SetFont(lafuente);
	*/
	if(fondo==1){
	wxBitmap fondo(appdata+"/Divel/Calendar/fondo.png",wxBITMAP_TYPE_PNG);
	wxStaticBitmap* fonpantalla=new wxStaticBitmap(panel,wxID_ANY,fondo,wxDefaultPosition,wxDefaultSize);
	}
	wxButton* anadirevt=new wxButton(panel,ID_ADDEVT,"Anadir evento",wxPoint(610,20),wxSize(150,50));
	wxButton* anadirrec=new wxButton(panel,ID_ADDREC,"Anadir recordatorio",wxPoint(610,80),wxSize(150,50));
	wxButton* del=new wxButton(panel,ID_DELETE,"Borrar evento",wxPoint(610,140),wxSize(150,50));
	wxButton* ver=new wxButton(panel,ID_VER,"Ver evento",wxPoint(610,200),wxSize(150,50));
	wxButton* divchat=new wxButton(panel,ID_CHAT,"DivChat",wxPoint(610,260),wxSize(150,50));
	desc=new wxStaticText(panel,wxID_ANY,"Ningun evento seleccionado",wxPoint(1,410));
	//wxPanel* calendar=new wxPanel(panel,-1,-1,600,400);
	/*wxMemoryDC* memoria=new wxMemoryDC;
	wxClientDC calendario(panel);
	//memoria->DrawCircle(wxPoint(1,1),wxCoord(32));
	//calendario.Blit(wxPoint(-1,-1),wxSize(600,400),memoria,wxPoint(-1,-1));
	calendario.DrawCircle(wxPoint(1,1),wxCoord(32));*/
	wxCalendarCtrl* calendarctrl=new wxCalendarCtrl(calendar,ID_CAL,wxDefaultDateTime,wxPoint(1,1),wxSize(600,400),wxCAL_MONDAY_FIRST);
	Connect(ID_ADDEVT, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Calendario::CrearEvento));
	Connect(ID_ADDREC, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Calendario::CrearRecordatorio));
	Connect(ID_VER, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Calendario::VerEvento));
	Connect(ID_DELETE, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Calendario::BorrarEvento));
	Connect(ID_CHAT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Calendario::DivelChat));

    CreateStatusBar();
    SetStatusText( "Bienvenido a Divel Calendar" );
}


void Calendario::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	int salir=wxMessageBox("Deseas salir?","Confirmar -- Divel Calendar",wxICON_QUESTION|wxYES_NO);
	if(salir==wxYES){
    Close( true );
	}
}


void Calendario::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxBell();
   wxAboutDialogInfo info;
   info.AddDeveloper("Adrian Arroyo Calle");
   info.AddDeveloper("Microsoft Visual Studio 2010");
   info.AddDeveloper("wxWidgets 2.9.3");
   info.AddDeveloper("GNU C++ Compiler");
   info.SetCopyright("(C) Adrián Arroyo Calle 2012");
   info.SetDescription("Divel Calendar es el programa para organizar eventos, seguir eventos, hablar con gente, hacer listas y seguir sitios web");
   info.SetName("Divel Calendar");
   info.SetVersion("1.0");
   info.SetWebSite("http://sites.google.com/site/divelmedia");
   //info.SetIcon(wxICON("Divel Calendar.ico"));
   wxAboutBox(info);
   wxClientDC dc(this);
   Render(dc);
   wxBell();

	
	
	 
   //GUID {917BDFD2-0425-45D6-A495-5AA24EFD2C03}
}

void Calendario::Movimiento(wxMouseEvent& event)
{
	if (event.Dragging())
    {
        wxClientDC dc(this);
        wxPen pen(*wxRED, 1); // red pen of width 1
        dc.SetPen(pen);
        dc.DrawPoint(event.GetPosition());
        dc.SetPen(wxNullPen);
    }
}

void Calendario::Paint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	Render(dc);
}
void Calendario::Render(wxDC& dc)
{
	if(fondo==1){
	wxString appdata=getenv("HOME");
	wxString rutapng=appdata+"/Divel/Calendar/fondo.png";
	wxBitmap fondo(rutapng,wxBITMAP_TYPE_PNG);
	dc.DrawText("Cargando fondo de pantalla...",wxPoint(610,400));
	dc.DrawBitmap(fondo,wxPoint(1,1));
	}

}


void Calendario::SeleccionarDia(wxCalendarEvent& event)
{
	wxDateTime dia=event.GetDate();
	diadelmes=dia.GetDayOfYear();
	mes=dia.GetMonth();
	ano=dia.GetYear();
	
	//wxMessageBox(wxString::Format("Dia seleccionado %d del %d",eventodia,ano));
	SeleccionarEventos(diadelmes,(int)mes,ano);
}
void Calendario::SeleccionarEventos(short unsigned int dia,int elmes,int ano)
{
	//Abril, Junio, Septiembre, Noviembre
	//Sucesión completa 31-28-31-30-31-30-31-31-30-31-30-31
	switch(elmes){
	case 0:break;
	case 1: dia=dia-31;break;
	case 2: dia=dia-28-31;break;
	case 3: dia=dia-28-31-30-1;break; //Abril
	case 4: dia=dia-28-31-30-31;break;
	case 5: dia=dia-28-31-30-31-30-1;break; //Junio
	case 6: dia=dia-28-31-30-31-30-31;break;//Sucesión completa 31-28-31-30-31-30-31-31-30-31-30-31
	case 7: dia=dia-28-31-30-31-30-31-31;break;
	case 8: dia=dia-28-31-30-31-30-31-31-30-1;break;//Septiembre
	case 9: dia=dia-28-31-30-31-30-31-31-30-31;break;
	case 10: dia=dia-28-31-30-31-30-31-31-30-31-30-1;break;//Noviembre
	case 11: dia=dia-28-31-30-31-30-31-31-30-31-30-31;break;
								
	}
	if((ano%4==0 && (ano%400==0 || ano%100!=0))&& mes>1)
	{
		dia-=1;
	}

	//Sucesión completa 31-28-31-30-31-30-31-31-30-31-30-31
	//Comprobar eventos
	wxString appdata=getenv("HOME");
	wxString pathdiario=wxString::Format("%s/Divel/Calendar/%d/%d/%d",appdata,ano,mes,dia);
	if(wxFileExists(pathdiario)==false){
	desc->SetLabel(wxString::Format("Ningun evento para el dia %d de %d del %d",dia,elmes,ano));
	
	
	}else{
		int lectura=0;
		char eventolinea[4096][2];
		wxString myevento[4];
		char buffer;
		bool leyendoeventos=false;
		int bucle=0;

		ifstream file(pathdiario.mb_str(),ifstream::in);
		while(file.is_open() && file.good() && file.eof()==false){

			if(leyendoeventos==false){
				if(file.get()==':' && file.get()==' '){leyendoeventos=true;}

			}else{
				buffer=file.get();
				if(buffer!='~'){
					if(buffer=='\n' && file.get()=='E'){
					wxMessageBox("Hay mas de un evento, solo se mostrara el primero en la vista general");
					break;
					
					}else{
						myevento[lectura]+=buffer;}
					}else{lectura++;}
	
	
	}
			
	}
	desc->SetLabel(wxString::Format("Titulo: %s\nFecha: %d/%d/%d\nLugar: %s\nDuracion: %s\nComentario: %s",myevento[0],dia,elmes,ano,myevento[1],myevento[2],myevento[3]));
	
	}
	
}
void Calendario::CrearEvento(wxCommandEvent& event)
{
	AddEvent* agregarevento=new AddEvent("Agregar Evento",diadelmes,mes,ano);
	agregarevento->ano=ano;
	agregarevento->mes=mes;
	agregarevento->diadelano=diadelmes;
	agregarevento->ShowModal();
	agregarevento->Destroy();


	//Pasar al diálogo nuevo de creación
	/*if(ano<0 || ano>5000){
	ano=wxGetNumberFromUser("Introduce al año del evento","Escribe el número","Divel Calendar",0L,0L,5000L);
	diadelano=wxGetNumberFromUser("Introduce el día del evento","Escribe el número","Divel Calendar",0L,0L,366L);
	
	
	}
	
	wxString appdata=getenv("appdata");
	wxString pathanual=wxString::Format("%s\\Divel\\Calendar\\%d",appdata,ano);
	if(wxDirExists(pathanual)==false)
	{
		wxMkdir(pathanual);
	}
	wxString pathdiario=wxString::Format("%s\\%d",pathanual,diadelano);
	if(wxFileExists(pathdiario)==false)
	{
		//Crear fichero nuevo
		ofstream diafile(pathdiario.mb_str(),ofstream::app);
		if(diafile.is_open() && diafile.good())
		{
			char* cabecera="DivelCalendar:DiaFile\n";
			int tamano=strlen(cabecera);
			//strlen para tamaño de caracteres, sizeof tamaño de memoria
			diafile.write(cabecera,tamano);
			diafile.close();
		}



	}
		//Añadir al fichero
	  ofstream diafile(pathdiario.mb_str(),ofstream::app);
	  if(diafile.is_open() && diafile.good())
	  {
		  
	  }*/
	

}

void Calendario::CrearRecordatorio(wxCommandEvent& event)
{
	long minutos=wxGetNumberFromUser("Escribe los minutos","Introduce los minutos","Divel Calendar",1L,1L);
	sleep(minutos*60*1000);
	wxMessageBox("Tiempo acabado","Divel Calendar",wxICON_INFORMATION|wxOK);


}
void Calendario::VerEvento(wxCommandEvent& event)
{
	switch(mes){
	case 0:break;
	case 1: diadelmes=diadelmes-31;break;
	case 2: diadelmes=diadelmes-28-31;break;
	case 3: diadelmes=diadelmes-28-31-30-1;break; //Abril
	case 4: diadelmes=diadelmes-28-31-30-31;break;
	case 5: diadelmes=diadelmes-28-31-30-31-30-1;break; //Junio
	case 6: diadelmes=diadelmes-28-31-30-31-30-31;break;//Sucesión completa 31-28-31-30-31-30-31-31-30-31-30-31
	case 7: diadelmes=diadelmes-28-31-30-31-30-31-31;break;
	case 8: diadelmes=diadelmes-28-31-30-31-30-31-31-30-1;break;//Septiembre
	case 9: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31;break;
	case 10: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31-30-1;break;//Noviembre
	case 11: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31-30-31;break;
								
	}
	if((ano%4==0 && (ano%400==0 || ano%100!=0))&& mes>1)
	{
		diadelmes-=1;
	}
	if(ano<0 || ano>5000)
	{
		wxMessageBox("Selecciona antes una fecha","Divel Calendar",wxICON_WARNING|wxOK);

	}else{
	wxString appdata=getenv("HOME");
	wxString pathdiario=wxString::Format("%s/Divel/Calendar/%d/%d/%d",appdata,ano,mes,diadelmes);
	if(wxFileExists(pathdiario)==false){
	desc->SetLabel(wxString::Format("Ningun evento para el dia %d de %d del %d",diadelmes,mes,ano));
	
	
	}else{
		int lectura=0;
		char eventolinea[4096][2];
		wxString myevento[100][4];
		char buffer;
		bool leyendoeventos=false;
		int bucle=0;
		int linea=0;

		ifstream file(pathdiario.mb_str(),ifstream::in);
		while(file.is_open() && file.good() && file.eof()==false){

			if(leyendoeventos==false){
				if(file.get()==':' && file.get()==' '){leyendoeventos=true;}

				}else{
					buffer=file.get();
						if(buffer!='~'){
							if(buffer=='\n' && file.get()=='E'){
								linea++;
								lectura=0;
								leyendoeventos=false;
							}else{
								myevento[linea][lectura]+=buffer;}
						}else{lectura++;}
	
	
	}
			
	}
		int aux;
		for(aux=linea;aux!=0;aux--){
	wxMessageBox(wxString::Format("Titulo: %s\nFecha: %d/%d/%d\nLugar: %s\nDuracion: %s\nComentario: %s",myevento[aux][0],diadelmes,mes,ano,myevento[aux][1],myevento[aux][2],myevento[aux][3]),"Divel Calendar",wxICON_INFORMATION|wxOK);
		}
	}
	
	
	
	
	
	
	
	
	}

}

void Calendario::BorrarEvento(wxCommandEvent& event)
{
		switch(mes){
	case 0:break;
	case 1: diadelmes=diadelmes-31;break;
	case 2: diadelmes=diadelmes-28-31;break;
	case 3: diadelmes=diadelmes-28-31-30-1;break; //Abril
	case 4: diadelmes=diadelmes-28-31-30-31;break;
	case 5: diadelmes=diadelmes-28-31-30-31-30-1;break; //Junio
	case 6: diadelmes=diadelmes-28-31-30-31-30-31;break;//Sucesión completa 31-28-31-30-31-30-31-31-30-31-30-31
	case 7: diadelmes=diadelmes-28-31-30-31-30-31-31;break;
	case 8: diadelmes=diadelmes-28-31-30-31-30-31-31-30-1;break;//Septiembre
	case 9: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31;break;
	case 10: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31-30-1;break;//Noviembre
	case 11: diadelmes=diadelmes-28-31-30-31-30-31-31-30-31-30-31;break;
								
	}
	if((ano%4==0 && (ano%400==0 || ano%100!=0))&& mes>1)
	{
		diadelmes-=1;
	}
	if(ano<0 || ano>5000){
	wxMessageBox("Seleccione una fecha","Divel Calendar",wxICON_WARNING|wxOK);
	
	}else if(wxFileExists(wxString::Format("%s/Divel/Calendar/%d/%d/%d",getenv("HOME"),ano,mes,diadelmes))==true){
	int respuesta=wxMessageBox(wxString::Format("Seguro que quieres borrar todos los eventos del %d/%d/%d?",diadelmes,mes,ano),"Divel Calendar",wxICON_QUESTION|wxYES_NO);
	if(respuesta==wxYES){
		wxString appdata=getenv("HOME");
		wxString path=wxString::Format("%s/Divel/Calendar/%d/%d/%d",appdata,ano,mes,diadelmes);
	wxRemoveFile(path);
	
	
	
	}
	
	
	
	
	}

}

void Calendario::Options(wxCommandEvent& event)
{
#ifdef WIN32
	wxShell(wxString::Format("%s\\Divel\\Calendar\\conf.cfg",getenv("appdata"))); //GEDIT en LINUX
#else
	wxShell(wxString::Format("gedit %s/Divel/Calendar/conf.cfg",getenv("HOME")));
#endif WIN32
}

void Calendario::DivelChat(wxCommandEvent& event)
{
	DivChat* dchat=new DivChat("DivChat");
	dchat->Show();
	
}
