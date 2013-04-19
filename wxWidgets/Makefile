#Makefile de Divel Calendar

CC = g++
CFLAGS = `wx-config --cppflags`
PRE = -DIDIOMA=ES -DLINUX
OBJ = AddEvent.o Calendario.o DivChat.o StdAfx.o DivelCalendar.o
EXIT = DivelCalendar
LIBFLAGS = `wx-config --libs`

all: $(OBJ)
	$(CC) -o $(EXIT) $(OBJ) $(LIBFLAGS)
AddEvent.o:
	$(CC) -o AddEvent.o -c AddEvent.cpp $(CFLAGS)
Calendario.o:
	$(CC) -o Calendario.o -c Calendario.cpp $(CFLAGS)
DivChat.o:
	$(CC) -o DivChat.o -c DivChat.cpp $(CFLAGS)
StdAfx.o:
	$(CC) -o StdAfx.o -c StdAfx.cpp $(CFLAGS)
DivelCalendar.o:
	$(CC) -o DivelCalendar.o -c "Divel Calendar.cpp" $(CFLAGS)


clean:
	$(RM) $(OBJ)
