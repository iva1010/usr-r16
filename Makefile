all: sources

.PHONY: sources
sources:
	make -C sources  all

.PHONY: clean
clean: sources-clean

