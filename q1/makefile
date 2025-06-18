all: divide_by_zero stack_overflow invalid_memory divide_by_zero_g stack_overflow_g invalid_memory_g

divide_by_zero: divide_by_zero.c
	gcc $< -o $@

stack_overflow: stack_overflow.c
	gcc $< -o $@

invalid_memory: invalid_memory.c
	gcc $< -o $@
divide_by_zero_g: divide_by_zero.c
	gcc -g $< -o $@

stack_overflow_g: stack_overflow.c
	gcc -g $< -o $@

invalid_memory_g: invalid_memory.c
	gcc -g $< -o $@

clean:
	rm -f divide_by_zero stack_overflow invalid_memory divide_by_zero_g stack_overflow_g invalid_memory_g core.*