#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "neural.h"

/* Struct for holding object data */
struct nNetwork{
	struct neuron * nodeList;
	/* List identifying which nodes belong to what layer
		nodeID should be index, value is layer number */
	uint32_t * layerList;
	/* Current count of populated nodes */
	uint32_t populatedNodes;
	/* Last Populated Layer */
	uint32_t populatedLayers;
	uint32_t networkSize;
}

/* Initialize Neural Network */
void initNetwork(struct nNetwork *networkSpace, uint16_t layers);

/* Add a layer to the net */
void addLayer(struct nNetwork *net, uint16_t nodeCount);

/* Link Network */
void linkNetwork(struct nNetwork *net);

/* Learn Network */
void learnNetwork(struct nNetwork *net);

void runNetwork(struct nNetwork *net, double input[], double output[]);

#endif