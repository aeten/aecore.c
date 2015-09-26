GENERATED=generated
CC=gcc
CCFLAGS=-g -O0 -DAETEN_DEBUG

all: test

test: test/core/algebra/base test/lang
	@for procedure in $^; do ./$$procedure || exit 1; done

clean:
	rm -rf build ${GENERATED}

test/lang: build/test/lang.o
	@true

test/core/algebra/base: build/src/aeten/core/algebra/base.c.o build/src/aeten/core/algebra/base.cpp.o
	@true

build/api/aeten/lang.h.o: api/aeten/lang.h ${GENERATED}/api/aeten/lang/export.h ${GENERATED}/api/aeten/lang/for-each-macro.h
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $< -Iapi -I${GENERATED}/api -o $@

build/test/lang.o: test/lang.c build/api/aeten/lang.h.o
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $< -Iapi -I${GENERATED}/api -o $@

build/src/aeten/core/algebra/base.c.o: src/aeten/core/algebra/base.c
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} -g -O0 -lm -o $@ $<

build/src/aeten/core/algebra/base.cpp.o: src/aeten/core/algebra/base.c
	@-mkdir --parent $$(dirname $@)
	g++ -g -O0 -lm -o $@ $<

${GENERATED}/api/aeten/lang/export.h:
	./generator/export

${GENERATED}/api/aeten/lang/for-each-macro.h:
	./generator/for-each-macro

.PHONY: all test ${GENERATED}/api/aeten/lang/export.h ${GENERATED}/api/aeten/lang/for-each-macro.h
