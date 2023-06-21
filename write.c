#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define NBYTES 1000
#define WRSTR "Hello world!"

#define ERR(x) fprintf(stderr, "%s: %s (code %d)\n", x, strerror(errno), errno)

int main() {
	key_t key = rand();

	int shmid = shmget(key, NBYTES, IPC_CREAT | 0600);
	if (shmid < 0) {
		ERR("shmget");
		return EXIT_FAILURE;
	}

	void *shmaddr = shmat(shmid, NULL, 0);
	if (shmaddr == (void *)-1) {
		ERR("shmat");
		goto cleanup;
	}

	strncpy(shmaddr, WRSTR, NBYTES);

	int err = shmdt(shmaddr);
	if (err != 0) {
		ERR("shmdt");
		goto cleanup;
	}

	err = printf("%d\n", key);
	if (err < 0) {
		ERR("printf");
		goto cleanup;
	}

	return EXIT_SUCCESS;

cleanup:
	if (shmctl(shmid, IPC_RMID, NULL) != 0) {
		ERR("shmctl");
	}
	return EXIT_FAILURE;
}
