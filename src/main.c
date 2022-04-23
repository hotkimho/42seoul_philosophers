#include "../include/philosophers.h"
int	get_time(struct timeval start);

int	get_time(struct timeval start)
{
	struct timeval current;
	gettimeofday(&current, NULL);

	/*
	구조체에 값 저장해놓기
	*/
	unsigned long long startTime = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	unsigned long long currentTime = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return currentTime - startTime;
}


int main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (FAILURE);



}


