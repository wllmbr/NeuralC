#include "neuralNetwork.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Initialize Neural Network */
void initNetwork(struct nNetwork *networkSpace, uint32_t nodeCount){
	networkSpace->nodeList = (struct neuron *)malloc(sizeof(struct neuron) * nodeCount);
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

	/* ID the nodes */
	for(i = 0; i < nodeCount; i++){
		net->layerList[i + populatedNodes] = populatedLayers;
	}

	/* Initialize the nodes */
	for(i = 0; i < nodeCount; i++){
		initNeuron(net->nodeList[i + populatedNodes],i + populatedNodes);
	}

	net->populatedNodes += nodeCount;
	
}

/* Link Network */
void linkNetwork(struct nNetwork *net){
	struct neuron *src;
	struct neuron *dst;

	uint32_t srcInt = 0;
	uint32_t dstInt = 0;

	for(srcInt = 0; srcInt < populatedNodes; i++){
		
	}

}
