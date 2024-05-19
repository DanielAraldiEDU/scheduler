# makefile for scheduling program
#
# make rr_p - for round-robin scheduling
# make edf - for edf scheduling

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf *.exe

rr_p: driver.o list.o cpu.o schedule_rr_p.o
	$(CC) $(CFLAGS) -o rr_p.exe driver.o schedule_rr_p.o list.o cpu.o

edf: driver.o list.o cpu.o schedule_edf.o
	$(CC) $(CFLAGS) -o edf.exe driver.o schedule_edf.o list.o cpu.o

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c

schedule_rr_p.o: schedule_rr_p.c
	$(CC) $(CFLAGS) -c schedule_rr_p.c

schedule_edf.o: schedule_edf.c
	$(CC) $(CFLAGS) -c schedule_edf.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

cpu.o: cpu.c cpu.h
	$(CC) $(CFLAGS) -c cpu.c