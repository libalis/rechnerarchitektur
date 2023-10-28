.PHONY: all clean

all: standard_deviation

clean:
	rm -rf standard_deviation

standard_deviation: standard_deviation.c
	gcc -lm -o $@ $^
