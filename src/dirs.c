#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dirs.h"
#include "path.h"

/**
 * The namespace for this application.
 */
static const char * app_folder = "wtf-is";

const char * system_data_dir = "/usr/share/wtf-is";

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
