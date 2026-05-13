#ifndef WTF_PATH_H
#define WTF_PATH_H
#include <stdbool.h>
#include <stdio.h>
/**
 * Joins a parent and child path. Very similar to appending strings, but handles trailing `/`.
 *
 * Will not append beyond the buffer length. Returns `false` if the full path could not be created.
 */
bool path_join(char * buffer, size_t buffer_len, const char * parent, const char * child);
#endif
