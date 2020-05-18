int nhost = 3;

struct outputTask
{
	char **outputSlaveMsec;
	char **outputSlaveSize;
};
struct outputTask arrOutputTask[4];

char **getDariSlave(int nhost, char **hostname, int jmlRand){
	int cc, dd, ee, *tid, i, j, sisa, slice, bound;
	
	arrOutputTask->outputSlaveMsec = malloc((nhost+1)*sizeof(arrOutputTask->outputSlaveMsec));
	arrOutputTask->outputSlaveSize = malloc((nhost+1)*sizeof(arrOutputTask->outputSlaveSize));
	
	char charSlice[9], charLowerBound[9], charUpperBound[9], charJmlRand[9], task_tid[9];
	char **args = (char**) malloc(4*sizeof(char*));
	tid = (int*) malloc((task_sizePvm+1)*sizeof(int));
	slice = task_sizePvm/nhost;
	sisa = task_sizePvm%nhost;
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
		//	printf("TID %d adl %ld\n", j, arr_task[j].task_id);
			sprintf(task_tid, "%ld", arr_task[j].task_id);
			args[0] = task_tid;
			printf("PVM %d\n", j);
			cc = pvm_spawn("./mergeSortSlave", args, 1, hostname[i], 1, &tid[j]);
		}
		bound += slice;	
		sleep(1);
	}
	
	printf("PVM sudah dikirim\n");
	
	bound = 0;
	for(i=0; i<nhost; i++){		
		for(j=bound; j<=(bound+slice-1); j++){
			arrOutputTask->outputSlaveMsec[j] = malloc((task_sizePvm-sisa)*sizeof(arrOutputTask->outputSlaveMsec[j]));
			arrOutputTask->outputSlaveSize[j] = malloc((task_sizePvm-sisa)*sizeof(arrOutputTask->outputSlaveSize[j]));

			dd = pvm_nrecv(tid[j], 2);
			//pvm_bufinfo(dd, (int*)0, (int*)0, &tid[j]);
			if ( dd > 0){
				pvm_upkstr(arrOutputTask->outputSlaveMsec[j]);
				printf("outputSlaveMsec %d sudah diterima\n", j);		
			}	

			ee = pvm_nrecv(tid[j], 3);
			//pvm_bufinfo(ee, (int*)0, (int*)0, &tid[j]);
			if ( ee > 0){
				pvm_upkstr(arrOutputTask->outputSlaveSize[j]); 
				printf("outputSlaveSize %d sudah diterima\n", j);		
			}			
			printf("PVM %d sudah diterima\n", j);
		}
		bound += slice;
	}
	
	printf("PVM sudah diterima\n");
	
/*	if(sisa == 0){
		return arrOutputTask->outputSlaveMsec;
	}
	else{
		sprintf(charLowerBound, "%d", (task_sizePvm-sisa));		
		sprintf(charUpperBound, "%d", (task_sizePvm-1)); 
		
	/*	args[0] = charJmlRand;
		args[1] = charSlice;
		args[2] = charLowerBound;
		args[3] = charUpperBound;		
		
		printf("Yang mengerjakan sisa task %s-%s adalah: %s\n", charLowerBound, charUpperBound, hostname[nhost-1]);
		
		for(j=(task_sizePvm-sisa); j<task_sizePvm; j++){
			sprintf(task_tid, "%ld", arr_task[j].task_id);
			args[0] = task_tid;
			printf("PVM sisa %ld\n", arr_task[j].task_id);
			cc = pvm_spawn("./mergeSortSlave", args, 1, hostname[nhost-1], 1, &tid[j]); 
			printf("PVM keluar sisa1\n");
		}
		
		printf("PVM keluar sisa\n");
		
		for(i=(task_sizePvm-sisa); i<task_sizePvm; i++){
			arrOutputTask->outputSlaveMsec[i] = malloc(15*sizeof(arrOutputTask->outputSlaveMsec[i]));
			arrOutputTask->outputSlaveSize[i] = malloc(15*sizeof(arrOutputTask->outputSlaveSize[i]));

			cc = pvm_recv(tid[i], 2);
			pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
			pvm_upkstr(arrOutputTask->outputSlaveMsec[i]);

			cc = pvm_recv(tid[i], 3);
			pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
			pvm_upkstr(arrOutputTask->outputSlaveSize[i]);
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
		printf("Hostname yg didapat: %s\n", arrOutputTask->outputSlaveMsec[i]);
		
	} 
	printf("\n"); */
		
	return 0;	
}