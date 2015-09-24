CC=gcc
CCFLAGS=-g -O0
all: test

test: test/core/algebra/base test/core/constructor test/core/object
	@for procedure in $^; do ./$$procedure || exit 1; done

clean:
	rm -rf build

build/test/core/constructor.c.o: test/core/constructor.c build/api/aeten/core.h.o
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $< -Iapi -o $@

build/test/core/constructor.cpp.o: test/core/constructor.c build/api/aeten/core.hh.o
	@-mkdir --parent $$(dirname $@)
	g++ $< -Iapi -o $@

test/core/object: build/test/core/object.c.o build/test/core/object.cpp.o
	@true

test/core/constructor: build/test/core/constructor.c.o build/test/core/constructor.cpp.o
	@true

test/core/algebra/base: build/src/aeten/core/algebra/base.c.o build/src/aeten/core/algebra/base.cpp.o
	@true

build/api/aeten/core.h.o: api/aeten/core.h
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $< -Iapi -o $@

build/api/aeten/core.hh.o: api/aeten/core.h
	@-mkdir --parent $$(dirname $@)
	g++ $< -Iapi -o $@

build/test/core/object.c.o: test/core/object.c build/api/aeten/core.h.o
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} $< -Iapi -o $@

build/test/core/object.cpp.o: test/core/object.c build/api/aeten/core.hh.o
	@-mkdir --parent $$(dirname $@)
	g++ $< -Iapi -o $@

build/src/aeten/core/algebra/base.c.o: src/aeten/core/algebra/base.c
	@-mkdir --parent $$(dirname $@)
	${CC} ${CCFLAGS} -g -O0 -lm -o $@ $<

build/src/aeten/core/algebra/base.cpp.o: src/aeten/core/algebra/base.c
	@-mkdir --parent $$(dirname $@)
	g++ -g -O0 -lm -o $@ $<

.PHONY: all test
