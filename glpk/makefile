all: install

install:

	cd glpk-4.43; ./configure --disable-shared
	cd glpk-4.43; make
	cd glpk-4.43; make install

uninstall:

	cd glpk-4.43; make uninstall
	make clean

clean:

	cd glpk-4.43; make clean
	cd glpk-4.43; make distclean
