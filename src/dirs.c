#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dirs.h"

/**
 * The namespace for this application.
 */
static const char * app_folder = "wtf-is";

const char * system_data_dir = "/usr/share/wtf-is";

/**
 * Joins a parent and child path. Very similar to appending strings, but handles trailing `/`.
 *
 * Will not append beyond the buffer length. Returns `false` if the full path could not be created.
 */
static bool path_join(char * buffer, size_t buffer_len, const char * parent, const char * child) {
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

#define USER_DATA_DIR_BUFFER_LEN 256

/**
 * Buffer for storing the XDG data dir.
 */
static char user_data_dir_buffer[USER_DATA_DIR_BUFFER_LEN];

/**
 * Gets a namespaced directory under an environment variable path.
 */
static char * namespaced_user_data_dir(const char * env_key, const char * subdir) {
	const char * env_var = getenv(env_key);
	if (env_var == NULL) {
		return NULL;
	}
	if (path_join(user_data_dir_buffer, USER_DATA_DIR_BUFFER_LEN, env_var, subdir)) {
		return user_data_dir_buffer;
	} else {
		return NULL;
	}
}

/**
 * Gets the data dir based on `$XDG_DATA_HOME`.
 */
static char * xdg_data_dir() {
	return namespaced_user_data_dir("XDG_DATA_HOME", "wtf-is");
}

/**
 * Gets the default user data dir.
 */
static char * default_user_data_dir() {
	return namespaced_user_data_dir("HOME", ".local/share/wtf-is");
}

const char * user_data_dir() {
	char * dir = xdg_data_dir();
	if (dir == NULL) {
		dir = default_user_data_dir();
	}
	return dir;
}
