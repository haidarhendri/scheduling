// Merges two subarrays of task_t arr_task[task_size].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct task_t arr_task[task_size], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    	struct task_t L[n1];
	struct task_t R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr_task[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr_task[m + 1+ j];

    /* Merge the temp arr_taskays back into arr_task[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i].time_delay <= R[j].time_delay)
        {
            arr_task[k] = L[i];
            i++;
        }
        else
        {
            arr_task[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr_task[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr_task[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr_task to be sorted */
void mergeSort(struct task_t arr_task[task_size], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 

        // Sort first and second halves 
        mergeSort(arr_task, l, m); 
        mergeSort(arr_task, m+1, r); 
  
        merge(arr_task, l, m, r); 
    } 
} 
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
  
