#include "neural.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void runNeuron(struct neuron * node){
	/* Calculate Neuron Output */

	node->neuralState = node->vectorSum * node->vectorGain;
	printf("Node %lld had a sum of %f and produced a state of %f\n",node,node->vectorSum,node->neuralState );

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
		traversalPoint->targetNode->vectorSum += node->neuralState;
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

	printf("Linking Nodes %lld and %lld\n",source, destination);

	traversalPoint = source->pointingTo;
	/* Move to the end of the linked list */
	while(traversalPoint->next != NULL){
		printf("Node %lld already points to %lld\n",source,traversalPoint->targetNode);
		traversalPoint = traversalPoint->next;
	}
	struct neuralLink * newLink;
	newLink = (struct neuralLink *)malloc(sizeof(struct neuralLink));
	newLink->next = NULL;
	newLink->targetNode = NULL;
	traversalPoint->next = newLink;
	traversalPoint->targetNode = destination;

	// traversalPoint = destination->pointedToBy;
	// /* Move to the end of the linked list */
	// while(traversalPoint->next != NULL){
	// 	traversalPoint = traversalPoint->next;
	// }
	// traversalPoint->targetNode = source;

	destination->vectorInputTotal++;

	printf("Node %lld now has a reference to node %lld\n",source,traversalPoint->targetNode);
}