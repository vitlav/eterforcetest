#include <windows.h>
#include "eterforcetest.h"

/*
  Measure function work time
  http://bugs.etersoft.ru/show_bug.cgi?id=3031
*/

FILE *measure_f;
void measure_init()
{
	measure_f = fopen("eterforcetest.log","w+");
}

void measure_report()
{
	int i, count = 0;
	double s = 0;
	for (i = 0 ; et_measure[i].name ; i++) {
		if (!et_measure[i].res)
			continue;
		s += ((double)et_measure[i].res / et_measure[i].ms);
		count++;
	}
	s /= count;
	/* TODO: ��������� ���, � ��������� ������� ��� ��������� �� ������� */
	printf ("Average: %2.02f\n", s);
	printf ("\nNormalize result:\n");
	for (i = 0 ; et_measure[i].name ; i++) {
		if (et_measure[i].ms)
			printf("    %25s %2.02f\n", et_measure[i].name, (((double)et_measure[i].res / et_measure[i].ms)/s));
	}
	fclose(measure_f);
}

int main()
{
	measure_init();
	//test_string();
	//test_encoding();
	test_file();
	//test_time();
	test_memory();
	//test_window();
	//test_font();
	measure_report();
}
