unsigned int cnt;

double dbl;
void i_fnc_4_2(void);
void i_fnc_4_2(void)
{
    if(dbl > 1.0)
    {
        dbl = 1.0;
    }
}

#if defined(__CCRX__)

#if 0 /* 1: Without SmartConfigurator, 0: With SmartConfigurator. */

#include <stdio.h>

#int write(int fd, const void *buf, size_t byte)
{
    (void) fd; (void) buf; (void) byte;
    return -1;
}

int read(int fd, void *buf, size_t byte)
{
    (void) fd; (void) buf; (void) byte;
    return -1;
}

#endif

#endif

#if defined(__GNUC__)

#if 0 /* 1: Without SmartConfigurator, 0: With SmartConfigurator. */

#include <unistd.h>
#include <sys/stat.h>

int write(int fd, const void *buf, size_t byte)
{
    (void) fd; (void) buf; (void) byte;
    return -1;
}

int read(int fd, void *buf, size_t byte)
{
    (void) fd; (void) buf; (void) byte;
    return -1;
}

off_t lseek (int fd, off_t offset, int whence)
{
    (void) fd; (void) offset; (void) whence;
    return -1;
}

int isatty(int fd)
{
    (void) fd;
    return 0;
}

int close(int fd)
{
    (void) fd;
    return -1;
}

int fstat(int fd, struct stat *buf)
{
    (void) fd; (void) buf;
    return -1;
}

#endif

#include <stdlib.h>

void abort(void)
{
   exit(-1);
}

#endif
