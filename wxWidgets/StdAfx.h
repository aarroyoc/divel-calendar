// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows

#ifdef WIN32
// Archivos de encabezado de Windows:
	#include <ws2tcpip.h>
	#include <WinSock2.h>
	#include <windows.h>
#else
//Archivos UNIX/LINUX
    #include <pthread.h>
    #include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#endif
// wxWidgets
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/aboutdlg.h>
#include <wx/fontdlg.h>
#include <wx/fontpicker.h>
#include <wx/dcbuffer.h>
#include <wx/calctrl.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include <wx/numdlg.h>
#include <wx/taskbar.h>
#include <wx/datetime.h>
#include <wx/thread.h>
//Clases
#include "Calendario.h"
#include "Divel Calendar.h"
#include "AddEvent.h"
#include "DivChat.h"
// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
//Archivo de C++
#include <iostream>
#include <fstream>
using namespace std;


// TODO: mencionar aquí los encabezados adicionales que el programa necesita
