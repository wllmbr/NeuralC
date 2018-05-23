#include "neuralNetwork.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Initialize Neural Network */
void initNetwork(struct nNetwork *networkSpace, uint32_t nodeCount){
	networkSpace->nodeList = NULL;
	/* Create an array that will reference the layers */
	networkSpace->layerList = (uint32_t *)malloc(sizeof(uint32_t) * nodeCount);
	networkSpace->populatedNodes = 0;
	networkSpace->populatedLayers = 0;
	networkSpace->networkSize = nodeCount;

}

/* Add a layer to the net */
void addLayer(struct nNetwork *net, uint16_t nodeCount){
	uint32_t i = 0;
	net->populatedLayers++;

	if((net->populatedLayers + nodeCount) > net->networkSize){
		printf("\nRequested node count exceeds predeclared size\n");
		printf("Offending Request: Layer %d Node Count %d\n",net->populatedLayers,nodeCount);
		exit(-1);

	}

	for(i = 0; i < nodeCount; i++){
		net->layerList[i + populatedNodes] = populatedLayers;
	}

	
}

/* Link Network */
void linkNetwork(struct nNetwork *net){
	net->nodeList = (uint32_t *)malloc();

}
