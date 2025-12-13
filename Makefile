make:
	make -C build test_all --quiet

remake:
	cmake -S . -B build
	make -C build test_all --quiet

make viz:
	cmake -S . -B build
	make -C build test_all --quiet
	dot -Tsvg tree.dot -o tree.svg