#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * handleFileErrors - checks for file-related errors.
 * @sourceFileDescriptor: source file descriptor.
 * @destinationFileDescriptor: destination file descriptor.
 * @arguments: command line arguments.
 * Return: no return.
 */
void handleFileErrors(int sourceFileDescriptor, int destinationFileDescriptor, char *arguments[])
{
	if (sourceFileDescriptor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", arguments[1]);
		exit(98);
	}
	if (destinationFileDescriptor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", arguments[2]);
		exit(99);
	}
}

/**
 * main - Entry point for the file copy program.
 * @argc: Number of command line arguments.
 * @argv: Command line arguments.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	int sourceFileDescriptor, destinationFileDescriptor, closeStatus;
	ssize_t bytesRead, bytesWritten;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: file_copy source_file dest_file\n");
		exit(97);
	}

	sourceFileDescriptor = open(argv[1], O_RDONLY);
	destinationFileDescriptor = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);
	handleFileErrors(sourceFileDescriptor, destinationFileDescriptor, argv);

	bytesRead = 1024;
	while (bytesRead == 1024)
	{
		bytesRead = read(sourceFileDescriptor, buffer, 1024);
		if (bytesRead == -1)
			handleFileErrors(-1, 0, argv);
		bytesWritten = write(destinationFileDescriptor, buffer, bytesRead);
		if (bytesWritten == -1)
			handleFileErrors(0, -1, argv);
	}

	closeStatus = close(sourceFileDescriptor);
	if (closeStatus == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close source file descriptor %d\n", sourceFileDescriptor);
		exit(100);
	}

	closeStatus = close(destinationFileDescriptor);
	if (closeStatus == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close destination file descriptor %d\n", destinationFileDescriptor);
		exit(100);
	}

	return 0;
}
