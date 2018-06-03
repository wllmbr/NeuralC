#include "neuralNetwork.h"
#include "neural.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Initialize Neural Network */
void initNetwork(struct nNetwork *networkSpace, LAYER_ID layerCount){
	srand(0xdeadbeef);

	/* Set the nodelist pointer to 0 */
	networkSpace->nodeList = NULL;

	/* Build the array for tracking node counts and layer associated */
	networkSpace->layers = (LAYER_ID *)malloc(sizeof(LAYER_ID) * layerCount);
	networkSpace->numLayers = layerCount;

	return;
}

void addLayer(struct nNetwork *net, NODE_ID nodeCount){
	static LAYER_ID maxLayers =0;
	net->layers[maxLayers++] = nodeCount;
	return;
}

void linkNetwork(struct nNetwork * net){

	NODE_ID currentNode, nodeCount, inode, i2node, srcNode, desNode;
	LAYER_ID ilayer;

	currentNode = 0;
	nodeCount = 0;
	inode = 0;

	/* Add up layer counts to get total number of nodes */
	for(ilayer = 0; ilayer < net->numLayers; ilayer++){
		nodeCount += net->layers[ilayer];
	}

	/* Create node memory space */
	net->nodeList = (struct neuron *)malloc(sizeof(struct neuron) * nodeCount);
	net->nodeCount = nodeCount;

	/* Initialize all of the nodes */
	for(inode = 0; inode < nodeCount; inode++){
		initNeuron(&(net->nodeList[inode]), inode);
	}

	/* Link nodes across layers */
	NODE_ID *layerNodeStart= (NODE_ID *) malloc(sizeof(NODE_ID) * net->numLayers);
	NODE_ID i;
	layerNodeStart[0] = 0;
	currentNode = 0;
	for(i = 1; i < net->numLayers; i++){
		currentNode += net->layers[i-1];
		layerNodeStart[i] = currentNode;
	}

	currentNode = 0;
	srcNode = 0;
	desNode = 0;
	for(ilayer = 0; ilayer < (net->numLayers-1); ilayer++){
		// printf("Linking Layer %d to layer %d\n",ilayer, ilayer+1);
		srcNode = layerNodeStart[ilayer];
		desNode = layerNodeStart[ilayer+1];
		// printf("Layer %d starts at node %lld\n", ilayer, srcNode);
		// printf("Layer %d starts at node %lld\n", ilayer+1, desNode);
		for(inode = 0; inode < net->layers[ilayer]; inode++){
			desNode = layerNodeStart[ilayer+1];
			for(i2node = 0; i2node < net->layers[ilayer+1]; i2node++){
				// printf("Node Pair SRC = %lld, DES = %lld\n",srcNode,desNode);
				addNeuralLink(&(net->nodeList[srcNode]),&(net->nodeList[desNode]));
				desNode++;
			}
			srcNode++;
		}
	}

	printf("Node Count %lld\n",nodeCount);

	free(layerNodeStart);

	return;
}

void learnNetwork(struct nNetwork *net, double error){
	NODE_ID currentNode = 0;

	/*Iterate through node list and apply error terms to neuron learning function*/
	for(currentNode =0; currentNode < net->nodeCount; currentNode++){
		learnNeuron(&(net->nodeList[currentNode]),error);
	}

	return;
}

double trainNetwork(struct nNetwork *net, double *input, double *output){
	NODE_ID currentNode = 0;
	double lastError =0, errorDeltaP =0;
	uint8_t firstRound = 1;

	while(1){
		/*Iterate through node list and apply error terms to neuron learning function*/
		net->nodeList[0].vectorSum = *input;

		for(currentNode =0; currentNode< net->nodeCount; currentNode++){
			runNeuron(&(net->nodeList[currentNode]));
		}

		double result;
		result = net->nodeList[net->nodeCount - 1].neuralState;

		if(result != result){
			fprintf(stderr, "Network created NaN result.\n");
			exit(-1);
		}

		double errorTerm = *output - result;

		printf("Error Term %.3f ",errorTerm);
		fflush(stdout);



		/* Test if error has changed enough since last time break*/
		if(!(firstRound)){
			errorDeltaP = (errorTerm - lastError)/ lastError;
			printf(" Error Delta %.3f\n",errorDeltaP);
			if((fabs(errorDeltaP) < TRAINED_LIMIT) || (errorTerm == 0.0) || (fabs(errorTerm) < 0.001)){
				
				return errorTerm;
			}
		}
		firstRound = 0;
		lastError = errorTerm;

		/* Train the network on the error */
		learnNetwork(net, errorTerm);

	}

}

double runNetwork(struct nNetwork *net, double *input){
	NODE_ID currentNode = 0;

	for(currentNode =0; currentNode< net->nodeCount; currentNode++){
		runNeuron(&(net->nodeList[currentNode]));
	}

	double result;
	result = net->nodeList[net->nodeCount - 1].neuralState;

	return result;



}