# Copyright (c) 2014 Cesanta Software
# All rights reserved

PROG = server
CFLAGS = -W -Wall -I -pthread -g -O0 $(CFLAGS_EXTRA)
SOURCES = $(PROG).cpp mongoose.c

$(PROG): $(SOURCES)
	g++ -o $(PROG) $(SOURCES) $(CFLAGS)

clean:
	rm -rf $(PROG) *.exe *.dSYM *.obj *.exp .*o *.lib
