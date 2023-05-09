#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main ( void ) {
	char line[128], cmd[256], fullpath[256];
	char dirname[] = "/home/jstromberg/Development/loki/payload/tools/sandbox/function_checks/test";

	sprintf(cmd, "ls %s | sort -n", dirname);
	printf("cmd is now: %s\n", cmd);
	
	FILE * dirFiles = NULL;
	printf("dirFiles is now: %p\n", dirFiles);
	
	dirFiles = popen(cmd, "r");
	printf("dirFiles is now: %p\n", dirFiles);

	if(fgets(line, sizeof(line), dirFiles) != NULL) {
		printf("fgets pulled this to line: %s\n", line);
		printf("fullpath is now: %s\n", fullpath);
		int len = sprintf(fullpath, "%s/%s", dirname, line);
		if(fullpath[len-1] == '\n') {
			fullpath[len-1] = '\0';
		}
		printf("len is %d\n", len);
		printf("fullpath is now: %s\n", fullpath);
	}
	
	
	char findmnt_cmd[] = "findmnt / --raw --output=source -n";
	char emmc[] = "/dev/sda5";
	char sd[] = "/dev/sda6";
	FILE *pipe = popen(findmnt_cmd, "r");
	if (pipe == NULL) {
		fprintf(stderr, "Failed to open pipe for command '%s'\n", findmnt_cmd);
		return 1;
	}

	char buffer[MAX_BUFFER_SIZE];
	size_t n = 0;
	char *char_line = NULL;
	if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
		/* trim newline character  */
		n = strlen(buffer);
		if (n > 0 && buffer[n-1] == '\n') {
			buffer[n-1] = '\0';
		}

		/* extract source column */
		char *source = strtok(buffer, " ");

		/* match against source */
		if (strcmp(source, emmc) == 0) {
			printf("Match found: source=%s\n", source);
		}
	}

	return 0;
}
