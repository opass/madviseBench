#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#define TIMER(val) do { \
  struct timeval tm; \
  gettimeofday(&tm, NULL); \
  val = tm.tv_sec * 1000 + tm.tv_usec/1000; \
} while(0)


int FILE_LENGTH = 0;

int doprocess(char *p)
{
  long starttime, endtime;
  TIMER(starttime);
  int nSum = 0;
  int i;
  for (i = 0; i < FILE_LENGTH; i++) {
    nSum += *p;
    p++;
  }
  TIMER(endtime);
  return (endtime - starttime);
}
void readWithoutMadvise(char *path)
{
  int fd = open(path, O_RDWR | O_EXCL);
  if (fd == -1) {
    perror("open error in readWithoutMadvise");
    return;
  }
  void *p = mmap(NULL, FILE_LENGTH, PROT_READ, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("map error in readWithoutMadvise");
    return;
  }
  close(fd);
  fd = -1;
  int interval = doprocess((char *)p);
  printf("read without madvise: %d ms\n", interval);
  if (munmap(p, FILE_LENGTH) == -1) {
    perror("unmap error in readWithoutMadvise");
    return;
  }
}
void readWithMadvise(char *path)
{
  int fd = open(path, O_RDWR | O_EXCL);
  if (fd == -1) {
    perror("open error in readWithoutMadvise");
    return;
  }
  void *p = mmap(NULL, FILE_LENGTH, PROT_READ, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("map error in readWithoutMadvise");
    return;
  }
  close(fd);
  fd = -1;
  if (madvise(p, FILE_LENGTH, MADV_WILLNEED | MADV_SEQUENTIAL) == -1) {
    perror("madvise error");
    return;
  }
  int interval = doprocess((char *)p);
  printf("read with madvise: %d ms\n", interval);
  if (munmap(p, FILE_LENGTH) == -1) {
    perror("unmap error in readWithoutMadvise");
    return;
  }
}

void getFileLength(char* path) {
    struct stat st;
    stat(path, &st);

    FILE_LENGTH = (int)st.st_size;  //set global variable FILE_LENGTH

    printf("This file has %d bytes", FILE_LENGTH);
}

int main(int argc, char* argv[])
{
  char *bigFilePath = argv[1];
  long int useMadvise = strtol(argv[2], NULL, 10);

  getFileLength(bigFilePath);

  if (useMadvise == 1) {
    readWithMadvise(bigFilePath);
  } else {
    readWithoutMadvise(bigFilePath);
  }
}
