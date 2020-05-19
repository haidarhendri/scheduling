#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "pvm3.h"

void swap_bubble(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-i-1; j++)
			if (arr[j] > arr[j+1])
				swap_bubble(&arr[j], &arr[j+1]);
}

int tardiness(int dl, int finish_time)
{
	return dl - finish_time;
}

int main(int argc, char const *argv[]) {
	char outputSlave[1000];
//	gethostname(outputSlave,25);

	srand(time(NULL));

	int task_tid = atoi(argv[1]);
	int dl = atoi(argv[2]);
	int size = 1000;
	int arr[size];
	int i, tardiness_t, non_delay;
	int min = 1;
	int max = size;
	
	//mendapatkan tid dari master
	int ptid = pvm_parent();

	for (i = 0; i < size; i++)
	{
		arr[i] = rand() % max + min;
	}

	int msec = 0, trigger = 10;

	clock_t before = clock();
	bubbleSort(arr, size);
	clock_t difference = clock() - before;
	msec = difference;
	
	tardiness_t = tardiness(dl, msec);
	
	if(dl > msec)
	{
		non_delay = 1;
	}
	else 
	{
		non_delay = 0;
	}
	
//	printf("Running time bubbleSort adalah %d ns\n", msec);	

	//mengirimkan hasil ke master
	pvm_initsend(PvmDataDefault);	
	sprintf(outputSlave, "%d", task_tid);
	pvm_pkstr(outputSlave);
	pvm_send(ptid, 2);

	pvm_initsend(PvmDataDefault);
	sprintf(outputSlave, "%d", tardiness_t);
	pvm_pkstr(outputSlave);
	pvm_send(ptid, 3);
	
	pvm_initsend(PvmDataDefault);
	sprintf(outputSlave, "%d", non_delay);
	pvm_pkstr(outputSlave);
	pvm_send(ptid, 4);
	
	pvm_exit();
	
	return 0;
}
