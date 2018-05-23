CC = gcc
OPT =  
EF = -Wall -Wno-format
LINKS = -lm
EXE = shittyNet
BUILD = bld
LIBS = $(BUILD)/$(NRL).o 
NRL = neural
NET = neuralNetwork
MAIN = testNet.c



all: $(EXE)

$(EXE): $(MAIN) $(LIBS)
	$(CC) $(EF) $(OPT) -o $@ $(MAIN) $(LIBS) $(LINKS)

$(BUILD)/$(NRL).o: $(NRL).c $(NRL).h
	$(CC) $(EF) $(OPT) -o $@ -c $<

#$(BUILD)/$(NET).o: $(NET).c $(NET).h
#	$(CC) $(EF) $(OPT) -o $@ -c $<

remake:
	rm -rf bld/*; make