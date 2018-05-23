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

	srand(DEFAULT_RANDOM_SEED);
	/* Create a shitty four node net */

	struct neuron net[NUM_NODES];

	int32_t i;
	for(i = 0; i < NUM_NODES; i++){
		initNeuron(&net[i],i);
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
			training[i] = 0.667;
		} else if ((i > 0x60) && (i < 0x7B)){
			training[i] = 0.75;
		} else {
			training[i] = 0.5;
		}

		// printf("%d -> %f\n",i,training[i]);
	}

	/* Run Training */
	uint8_t netTrained = 0;
	uint64_t iterations =0;
	double totalError = 0;
	double lastError = 0;

	uint8_t jumpRate = 2;

	while(!netTrained){
		iterations++;
		// netTrained = 1;
		totalError = 0;

		for(i = 0; i <256; i++){
			printf("\rR %d\tI %d",iterations,i);
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
				printf(" Tested %d which is cat %.3f and got %.3f\t",i,training[i],netResult);
				// printf("Error was %.1f\n",errorTerm);

				// totalError = (errorTerm * errorTerm);

				printf("\nNode Gains ");
				learnNeuron(&net[2], errorTerm);
				learnNeuron(&net[1], errorTerm);
				learnNeuron(&net[0], errorTerm);

				if(!isnormal(errorTerm)){
					printf("\nExploded\n");
					exit(-10);
				}

				if(fabs(errorTerm) < TRAINED_THRESHOLD){
					totalError += fabs(errorTerm);
					break;
				}

				uint64_t q;
				// for(q = 0; q < 0x3ffff; q++){asm("");}
			}

			uint64_t q;
			// for(q = 0; q < 0x3ffffff; q++){asm("");}

		}
		// printf("\nTotal Error is %.3f\n",totalError);

		// totalError /= 256.0 / (double)jumpRate;

		// printf("MSE is %.3f\n",totalError);

		uint64_t q;
		// for(q = 0; q < 0xfffffff; q++){asm("");}
		/* Calculate Weight Change */



		// printf("Total Error is %.3f\n",totalError);
		fflush(stdout);		

		/*If lastError is zero, then this is first run */
		if(lastError != 0){

			double errorDelta = fabs((totalError - lastError)/lastError) * 100.0;
			printf("Total Error: %.3f, Error Delta: %.3f%%\n",totalError,errorDelta);

		// 	 If the overall error hasn't changed within 0.01%, then break 
			if( errorDelta < 0.000001){
				printf("Training Complete, error is %.3f%%\n",totalError);
				netTrained = 1;
			}
		}

		lastError = totalError;

	}

	printf("\nTraining Complete with %lld iterations\n",iterations);

	/* Testing Prediction */
	for(i=0; i < 256; i++){
		net[0].vectorSum = (double)i;
		runNeuron(&net[0]);
		runNeuron(&net[1]);
		runNeuron(&net[2]);
		runNeuron(&net[3]);

		double netResult = net[3].neuralState;

		printf("Number %d is category %f when it should be %.3f\n",i,netResult,training[i]);
	}

	return 0;
}