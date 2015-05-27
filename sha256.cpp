// Example taken from:
// http://stackoverflow.com/a/2458382
// gcc  -lcrypto

#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>
#include <errno.h>

#include <openssl/sha.h>

void sha256_string(const char *string, char outputBuffer[65])
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, string, strlen(string));
	SHA256_Final(hash, &sha256);

	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[64] = 0;
}

int sha256_file(const char *path, char outputBuffer[65])
{
	FILE *file = fopen(path, "rb");
	if (!file) {
		return -534;
	}
	const int bufSize = 32768;

	unsigned char *buffer = (unsigned char*)malloc(bufSize);
	if(!buffer) {
		return ENOMEM;
	}

	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);

	int bytesRead = 0;
	while((bytesRead = fread(buffer, 1, bufSize, file))) {
		SHA256_Update(&sha256, buffer, bytesRead);
	}
	SHA256_Final(hash, &sha256);

	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[64] = 0;

	fclose(file);
	free(buffer);
	return 0;
}

int main()
{
	char buffer[65] = {0};
	// sha256_string("kgaipal", buffer);
	sha256_file("/tmp/bomgar-rep.exe", buffer);
	printf("%s\n", buffer);

	return 0;
}
