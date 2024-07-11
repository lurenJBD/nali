include config.mak

all: nali.c libqqwry/qqwry.c
	gcc -o bin/nali nali.c libqqwry/qqwry.c

install: bin share
	install bin/nali $(DESTDIR)$(bindir)
	install bin/nali-update $(DESTDIR)$(bindir)
	install share/qqwry.dat $(DESTDIR)$(datadir)

uninstall:
	rm -f $(DESTDIR)$(bindir)/nali
	rm -f $(DESTDIR)$(bindir)/nali-update
	rm -f $(DESTDIR)$(datadir)/qqwry.dat

distclean: clean
	rm -f config.mak
	rm -f config.h

clean:
	rm -f bin/nali
	rm -f bin/nali-update
