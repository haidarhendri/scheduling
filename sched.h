#define _GNU_SOURCE
#define gettid() syscall(__NR_gettid)
#define SCHED_DEADLINE       6

#ifdef __x86_64__
#define __NR_sched_setattr           314
#define __NR_sched_getattr           315
#endif

static volatile int done;

struct sched_attr {
	__u32 size;
	__u32 sched_policy;
	__u64 sched_flags;
	__s32 sched_nice;
	__u32 sched_priority;
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid,
	const struct sched_attr *attr,
	unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
	struct sched_attr *attr,
	unsigned int size,
	unsigned int flags)
{
     return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

struct sched_attr attr = {
	.size = sizeof(attr),
	.sched_flags = 0,
	.sched_nice = 0,
	.sched_priority = 0,
	.sched_policy = SCHED_DEADLINE,
	.sched_runtime = 10 * 1000 * 1000,
	.sched_deadline = 30 * 1000 * 1000,
	.sched_period = 30 * 1000 * 1000,
};

struct task_t
{
	long int task_id;
	int arrival_time;
	int eet;
	int deadline;
	int time_delay;
	int finishing_time;
	int tardiness;
};
struct task_t arr_task[1000];

void *run_deadline(void *data)
{
//	struct task_t arr_task[task_size];
	int x = 0;
	unsigned int flags = 0;
	int ret;
/*	long int i;

	i = *(long int *)data;
	
	for(int j = 0; j < task_size; j++)
	{
		if(arr_task[j].task_id == i)
		{
			arr_task[j].task_id = gettid();
			printf("TID saya adl %ld\n", arr_task[j].task_id);
			
		}
		printf("TID saya adl %ld\n", arr_task[j].task_id);
		printf("TID saya adl %ld\n", i);
	}
*/	

	printf("deadline thread started [%ld]\n", gettid());

//	printf("runtime is %lld ms\n", attr.sched_runtime/CLOCKS_PER_SEC);
//	printf("deadline run_deadline adalah %lld ms\n", attr.sched_deadline/CLOCKS_PER_SEC);
//	printf("period is %lld ms\n", attr.sched_period/CLOCKS_PER_SEC);

	ret = sched_setattr(0, &attr, flags);

//	if (ret < 0) {
//		done = 0;
//		perror("sched_setattr");
//		exit(-1);
//	}
//	sleep(1000);
	while(!done)
	{
		x++;
	}
//	retur = 100;
	pthread_exit(0);

//	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
}
