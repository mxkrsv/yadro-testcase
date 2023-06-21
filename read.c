#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define NBYTES 1000

#define ERR(x) fprintf(stderr, "%s: %s (code %d)\n", x, strerror(errno), errno)

int main() {
	key_t key;
	int err = scanf("%d", &key);
	if (err < 1) {
		ERR("scanf");
		return EXIT_FAILURE;
	}

	int shmid = shmget(key, NBYTES, 0);
	if (shmid < 0) {
		ERR("shmget");
		return EXIT_FAILURE;
	}

	void *shmaddr = shmat(shmid, NULL, SHM_RDONLY);
	if (shmaddr == (void *)-1) {
		ERR("shmat");
		goto cleanup;
	}

	err = printf("%.*s\n", NBYTES, (char *)shmaddr);
	if (err < 0) {
		ERR("printf");
		goto cleanup;
	}

	err = shmdt(shmaddr);
	if (err != 0) {
		ERR("shmdt");
		goto cleanup;
	}

	err = shmctl(shmid, IPC_RMID, NULL);
	if (err != 0) {
		ERR("shmctl");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

cleanup:
	if (shmctl(shmid, IPC_RMID, NULL) != 0) {
		ERR("shmctl");
	}
	return EXIT_FAILURE;
}
