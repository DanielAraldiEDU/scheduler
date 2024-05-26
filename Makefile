# makefile for scheduling program
#
# make rr_p - for round-robin scheduling
# make edf - for edf scheduling

CC=gcc
CFLAGS=-Wall
RR_P=./src/rr_p
EDF=./src/edf

clean:
	rm -rf ./src/*.o ./src/**/*.o
	rm -rf ./src/*.exe ./src/**/*.exe

rr_p: $(RR_P)/driver.o $(RR_P)/list.o $(RR_P)/cpu.o $(RR_P)/schedule_rr_p.o
	$(CC) $(CFLAGS) -o $(RR_P)/rr_p.exe $(RR_P)/driver.o $(RR_P)/schedule_rr_p.o $(RR_P)/list.o $(RR_P)/cpu.o

edf: $(EDF)/driver.o $(EDF)/list.o $(EDF)/cpu.o $(EDF)/schedule_edf.o
	$(CC) $(CFLAGS) -o $(EDF)/edf.exe $(EDF)/driver.o $(EDF)/schedule_edf.o $(EDF)/list.o $(EDF)/cpu.o

exe_rr_p: $(RR_P)/rr_p.exe
	$(RR_P)/rr_p.exe $(RR_P)/rr-schedule_pri.txt

exe_edf: $(EDF)/edf.exe
	$(EDF)/edf.exe $(EDF)/edf-schedule_pri.txt

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