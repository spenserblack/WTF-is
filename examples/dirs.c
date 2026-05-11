#include "../src/dirs.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	const char * user_dir = user_data_dir();
	printf("Data dirs:\n");
	printf("\t%s\n", system_data_dir);
	if (user_dir != NULL) {
		printf("\t%s\n", user_dir);
	}

	return 0;
}
