#ifndef WTF_DIRS_H
#define WTF_DIRS_H
/**
 * The system-level data directory.
 */
extern const char * system_data_dir;

/**
 * Gets the user's data directory.
 */
const char * user_data_dir();
#endif
