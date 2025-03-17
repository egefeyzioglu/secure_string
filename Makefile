all: secure_string

secure_string: main.c
	gcc main.c -o secure_string -O3

clean:
	rm -f secure_string
