all: test

test: build/api/aeten/core/algebra/base build/test/core/constructor/constructor.c.o build/test/core/constructor/constructor.cpp.o test/core/constructor/constructor
	build/api/aeten/core/algebra/base  -i 8 -o 16 173 -v
	@test/core/constructor/constructor

clean:
	rm -rf build

build/api/aeten/core/constructor.h.o: api/aeten/core/constructor.h
	@-mkdir --parent $$(dirname $@)
	gcc $< -Iapi -o $@

build/api/aeten/core/constructor.hpp.o: api/aeten/core/constructor.h
	@-mkdir --parent $$(dirname $@)
	g++ $< -Iapi -o $@

build/test/core/constructor/constructor.c.o: test/core/constructor/constructor.c build/api/aeten/core/constructor.h.o
	@-mkdir --parent $$(dirname $@)
	gcc $< -Iapi -o $@

build/test/core/constructor/constructor.cpp.o: test/core/constructor/constructor.c build/api/aeten/core/constructor.hpp.o
	@-mkdir --parent $$(dirname $@)
	g++ $< -Iapi -o $@

test/core/constructor/constructor:
	echo

build/api/aeten/core/algebra/base: src/aeten/core/algebra/base.c
	@-mkdir --parent $$(dirname $@)
	gcc -g -O0 -lm -o $@ $<
.PHONY: all test
