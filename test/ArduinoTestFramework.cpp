#include "ArduinoTestFramework.h"

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

int ICR1;

/* Obtain a backtrace and print it to stdout. */
//Code from GNU example found at http://www.gnu.org/software/libc/manual/html_node/Backtraces.html
void print_trace(void)
{
	void *array[10];
	size_t size;
	char **strings;
	size_t i;

	size = backtrace(array, 10);
	strings = backtrace_symbols(array, size);

	printf("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		fprintf(stderr, "%s\n", strings[i]);

	free(strings);
}


#include <execinfo.h>

bool ArduinoTestFramework::assert(bool value, char[] funcName, char[] file, int line);
{
	if (assertVal) return true;

	fprintf(stderr, "Assert failed in %s at line %d of file %s. Stack trace:", funcName, line, file);
	print_trace;
	return false;
}