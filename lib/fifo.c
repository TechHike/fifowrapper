/******************************************************************************
 *
 * PROJECT: FIFO
 * COPYRIGHT - Do what ever you want!!!
 *
 * FILENAME: fifo.h
 *
 * ABSTRACT:
 * 1.0 - Wrapper for FIFO.
 * 1.1 - Making open_fifo to openFIFO and public function, coz. if,
 *       other process need access to file this function will return
 *       the fd to existing file.
 * 1.2 - Adding lock mechanism.
 *
 ******************************************************************************/

/* Standard Includes */
#include <fcntl.h>
#include <pthread.h>
/* Module Includes */
#include "fifo.h"

/******************************************************************************
 * MACROS/VARIABLES 
 ******************************************************************************/

#define check_error(A, ...) \
    if (A) { \
        fprintf(stderr, "%s\n", __VA_ARGS__); \
        goto error; \
    }

#define SAFE_FREE(X) \
    free(X); \
    X = NULL;

static pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;

/******************************************************************************
 * FUNCTION DECLARATION
 ******************************************************************************/

static int createFIFO(const char *path);

/******************************************************************************
 * FUNCTION DEFINITION
 ******************************************************************************/

/* PRIVATE FUNCTION */
static int createFIFO(const char *path)
{
	int retval;
	retval = mkfifo(path, 0600);
	check_error(retval, strerror(errno));
	return (0);

error:
	return (-1);
}

/* PUBLIC FUNCTION */
int openFIFO(const char *path)
{
	int fd;
	fd = open(path, O_RDWR);
	/* open returns -1 on failure. */
	if (fd == -1) goto error;
	/* open successful. */
	return fd;

error:
	return (-1);
}

int makeFIFO(const char *path)
{
	int retval, fd;
	/* create fifo */
	retval = createFIFO(path);
	check_error(retval, "FIFO creation failure.");
	/* open fifo file and return fd. 
	 * -1 on failure. */
	fd = openFIFO(path);
	return fd;

error:
	return (-1);
}

void cleanupFIFO(int fd, const char *path)
{
	close(fd);
	unlink(path);
}

int writeFIFO(int fd, const char *data, size_t bytes)
{
	const char *t_ptr = NULL;
	size_t t_bytes = 0;
	if ((!data) || (bytes < 1))
		goto error;

	t_ptr = data;
	t_bytes = write(fd, t_ptr, bytes);
	check_error((t_bytes != bytes), "FIFO write failed.");
	/* successful write */
	return (0);

error:
	return (-1);
}

int readFIFO(int fd, char *data, size_t bytes)
{
	char *t_ptr = NULL;
	size_t t_bytes = 0;
	if ((!data) || (bytes < 1))
		goto error;

	t_ptr = (char *)malloc(bytes);
	check_error((t_ptr == NULL), strerror(errno));

	t_bytes = read(fd, t_ptr, bytes);
	check_error((t_bytes != bytes), "FIFO read failed.");
	memcpy(data, t_ptr, bytes);

	SAFE_FREE(t_ptr);
	return (0);

error:
	if (t_ptr)
		SAFE_FREE(t_ptr);
	return (-1);
}

int lock()
{
	int retval;
	retval = pthread_mutex_trylock(&locker);
	check_error(retval, "Unable to obtain lock.");
	return (0);

error:
	return (-1);
}

int unlock()
{
	int retval;
	retval = pthread_mutex_unlock(&locker);
	check_error(retval, "Unable to free lock.");
	return (0);

error:
	return (-1);
}

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
