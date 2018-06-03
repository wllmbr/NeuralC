#include "neural.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void runNeuron(struct neuron * node){
	/* Calculate Neuron Output */

	// if(node->vectorGain < 0){
		// printf("\nWarning: Gains are negative, instability detected\n");
		// exit(-11);
	// }

	node->neuralState = activation(node->vectorSum + node->vectorBias);
	// printf("Node %lld had a sum of %f and produced a state of %f\n",node,node->vectorSum,node->neuralState );

	/* Apply Output to all of the output nodes */

	struct neuralLink * traversalPoint;
	traversalPoint = node->pointingTo;
	while(traversalPoint->next != NULL){
		/* Check to make sure the target node is actually there... */
		if(traversalPoint->targetNode == NULL){
			// printf("Node %lld has no target nodes\n",node);
			exit(ERR_MISSING_NODE);
		}
		// printf("Node %lld applied state to node %lld\n",node,traversalPoint->targetNode);
		traversalPoint->targetNode->vectorSum += (node->neuralState * traversalPoint->weight);
		traversalPoint = traversalPoint->next;
	}

	/* Clear sum and count for next round */
	node->oldSum = node->vectorSum;
	node->vectorSum = 0;
	node->vectorInputCount = 0;

	return;
}

void initNeuron(struct neuron *node, uint32_t ID){
	/*Initialize Node Values */
	node->neuronID = ID;
	node->vectorSum = 0;
	// node->vectorGain = 1.0 / (ID + 1.0);
	node->vectorInputCount = 0;
	node->vectorInputTotal = 0;
	node->vectorBias = 0;

	/* Setup Linked Lists */
	node->pointingTo = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	node->pointingTo->targetNode = NULL;
	node->pointingTo->next = NULL;

	node->pointedToBy = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	node->pointedToBy->targetNode = NULL;
	node->pointedToBy->next = NULL;

	// printf("Node ID %d initialized with gain %.3f\n",ID,node->vectorGain);
	// printf("Node %lld allocated\n",node);

}

void addNeuralLink(struct neuron *source, struct neuron *destination){
	struct neuralLink * traversalPoint;

	// printf("Linking Nodes %lld and %lld\n",source, destination);

	traversalPoint = source->pointingTo;
	/* Move to the end of the linked list */
	while(traversalPoint->next != NULL){
		// printf("Node %lld already points to %lld\n",source,traversalPoint->targetNode);
		traversalPoint = traversalPoint->next;
	}
	struct neuralLink * newLink;
	newLink = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	newLink->next = NULL;
	newLink->targetNode = NULL;
	traversalPoint->next = newLink;
	traversalPoint->targetNode = destination;
	traversalPoint->weight = (float)rand() / (float)RAND_MAX;

	destination->vectorInputTotal++;

	// printf("Node %lld now has a reference to node %lld\n",source,traversalPoint->targetNode);
}

double activation(double input){
	return 1.0 / (1.0 + pow(2.71828,-1.0 * input));
}
double activationdx(double input){
	double act = activation(input);
	return act * ( 1 - act);
}

void learnNeuron(struct neuron * node, double error){
	struct neuralLink * traversalPoint;
	traversalPoint = node->pointingTo;
	while(traversalPoint->next != NULL){
		/* Check to make sure the target node is actually there... */
		if(traversalPoint->targetNode == NULL){
			// printf("Node %lld has no target nodes\n",node);
			exit(ERR_MISSING_NODE);
		}

		traversalPoint->weight += LEARNING_RATE * ( error * activationdx(node->neuralState) * traversalPoint->targetNode->oldSum );

		// printf("| %d -> %.3f\t", node->neuronID, traversalPoint->weight);

		traversalPoint = traversalPoint->next;
	}
}