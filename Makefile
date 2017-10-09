# Makefile.  Generated from Makefile.in by configure.

wilprefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin

CC = gcc
srcdir = .

HOST= x86_64-unknown-cygwin


DARWIN_CORE = $(if $(findstring apple-darwin,$(HOST)),/System/Library/Frameworks/CoreServices.framework/CoreServices,)

WFLAGS = -Wmissing-prototypes -Wunused -Wimplicit -Wreturn-type -Wparentheses -pedantic
CFLAGS = -g $(WFLAGS)
FONDUOBJS = fondu.o readnfnt.o fondups.o
UFONDOBJS = ufond.o ufondbdf.o ufondpfb.o ufondttf.o crctab.o
DFONT2RESOBJS = dfont2res.o crctab.o
SHOWOBJS = showfond.o
TOBINOBJS = tomacbinary.o crctab.o
FROMBINOBJS = frommacbinary.o
LUMPEROBJS = lumper.o
SETFONDNAMEOBJS = setfondname.o

all: fondu ufond showfond dfont2res tobin frombin lumper setfondname

fondu: $(FONDUOBJS)
	$(CC) $(CFLAGS) -o fondu $(FONDUOBJS) -lm $(DARWIN_CORE)


ufond: $(UFONDOBJS)
	$(CC) $(CFLAGS) -o ufond $(UFONDOBJS)

showfond: $(SHOWOBJS)
	$(CC) $(CFLAGS) -o showfond $(SHOWOBJS) $(DARWIN_CORE)

dfont2res: $(DFONT2RESOBJS)
	$(CC) $(CFLAGS) -o dfont2res $(DFONT2RESOBJS)

tobin: $(TOBINOBJS)
	$(CC) $(CFLAGS) -o tobin $(TOBINOBJS) $(DARWIN_CORE)

frombin: $(FROMBINOBJS)
	$(CC) $(CFLAGS) -o frombin $(FROMBINOBJS) $(DARWIN_CORE)

lumper: $(LUMPEROBJS)
	$(CC) $(CFLAGS) -o lumper $(LUMPEROBJS)

setfondname: $(SETFONDNAMEOBJS)
	$(CC) $(CFLAGS) -o setfondname $(SETFONDNAMEOBJS)

clean:
	-rm -f *.o fondu ufond showfond dfont2res tobin frombin lumper setfondname

distclean: clean
	-rm Makefile

install: all
	mkdir -p $(DESTDIR)$(bindir)
	cp fondu ufond showfond dfont2res tobin frombin lumper setfondname $(DESTDIR)$(bindir)


VERSION:=$(shell date +"%y%d%m")
DISTNAME=fondu-$(VERSION)
DISTFILES=$(wildcard *.c *.1 *.h) README Makefile.in configure.in configure \
	LICENSE install-sh config.sub config.guess


dist:
	mkdir $(DISTNAME)
	ln $(DISTFILES) $(DISTNAME)/
	tar cfz $(DISTNAME).tar.gz $(DISTNAME) 
	rm -fr $(DISTNAME)

Makefile: Makefile.in
	chmod +w $@
	./config.status
	chmod -w $@


