#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "neural.h"

#define NUM_NODES	4
double training[256];

int main(){
	printf("Starting Shitty Net TM\n");

	/* Create a shitty four node net */

	struct neuron net[NUM_NODES];

	uint16_t i;
	for(i = 0; i < NUM_NODES; i++){
		initNeuron(&net[i]);
	}

	/* Link the nets */

	addNeuralLink(&net[0],&net[1]);
	printf("\n\nNext Link\n");
	addNeuralLink(&net[0],&net[2]);
	printf("\n\nNext Link\n");
	addNeuralLink(&net[1],&net[3]);
	printf("\n\nNext Link\n");
	addNeuralLink(&net[2],&net[3]);
	printf("\n\n");

	/* Build Training Data */
	printf("Training Set\n");
	for(i=0; i < 256; i++){
		/* 0 -> Unknown, 1-> Capital Letter, 2 -> Lower Case Letter */
		if((i > 0x40) && ( i < 0x5B)){
			training[i] = 1.0;
		} else if ((i > 0x60) && (i < 0x7B)){
			training[i] = 2.0;
		} else {
			training[i] = 0.0;
		}

		// printf("%d -> %f\n",i,training[i]);
	}

	/* Run Training */
	uint8_t netTrained = 0;
	uint64_t iterations =0;
	double totalError = 0;
	double lastError = 0;

	while(!netTrained){
		iterations++;
		// netTrained = 1;
		
		lastError = totalError;
		totalError = 0;

		for(i = 0; i < 256; i += 2){
			/* Apply Index number on node 0 */
			while(1){
				net[0].vectorSum = (double)(i);
				runNeuron(&net[0]);
				runNeuron(&net[1]);
				runNeuron(&net[2]);
				runNeuron(&net[3]);

				/* Calculate Prediction Error */
				double netResult = net[3].neuralState;
				double errorTerm = training[i] - netResult;
				// printf("Tested %d which is cat %.3f and got %.3f\n",i,training[i],netResult);
				// printf("Error was %.1f\n",fabs(errorTerm));

				/* Apply Learning Rate */

				uint8_t j;
				for(j = 0; j < NUM_NODES; j++){
					net[j].vectorGain += errorTerm * LEARNING_RATE;
				}

				if(fabs(errorTerm) < TRAINED_THRESHOLD){
					// printf("Net trained on Data Point %d\n",i);
					totalError += fabs(errorTerm);
					break;
				}

				// netTrained = 0;
			}
		}

		// printf("Total Error is %.3f\n",totalError);
		// fflush(stdout);		

		/*If lastError is zero, then this is first run */
		if(lastError != 0){

			double errorDelta = fabs((totalError - lastError)/lastError) * 100.0;
			printf("Error Delta is %.3f%%\n",errorDelta);

			/* If the overall error hasn't changed within 0.01%, then break */
			if( errorDelta < 0.000001){
				printf("Training Complete, error is %.3f%%\n",totalError);
				netTrained = 1;
			}
		}

	}

	printf("Training Complete with %lld iterations\n",iterations);

	/* Testing Prediction */
	for(i=0; i < 256; i++){
		net[0].vectorSum = (double)i;
		runNeuron(&net[0]);
		runNeuron(&net[1]);
		runNeuron(&net[2]);
		runNeuron(&net[3]);

		double netResult = net[3].neuralState;

		printf("Number %d is category %f when it should be %.0f\n",i,netResult,training[i]);
	}

	return 0;
}