SHELL=sh
GENERATED=generated
BUILD=build
CC=gcc
CCFLAGS=-g -O0 -fPIC #-Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

NAME=$(notdir $(realpath $(dir $MAKEFILE)))
VERSION=$(shell { git describe --tags --match='[0-9]*\.[0-9]*' --dirty=+ 2>/dev/null || echo g$$(git describe --always --dirty=+); } | sed 's@.*/@@')

LIB=${BUILD}/${NAME}-${VERSION}.so
HDR=$(shell find api -type f -name \*.h) ${GEN}
SRC=$(shell find src -type f -name \*.c)

HDR_O=$(addprefix ${BUILD}/,$(patsubst %.h,%.h.o,${HDR}))
SRC_O=$(addprefix ${BUILD}/,$(patsubst %.c,%.o,${SRC}))

$(info Build ${NAME} ${VERSION})

.PHONY: check all lib clean debug generator

all: check #lib

lib: ${LIB}

check: ${BUILD}/test/lang
	@for procedure in $^; do ./$$procedure || exit 1; done

clean:
	rm -rf build ${GENERATED}

debug:
	$(eval CCFLAGS=${CCFLAGS} -DAETEN_DEBUG)

generator:
	./generator/export
	./generator/for-each-macro

${SRC_O}: ${HDR_O}

${BUILD}/%.h.o: %.h generator
	@-mkdir --parent $$(dirname $@)
	${CC} -c ${CCFLAGS} $< -Iapi -I${GENERATED}/api -o $@

${BUILD}/%.o: %.c ${HDR}
	@-mkdir --parent $$(dirname $@)
	${CC} -c ${CCFLAGS} $< -Iapi -I${GENERATED}/api -o $@

${LIB}: ${SRC_O}
	@-mkdir --parent $$(dirname $@)
	${CC} -shared -o $@ ${CCFLAGS}  -Iapi -I${GENERATED}/api $^
	@chmod -x $@

${BUILD}/test/lang: test/lang.c ${SRC_O}
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $^ -Iapi -I${GENERATED}/api -o $@

