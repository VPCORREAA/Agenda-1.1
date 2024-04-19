all: agenda

agenda: agenda.c
	$(CC) agenda.c -o agenda

run: agenda
	./agenda

clean:
	rm -f agenda
