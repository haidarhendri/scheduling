int generate_dl(int et)
{
	int arr, min, max;

	min = et + 1000;
	max = et + 3000;
	arr = rand() % (max + 1 - min) + min;

	return arr;
}

int generate_period(int et)
{
	int arr, min, max;

	min = (et + 3500);
	max = (et * 3);
	arr = rand() % (max + 1 - min) + min;

	return arr;
}