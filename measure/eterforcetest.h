#include <windows.h>
//#include <time.h>
#include <string.h>
#include <stdio.h>

#define MEASURE_COUNT 7000000

#define REPEAT_MEASURE 5

static int measure_count;
static int int_count;
static char measure_name[20];
static DWORD measure_iresult[REPEAT_MEASURE];
static DWORD measure_result;
static DWORD time_start;
static DWORD time_end;
static int measure_divid;

extern FILE *measure_f;
void measure_init();

extern struct { char *name; int ms; int res;} et_measure[];

static inline void measure_start() {
	putchar('.'); fflush(stdout); 
	time_start = GetTickCount();
	/* Align to interval start */
	while (time_start == GetTickCount());
	time_start++;
}

static inline void measure_end() {
	time_end = GetTickCount();
	measure_iresult[measure_count] = time_end - time_start;
}

static inline void print_measure()
{
	int i, etres = 0;
	measure_result = 0;
	for (i = 0 ; i < REPEAT_MEASURE ; i++)
		measure_result += measure_iresult[i];
	measure_result /= REPEAT_MEASURE;
	for (i = 0 ; et_measure[i].name ; i++) {
		if (!strcmp(et_measure[i].name, measure_name)) {
			etres = et_measure[i].ms;
			et_measure[i].res = measure_result;
		}
	}
	if (!etres)
		etres = measure_result;
	printf("%5d ms (%2.02f) * %d (%.2fm iterations)\n\n", measure_result, ((double)measure_result)/etres, measure_divid, 0.000001*(MEASURE_COUNT*REPEAT_MEASURE)/measure_divid);
	fprintf( measure_f, "%20s %10d\n", measure_name, measure_result);
}

#define MSTART(ok, name, divid) \
	{ printf("Test for %15s ", name); \
	measure_divid = (divid); \
	strcpy(measure_name, name); \
	if (!(ok)) { \
		printf("skipping\n"); \
		time_start = 0;\
	} \
	else \
	for (measure_count = 0 ; measure_count < REPEAT_MEASURE ; measure_count++ ) { \
		measure_start(); \
		for(int_count = 0; int_count < MEASURE_COUNT/divid ; int_count++)

#define MEND \
		measure_end(); \
	} \
	if (time_start) \
		print_measure(); }



void test_string();
void test_file();
void test_window();
void test_font();
void test_time();
void test_memory();
void test_encoding();

