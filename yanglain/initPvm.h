int nhost = 4;

struct outputTask
{
	char **outputSlaveTid;
	char **outputSlaveTardiness;
	char **outputSlaveNonDelay;
};
struct outputTask arrOutputTask[501];

char **getDariSlave(int nhost, char **hostname, int jmlRand){
	int cc, dd, ee, ff, *tid, i, j, sisa, slice, bound;
	
	arrOutputTask->outputSlaveTid = malloc((task_size)*sizeof(arrOutputTask->outputSlaveTid));
	arrOutputTask->outputSlaveTardiness = malloc((task_size)*sizeof(arrOutputTask->outputSlaveTardiness));	
	arrOutputTask->outputSlaveNonDelay = malloc((task_size)*sizeof(arrOutputTask->outputSlaveNonDelay));
	
	char charSlice[9], charLowerBound[9], charUpperBound[9], charJmlRand[9], task_tid[9], deadline_t[9];
	char **args = (char**) malloc(4*sizeof(char*));
	tid = (int*) malloc((task_size+1)*sizeof(int));
	slice = task_size/nhost;
	sisa = task_size%nhost;
	bound = 0;
	
	//mengirimkan perintah ke slave untuk mendapatkan jumlah task masing - masing
	for(i=0; i<nhost; i++){
		sprintf(charJmlRand, "%d", jmlRand);
		sprintf(charSlice,"%d",slice);
		sprintf(charLowerBound, "%d", bound);
		sprintf(charUpperBound, "%d", (bound+slice-1));
		
	/*	args[0] = charJmlRand;
		args[1] = charSlice;
		args[2] = charLowerBound;
		args[3] = charUpperBound; */
		
		printf("yang mengerjakan task %s-%s adalah: %s\n", charLowerBound, charUpperBound, hostname[i]);		
		
		for(j=bound; j<=(bound+slice-1); j++){
//			printf("TID %d adl %ld\n", j, arr_task[j].task_id);
			sprintf(task_tid, "%ld", arr_task[j].task_id);
			args[0] = task_tid;
			sprintf(deadline_t, "%d", arr_task[j].deadline);
			args[1] = deadline_t;
//			printf("PVM %d\n", j);
			cc = pvm_spawn("./mergeSortSlave", args, 1, hostname[i], 1, &tid[j]);
		}
		bound += slice;	
//		sleep(1);
	}
	
	printf("PVM sudah dikirim\n");
	
//	bound = 0;
//	for(i=0; i<nhost; i++){		
		for(j=0; j<(task_size-sisa); j++){
			arrOutputTask->outputSlaveTid[j] = malloc((task_size)*sizeof(arrOutputTask->outputSlaveTid[j]));
			arrOutputTask->outputSlaveTardiness[j] = malloc((task_size)*sizeof(arrOutputTask->outputSlaveTardiness[j]));
			arrOutputTask->outputSlaveNonDelay[j] = malloc((task_size)*sizeof(arrOutputTask->outputSlaveNonDelay[j]));

//			printf("%d\n", task_size);
			dd = pvm_recv(tid[j], 2);
//			printf("2\n");
			pvm_bufinfo(dd, (int*)0, (int*)0, &tid[j]);
//			printf("3\n");
			if ( dd > 0){
//				printf("4\n");
				pvm_upkstr(arrOutputTask->outputSlaveTid[j]);
//				printf("outputSlaveTid %d sudah diterima\n", j);		
			}	

			ee = pvm_recv(tid[j], 3);
//			printf("5\n");
			pvm_bufinfo(ee, (int*)0, (int*)0, &tid[j]);
//			printf("6\n");
			if ( ee > 0){
//				printf("7\n");
				pvm_upkstr(arrOutputTask->outputSlaveTardiness[j]); 
//				printf("outputSlaveTardiness %d sudah diterima\n", j);		
			}
			
			ff = pvm_recv(tid[j], 4);
//			printf("5\n");
			pvm_bufinfo(ff, (int*)0, (int*)0, &tid[j]);
//			printf("6\n");
			if ( ff > 0){
//				printf("7\n");
				pvm_upkstr(arrOutputTask->outputSlaveNonDelay[j]); 
//				printf("outputSlaveNonDelay %d sudah diterima\n", j);		
			}
//			printf("PVM %d sudah diterima\n", j); 
		} 
//		bound += slice;
//	}
	
	printf("PVM sudah diterima\n");
	
/*	if(sisa == 0){
		return arrOutputTask->outputSlaveTid;
	}
	else{
		sprintf(charLowerBound, "%d", (task_size-sisa));		
		sprintf(charUpperBound, "%d", (task_size-1)); 
		
	/*	args[0] = charJmlRand;
		args[1] = charSlice;
		args[2] = charLowerBound;
		args[3] = charUpperBound;		
		
		printf("Yang mengerjakan sisa task %s-%s adalah: %s\n", charLowerBound, charUpperBound, hostname[nhost-1]);
		
		for(j=(task_size-sisa); j<task_size; j++){
			sprintf(task_tid, "%ld", arr_task[j].task_id);
			args[0] = task_tid;
			printf("PVM sisa %ld\n", arr_task[j].task_id);
			cc = pvm_spawn("./mergeSortSlave", args, 1, hostname[nhost-1], 1, &tid[j]); 
			printf("PVM keluar sisa1\n");
		}
		
		printf("PVM keluar sisa\n");
		
		for(i=(task_size-sisa); i<task_size; i++){
			arrOutputTask->outputSlaveTid[i] = malloc(15*sizeof(arrOutputTask->outputSlaveTid[i]));
			arrOutputTask->outputSlaveTardiness[i] = malloc(15*sizeof(arrOutputTask->outputSlaveTardiness[i]));

			cc = pvm_recv(tid[i], 2);
			pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
			pvm_upkstr(arrOutputTask->outputSlaveTid[i]);

			cc = pvm_recv(tid[i], 3);
			pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
			pvm_upkstr(arrOutputTask->outputSlaveTardiness[i]);
			printf("PVM %d sudah diterima\n", i);
		} 
	} */
	printf("\n");
		
/*	for(i=0; i<nhost; i++){
		printf("Hostname yg diassign: %s\n", hostname[i]);		
	} 
	printf("Hostname yg diassign: %s\n", hostname[nhost-1]);
	printf("\n");
	for(i=0; i<=nhost; i++){
		printf("Hostname yg didapat: %s\n", arrOutputTask->outputSlaveTid[i]);
		
	} 
	printf("\n"); */
		
	return 0;	
}