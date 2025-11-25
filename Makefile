make:
	make -C build test_all --quiet

remake:
	cmake -S . -B build
	make -C build test_all --quiet