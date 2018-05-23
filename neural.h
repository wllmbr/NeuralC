#ifndef NEURAL_H
#define NEURAL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEARNING_RATE	0.5
#define DEFAULT_WEIGHT	0.25
#define TRAINED_THRESHOLD	0.001

#define DEFAULT_RANDOM_SEED	0xdeadbeef

/*Neural Node data structre */
struct neuron{
	uint32_t neuronID;
	/* Input Summation */
	double vectorSum;
	double oldSum;
	/* Node Gain */
	double vectorBias;
	/* Node Result */
	double neuralState;
	/* Number of incomming nodes that have applied their result */
	uint32_t vectorInputCount;
	/* Number of expected incoming nodes */
	uint32_t vectorInputTotal;
	/* Linked list identifying nodes to apply result to */
	struct neuralLink * pointingTo;
	/* Linked list of nodes to apply learning back prop to */
	struct neuralLink * pointedToBy;
};

/*Linked list for dynamically connecting nodes */
struct neuralLink{
	struct neuron * targetNode;
	double weight;
	struct neuralLink * next;
};

/*Init Functions */
void initNeuron(struct neuron *node, uint32_t ID);
void addNeuralLink(struct neuron *source, struct neuron *destination);

void runNeuron(struct neuron * node);
void learnNeuron(struct neuron * node, double error);

double activation(double input);
double activationdx(double input);


#define ERR_MISSING_NODE	10


#endif