/* standard includes */
#include <stdio.h>
#include <string.h>
/* module includes */
#include "../lib/fifo.h"
/* macros and other declarations */
#define NAME "hello world!"

int main()
{
	int fd, retval;
	void *handle = NULL;
	char str[100] = {0};
	fd = makeFIFO("/tmp/fifo1");
	if (fd == -1) return (0);

	/* write to fifo. */
	retval = lock();
	if (retval == -1) goto error;
	if (writeFIFO(fd, NAME, strlen(NAME)) == -1)
		goto error;
	unlock();
	
	/* read from fifo. */
	retval = lock();
	if (retval == -1) goto error;
	if (readFIFO(fd, str, strlen(NAME)) == -1)
		goto error;
	unlock();

	printf("Name: %s\n", str);

	/* cleanup. */
	cleanupFIFO(fd, "/tmp/fifo1");

	return (EXIT_SUCCESS);

error:
	/* cleanup on error. */
	cleanupFIFO(fd, "/tmp/fifo1");
	return (EXIT_FAILURE);
}
