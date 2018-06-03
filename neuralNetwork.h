#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "neural.h"

#define TRAINED_LIMIT	0.01

typedef uint16_t LAYER_ID;
typedef uint32_t NODE_ID;

/* Struct for holding object data */
struct nNetwork{
	struct neuron *nodeList;

	LAYER_ID *layers;

	LAYER_ID numLayers;
	NODE_ID nodeCount;
};

/* Initialize Neural Network */
void initNetwork(struct nNetwork *networkSpace,LAYER_ID layerCount);

/* Add a layer to the net */
void addLayer(struct nNetwork *net, NODE_ID nodeCount);

/* Link Network */
void linkNetwork(struct nNetwork *net);

/* Learn Network */
void learnNetwork(struct nNetwork *net, double error);

double trainNetwork(struct nNetwork *net, double *input, double *output);
double runNetwork(struct nNetwork *net, double *input);

#endif