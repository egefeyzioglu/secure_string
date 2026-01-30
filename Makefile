all: securestring

securestring: main.c
	gcc main.c -o securestring -O3

install: all
	cp securestring /usr/bin/securestring
	ln -s /usr/bin/securestring /usr/bin/sstring

uninstall:
	rm -f /usr/bin/securestring /usr/bin/sstring

clean:
	rm -f secure_string

.PHONY: all clean install uninstall
