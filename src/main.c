#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "dirs.h"
#include "path.h"

static void print_usage();
static int on_dir(const char * dir_path, const char * acronym);
static int on_line(const char * line, const char * acronym, const char * category);
static bool is_help(const char * arg);

int main(int argc, char ** argv) {
	int result;

	if (argc > 1 && is_help(argv[1])) {
		print_usage(stdout, argv[0]);
		return 0;
	}
	if (argc != 3) {
		print_usage(stderr, argv[0]);
		return 1;
	}

	if ((result = on_dir(system_data_dir, argv[2])) != 0) {
		return result;
	}

	return on_dir(user_data_dir(), argv[2]);
}

int on_dir(const char * dir_path, const char * acronym) {
	int result = 0;
	DIR * dir;
	FILE * file;
	struct dirent * entry;
	char * filename;
	const size_t path_buf_size = 256;
	char path_buffer[path_buf_size];
	const size_t line_buf_size = 256;
	char line_buf[line_buf_size];
	size_t filename_size;

	if (dir_path == NULL) {
		// NOTE Nothing to do.
		return 0;
	}

	if ((dir = opendir(dir_path)) == NULL) {
		// NOTE We skip on errors, because the directory may not exist.
		return 0;
	}

	while ((entry = readdir(dir)) != NULL) {
		filename = entry->d_name;
		if (strcmp(".", filename) == 0 || strcmp("..", filename) == 0) {
			continue;
		}
		filename_size = strlen(filename);
		// NOTE Filename must have at least 5 characters and end in `.txt`. The reason
		//		for 5 characters is to ensure it has a name before the `.txt`.
		if (filename_size < 5 || strcmp(".txt", filename + filename_size - 4) != 0) {
			// NOTE Wrong file extension; skipping.
			continue;
		}
		if (!path_join(path_buffer, path_buf_size, dir_path, filename)) {
			// NOTE Path too long, we'll just skip it.
			continue;
		}
		file = fopen(path_buffer, "r");
		if (file == NULL) {
			// NOTE Couldn't open file, continuing.
			continue;
		}

		// NOTE: Strip the extension from the filename
		filename[filename_size - 4] = '\0';

		while(fgets(line_buf, line_buf_size, file) != NULL) {
			if ((result = on_line(line_buf, acronym, filename)) != 0) {
				return result;
			}
		}
	}

	closedir(dir);

	return 0;
}

const char case_diff = 'a' - 'A';
/**
 * Normalizes a char to make ASCII characters uppercase. Useful for simple equality matching.
 */
static char case_normalize(const char c) {
	if ('a' <= c && c <= 'z') {
		return c - case_diff;
	}
	return c;
}

static int on_line(const char * line, const char * acronym, const char * category) {
	// NOTE: Format is `ACRONYM: definition 1|definition 2|...`
	const char case_diff = 'a' - 'A';
	char left;
	char right;
	size_t index;

	for (index = 0; (left = acronym[index]) != '\0' && (right = line[index]) != '\0'; ++index) {
		// NOTE Normalize case for case-insensitive matching.
		if (case_normalize(left) != case_normalize(right)) {
			// NOTE Acronym is not equal.
			return 0;
		}
	}
	if ((right = line[index]) != ':') {
		// NOTE Either the acronym on the line is longer, or it is an invalid line.
		return 0;
	}
	if ((right = line[++index]) != ' ') {
		// NOTE Definitely an invalid line.
		return 1;
	}

	printf("%s:\n", acronym);
	printf("\t%s:\t", category);
	for (index += 1; (right = line[index]) != '\0'; ++index) {
		if (right == '|') {
			printf("\n\t%s:\t", category);
		} else {
			printf("%c", right);
		}
	}
	printf("\n");

	return 0;
}

static void print_usage(FILE * stream, const char * exe) {
	fprintf(stream, "USAGE:\n");
	fprintf(stream, "\t%s is <ACRONYM>\n", exe);
}

static bool is_help(const char * arg) {
	return strcmp("-h", arg) == 0 || strcmp("--help", arg) == 0;
}
