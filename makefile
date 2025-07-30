# Root Makefile

SUBDIRS = q1 q2 q3 q4 q5 q6 q7

.PHONY: all clean

all:
	@for dir in $(SUBDIRS); do \
		echo "Building $$dir..."; \
		$(MAKE) -C $$dir all || { echo "Build failed in $$dir"; exit 1; }; \
	done
	@echo "All builds completed successfully."

clean:
	@for dir in $(SUBDIRS); do \
		echo "Cleaning $$dir..."; \
		$(MAKE) -C $$dir clean || { echo "Clean failed in $$dir"; exit 1; }; \
	done
	@echo "All clean completed successfully."