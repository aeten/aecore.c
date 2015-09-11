all: test

test: build/test/core/constructor/constructor.c.o build/test/core/constructor/constructor.cpp.o test/core/constructor/constructor
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

.PHONY: all test
