#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "neural.h"
#include "neuralNetwork.h"

#define NUM_NODES	4
double training[256];

int main(){
	printf("Starting Shitty Net TM\n");
	uint64_t i = 0;

	/* Create a shitty four node net */
	struct nNetwork net;

	initNetwork(&net, 3);

	addLayer(&net,1);
	addLayer(&net,2);
	addLayer(&net,1);

	printf("Linking Network\n");
	linkNetwork(&net);
	printf("Link Complete\n");

	/* Build Training Data */
	printf("Training Set\n");
	for(i=0; i < 128; i++){
		/* 0 -> Unknown, 1-> Capital Letter, 2 -> Lower Case Letter */
		if((i > 0x40) && ( i < 0x5B)){
			training[i] = 0.667;
		} else if ((i > 0x60) && (i < 0x7B)){
			training[i] = 0.75;
		} else {
			training[i] = 0.8;
		}

		// printf("%d -> %f\n",i,training[i]);
	}

	// double inNum = 452.0, outNum = 0.5;
	// trainNetwork(&net, &inNum, &outNum);
	for(i = 4; i < 128; i += 4){
		double in = (double)i/128.0;
		printf("Training against %d and %.3f\n",i,training[i]);
		trainNetwork(&net, &in, &(training[i]));
	}

	double result, input;
	for(i = 4; i < 128; i++){
		input = (double)i/128.0;
		result = runNetwork(&net, &input);
		printf("Input was %d classification was %.3f when should be %.3f\n",i,result,training[i]);
	}


	printf("Network trained\n");



	return 0;
}