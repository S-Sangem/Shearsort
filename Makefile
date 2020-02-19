all: shearsort threadsort

shearsort: shearsort.c
		gcc -o shearsort shearsort.c -pthread -lm

threadsort: threadsort.c
				gcc -o threadsort threadsort.c -pthread -lm
