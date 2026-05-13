#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "path.h"

bool path_join(char * buffer, size_t buffer_len, const char * parent, const char * child) {
	const size_t parent_len_tmp = strlen(parent);
	const size_t child_len = strlen(child);
	const size_t parent_len = parent[parent_len_tmp - 1] == '/' ? parent_len_tmp - 1 : parent_len_tmp;

	if (parent_len + child_len + 1 > buffer_len) {
		return false;
	}
	strncpy(buffer, parent, parent_len);
	buffer[parent_len] = '/';
	strcpy(buffer + parent_len + 1, child);

	return true;
}
