#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "tokenize.h"
#include "parse.h"


int main(int argc, char *argv[])
{
	// Disable output buffering
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if (argc < 3)
	{
		fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
		fprintf(stderr, "Usage: ./your_program parse <filename>\n");
		return 1;
	}

	int status = 0;
	const char *command = argv[1];

	if (strcmp(command, "tokenize") == 0)
	{
		char *file_contents = read_file_contents(argv[2]);
		status = (tokenize(file_contents) == 0) ? 0 : 65;
		free(file_contents);
	}
	else if (strcmp(command, "parse") == 0)
	{
		char *file_contents = read_file_contents(argv[2]);
		status = (parse(file_contents) == 0) ? 0 : 65;
		free(file_contents);
	}
	else
	{
		fprintf(stderr, "Unknown command: %s\n", command);
		return 1;
	}

	return status;
}
