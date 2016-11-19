
/******************************************************************************
 *
 * PROJECT: FIFO
 * COPYRIGHT - Do what ever you want!!!
 *
 * FILENAME: fifo.h
 *
 * ABSTRACT:
 *
 ******************************************************************************/

/* Standard Includes */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/******************************************************************************
 * FUNCTION DECLARATION
 ******************************************************************************/

int 	makeFIFO(const char *);
void 	cleanupFIFO(int , const char *);
int 	writeFIFO(int , const char *, size_t);
int 	readFIFO(int , char *, size_t);
int 	openFIFO(const char *);
int 	lock();
int 	unlock();

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
