# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include src/config.mk

SRC = src/drw.c src/dwm.c src/util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

src/.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: src/config.h src/config.mk

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f src/dwm ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm

ansible-diff:
	@[[ $$(sha256sum $$(which dwm) ./dwm | awk '{ print $$1 }' | uniq | wc -l) -ne 1 ]] && echo ANSIBLE_CHANGED_TRUE; true

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm

.PHONY: all options clean dist install uninstall
