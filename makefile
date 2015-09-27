SHELL=sh
GENERATED=generated
BUILD=build
CC=gcc
CCFLAGS=-g -O0 -DAETEN_DEBUG -fPIC

NAME=$(notdir $(realpath $(dir $MAKEFILE)))
VERSION=$(shell { git describe --tags --match='\d\+\.\d\+.*' --dirty=+ 2>/dev/null || echo g$$(git describe --always --dirty=+); } | sed 's@.*/@@')

LIB=${BUILD}/${NAME}-${VERSION}.so
GEN=$(addsuffix .h,$(addprefix ${GENERATED}/api/aeten/lang/,export import FOR_EACH))
HDR=$(shell find api -type f -name \*.h) ${GEN}
SRC=$(shell find src -type f -name \*.c)

HDR_O=$(addprefix ${BUILD}/,$(patsubst %.h,%.h.o,${HDR}))
SRC_O=$(addprefix ${BUILD}/,$(patsubst %.c,%.o,${SRC}))

$(info Build ${NAME} ${VERSION})

.PHONY: check all lib clean ${GEN}

all: check lib

lib: ${LIB}

check: ${BUILD}/test/lang
	@for procedure in $^; do ./$$procedure || exit 1; done

clean:
	rm -rf build ${GENERATED}

${SRC_O}: ${HDR_O}

${BUILD}/%.h.o: %.h ${GEN}
	@echo ${GEN}
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

${GENERATED}/api/aeten/lang/export.h:
	./generator/export

${GENERATED}/api/aeten/lang/FOR_EACH.h:
	./generator/for-each-macro

