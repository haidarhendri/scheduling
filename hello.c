#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <pthread.h>
#include <sys/syscall.h>
#include "pvm3.h"
#include "bubbleSort.h"
#include "ipdsa.h"

#define task_size 100

#include "sched.h"
#include "initGenerateAttr.h"
#include "init.h"
#include "initPvm.h"
#include "quickSortStruct.h"
#include "exportResult.h"


int main()
{	
	int h, *tasks, nproses, sisa, slice, bound, **arr, cc, *tid, jmlRand, avgTardiness;
	int sumOfTardiness = 0;
	int sumOfNonDelayed = 0;
	double avgLoad, *mips,*PELoad;
	char **hostname; //untuk menyimpan nama2 host yang terhubung
	char **outputSlave = (char**) malloc(task_size*sizeof(char*));
//	char **outputSlaveSize;
//	char **args = (char**) malloc(4*sizeof(char*));
//	char charSlice[9], charLowerBound[9], charUpperBound[9];
	
	pthread_t thread[task_size];
	int i, j, k, l, et, dl, period;

	et = runBubbleSort();
	slice = task_size/nhost;
	sisa = task_size%nhost;
	bound = 0;
	jmlRand = 1900;
	
	tid = (int*) malloc((nhost+1)*sizeof(int));
	
	hostname = gethostnamePvm(nhost);
	tasks = getTasks(hostname, nhost);
	avgLoad = avg_load(tasks, nhost);  //untuk mendapatkan rata - rata Load untuk setiap PE
	mips = getMips(hostname, nhost);
	PELoad = getPELoad(tasks, mips, avgLoad, nhost);
	
	
	printf("main thread [%ld]\n", gettid());
	for(i = 0; i < task_size; i++)
	{
//		printf("DL %d\n", i);
		dl = generate_dl(et);
		period = generate_period(et);

		attr.size = sizeof(attr),
		attr.sched_flags = 0,
		attr.sched_nice = 0,
		attr.sched_priority = 0,
		attr.sched_policy = SCHED_DEADLINE,
		attr.sched_runtime = et,
		attr.sched_deadline = dl,
		attr.sched_period = period,

		arr_task[i].task_id = i;
		arr_task[i].eet = attr.sched_runtime;
		arr_task[i].time_delay = time_delayIpdsa(dl, et);
		arr_task[i].deadline = attr.sched_deadline;
		arr_task[i].tardiness = attr.sched_period;

		pthread_create(&thread[i], NULL, run_deadline, NULL);
//		sleep(1);
	}
	sleep(2);
	
	outputSlave = getDariSlave(nhost, hostname, jmlRand);
	
/*	for(h=0; h<nhost; h++){
		printf("hostname: %s\n", hostname[h]);
		printf("total tasks: %d\n", tasks[h]);
		printf("rating (MIPS): %.5f\n", mips[h]);
		printf("PELoad: %.5f\n\n", PELoad[h]);
	} */
	printf("hello\n");
	
	for(h=0; h<task_size; h++){
		printf("getTID %d: %s\n", h, arrOutputTask->outputSlaveTid[h]);
		printf("getTardiness %d: %s ns\n", h, arrOutputTask->outputSlaveTardiness[h]);
		printf("getNonDelay %d: %s\n\n", h, arrOutputTask->outputSlaveNonDelay[h]);
	}
	
/*	if(sisa == 0){
		for(h=0; h<task_size; h++){
			printf("getTimeDariSlave: %s ns\n", arrOutputTask->outputSlaveMsec[h]);
			printf("getSizeDariSlave: %s\n\n", arrOutputTask->outputSlaveSize[h]);
		}
	}
	else{
		for(h=0; h<=task_size; h++){
			printf("getTimeDariSlave: %s ns\n", arrOutputTask->outputSlaveMsec[h]);
			printf("getSizeDariSlave: %s\n\n", arrOutputTask->outputSlaveSize[h]);
		} 
	} */
	printf("\n");
	
	
	
	
	
	
	sleep(1);

	for(j = 0; j < task_size; j++)
	{
		done = 1;
//		pthread_join(thread[j], &retvals[j]);
	}

	sleep(1);
	
	for(j = 0; j < task_size; j++)
	{
		sumOfTardiness += atoi(arrOutputTask->outputSlaveTardiness[j]);
		sumOfNonDelayed += atoi(arrOutputTask->outputSlaveNonDelay[j]);
	}
	
	printf("sumOfTardiness = %d\n", sumOfTardiness);
	printf("sumOfNonDelayed = %d\n", sumOfNonDelayed);
	
	avgTardiness = avg_tardiness(sumOfTardiness, task_size);	
	printf("avgTardiness = %d\n", avgTardiness);

/*	for(k = 0; k < task_size; k++)
	{
		printf("TID task %d adalah %ld\n", k, arr_task[k].task_id);
		printf("EET task %d adalah %d ns\n", k, arr_task[k].eet);
		printf("TD  task %d adalah %d ns\n", k, arr_task[k].time_delay);
		printf("DL  task %d adalah %d ns\n", k, arr_task[k].deadline);
		printf("PD  task %d adalah %d ns\n\n", k, arr_task[k].tardiness);
	}

	sleep(2); */
	
	exportResult();

	mergeSort(arr_task, 0, task_size);

/*	for( l = 1; l <= task_size; l++){
		printf("TD %d is %d \n", l, arr_task[l].time_delay);
	} */

	

	printf("main dies [%ld]\n", gettid());
	
	

	return 0; 
}


