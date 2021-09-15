all: sources

.PHONY: sources
sources:
	make -C sources  all

.PHONY: clean
clean: sources-clean

.PHONY: sources-clean
sources-clean:
	make -C sources clean

.PHONY: sources-debug
sources-debug:
	make -C sources debug

