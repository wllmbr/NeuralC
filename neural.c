#include "neural.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void runNeuron(struct neuron * node){
	/* Calculate Neuron Output */

	double neuralState = node->vectorSum * node->vectorGain;

	/* Apply Output to all of the output nodes */

	struct neuralLink * traversalPoint;
	traversalPoint = node->pointingTo;
	while(traversalPoint != NULL){
		/* Check to make sure the target node is actually there... */
		if(traversalPoint->targetNode == NULL){
			printf("A node targeted doesn't exist, exiting before segfault\n");
			exit(ERR_MISSING_NODE);
		}
		traversalPoint->targetNode->vectorSum += neuralState;
		traversalPoint = traversalPoint->next;
	}

	/* Clear sum and count for next round */

	node->vectorSum = 0;
	node->vectorInputCount = 0;

	return;
}

void initNeuron(struct neuron *node){
	/*Initialize Node Values */
	node->neuronID = 0;
	node->vectorSum = 0;
	node->vectorGain = DEFAULT_GAIN;
	node->vectorInputCount = 0;
	node->vectorInputTotal = 0;

	/* Setup Linked Lists */
	node->pointingTo = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	node->pointingTo->targetNode = NULL;
	node->pointingTo->next = NULL;

	node->pointedToBy = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	node->pointedToBy->targetNode = NULL;
	node->pointedToBy->next = NULL;


}

void addNeuralLink(struct neuron *source, struct neuron *destination){
	struct neuralLink * traversalPoint;

	traversalPoint = source->pointingTo;
	/* Move to the end of the linked list */
	while(traversalPoint->next != NULL){
		traversalPoint = traversalPoint->next;
	}
	traversalPoint->targetNode = destination;

	traversalPoint = destination->pointedToBy;
	/* Move to the end of the linked list */
	while(traversalPoint->next != NULL){
		traversalPoint = traversalPoint->next;
	}
	traversalPoint->targetNode = source;
}