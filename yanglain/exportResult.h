void exportResult()
{
	FILE *of;
	of = fopen("2000_task.txt", "w");

	if (of == NULL)
	{
		fprintf(stderr, "\n error to open  file\n");
		exit(1);
	}

	for (int m = 0; m <= task_size; m++)
	{
		fprintf(of, "%ld,%d,%d ns,%d ns,%d ns,%d,%d\n", arr_task[m].task_id, arr_task[m].arrival_time, arr_task[m].eet, arr_task[m].deadline, arr_task[m].time_delay, arr_task[m].finishing_time, arr_task[m].tardiness);
	}

	if(fprintf != 0)
		printf("Berhasil export result !\n");
	else
		printf("Error writing to file !\n");
	fclose(of);
}

int print()
{
	for (int i = 0; i < task_size; i++)
	{
		printf("DL %d adalah %d\n", i, arr_task[i].deadline);
	}
	return 0;
}
