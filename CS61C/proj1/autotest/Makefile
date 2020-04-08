CUNIT := -L/Usr/local/Cellar/cunit/2.1-3/lib -I/Usr/local/Cellar/cunit/2.1-3/include -lcunit

beargit: main.c beargit.c util.c beargit.h util.h
	gcc -g -std=c99 main.c beargit.c util.c -o beargit

beargit-unittest: main.c beargit.c cunittests.c util.c beargit.h util.h cunittests.h
	gcc -g -DTESTING -std=c99 main.c beargit.c cunittests.c util.c -o beargit-unittest $(CUNIT)

clean:
	rm -rf beargit autotest test beargit-unittest TEST_STDOUT TEST_STDERR

check: beargit
	python2.7 tester.pyc beargit.c