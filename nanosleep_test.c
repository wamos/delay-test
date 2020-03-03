#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <x86intrin.h>

static inline uint64_t getNanoSecond(struct timespec* tp){
        //clock_gettime(CLOCK_MONOTONIC, tp);
		clock_gettime(CLOCK_REALTIME, tp);
        return (1000000000) * (uint64_t)tp->tv_sec + tp->tv_nsec;
}

static inline void realnanosleep(uint64_t times_of_gettime, struct timespec* tp){
	for(uint64_t i = 0 ; i < times_of_gettime; i++)
		clock_gettime(CLOCK_REALTIME, tp);
}

static inline void clocksleep(uint64_t times_of_gettime){
	for(uint64_t i = 0 ; i < times_of_gettime; i++){
		//_mm_pause();
		//asm volatile("nop");
		__rdtsc();
	}	
}

int main(int argc, char* argv[]){
	struct timespec ts1, ts2, delay_timespec;
	delay_timespec.tv_sec  = 0;
	delay_timespec.tv_nsec = 10000;
	const char* filename = argv[1];   
	FILE* fp = fopen(filename, "w+");

	for(int i=0; i<1000000; i++){
		uint64_t start = getNanoSecond(&ts1);
		//nanosleep(&delay_timespec, NULL);
		//clock_nanosleep(CLOCK_REALTIME, 0, &delay_timespec, NULL);
		//clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &delay_timespec, NULL);
		realnanosleep(560, &delay_timespec);	
		uint64_t end = getNanoSecond(&ts2);
		fprintf(fp,"%" PRIu64 "\n", end - start); // test clock_nanosleep
	}	

	return 0;
}
