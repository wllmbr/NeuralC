CC = gcc
OPT = -O3
EF = -Wall
EXE = shittyNet
BUILD = bld
LIBS = $(BUILD)/$(NRL).o
NRL = neural
NET = neuralNet
MAIN = testNet.c



all: $(EXE)

$(EXE): $(MAIN) $(LIBS)
	$(CC) $(EF) $(OPT) -o $@ $(MAIN) $(LIBS)

$(BUILD)/$(NRL).o: $(NRL).c $(NRL).h
	$(CC) $(EF) $(OPT) -o $@ -c $<

$(BUILD)/$(NET).o: $(NET).c $(NET).h
	$(CC) $(EF) $(OPT) -o $@ -c $<