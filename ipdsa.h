int time_delayIpdsa(int dl, int et)
{
	return dl - et;
}

int tardiness(int dl, int finish_time)
{
	return dl - finish_time;
}

int avg_tardiness(int sum_tardiness, int n_task)
{
	return sum_tardiness / n_task;
}
