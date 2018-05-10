#ifndef NEURAL_H
#define NEURAL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEARNING_RATE	0.000005
#define DEFAULT_GAIN	2.0
#define TRAINED_THRESHOLD	0.0001

/*Neural Node data structre */
struct neuron{
	uint32_t neuronID;
	/* Input Summation */
	double vectorSum;
	/* Node Gain */
	double vectorGain;
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
	struct neuralLink * next;
};

/*Init Functions */
void initNeuron(struct neuron *node);
void addNeuralLink(struct neuron *source, struct neuron *destination);

void runNeuron(struct neuron * node);
// void learnNeuron(struct neuron * node);


#define ERR_MISSING_NODE	10


#endif