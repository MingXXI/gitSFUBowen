// Dr. Fraser's test code for custom string functions.
#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Custom testing framework
 */
// Track results:
static int numTests = 0;
static int numTestPassed = 0;

// Macro to allow us to get the line number, and argument's text:
#define TEST(arg) test_internal((arg), __LINE__, #arg)

// Actual function used to check success/failure:
void test_internal(_Bool success, int lineNum, char* argStr) {
	numTests++;
	if (!success) {
		printf("ERROR %4d: test on line %d failed: %s\n",
				numTestPassed, lineNum, argStr);
	} else {
		numTestPassed++;
	}
}

/*
 * Prototypes
 */
#define BIG_STRING_LENGTH (1024*1024)
void testMyStrLen(void);
void testMyStrCpy(void);
void testMyStrCpyWith(char* source);
void testMyStrCmp(void);
void testMyStrDup(void);
void testMyStrDupWith(char* source);
char* makeBigString();

/*
 * Main() and routines
 */
int main()
{
	testMyStrLen();
	testMyStrCpy();
	testMyStrCmp();
	testMyStrDup();

	printf("\nExecution finished.\n");
	printf("%4d/%d tests passed.\n", numTestPassed, numTests);
	printf("%4d/%d tests FAILED.\n", numTests - numTestPassed, numTests);
	return 0;
}


void testMyStrLen()
{
	TEST(mystrlen("") == 0);
	TEST(mystrlen(" ") == 1);
	TEST(mystrlen("12") == 2);
	TEST(mystrlen("000") == 3);
	TEST(mystrlen("a\nb\tc d") == 7);
	TEST(mystrlen("123\0xyz") == 3);
	TEST(mystrlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()") == 46);

	char *bigString = makeBigString();
	TEST(mystrlen(bigString) == BIG_STRING_LENGTH);
	free(bigString);

}

void testMyStrCpy()
{
	testMyStrCpyWith("");
	testMyStrCpyWith(" ");
	testMyStrCpyWith("1");
	testMyStrCpyWith("12345");
	testMyStrCpyWith("0");
	testMyStrCpyWith("a\nb\tc d");
	testMyStrCpyWith("123\0xyz");
	testMyStrCpyWith("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()");

	char *bigString = makeBigString();
	testMyStrCpyWith(bigString);
	free(bigString);
}
void testMyStrCpyWith(char* source)
{
	const char FILL_CHAR = 'z';
	int newSize = strlen(source) + 3; // Null, start check, end check
	char *buffer = malloc(sizeof(*buffer) * newSize);
	memset(buffer, FILL_CHAR, newSize);

	char *copyStringTo = buffer + 1;
	char *result = mystrcpy(copyStringTo, source);

	TEST(result == copyStringTo);
	TEST(strcmp(copyStringTo, source) == 0);
	if (strcmp(copyStringTo, source) != 0) {
		printf("\tError with string: %s\n", source);
	}
	TEST(buffer[0] == FILL_CHAR);
	TEST(buffer[newSize-2] == '\0');
	TEST(buffer[newSize-1] == FILL_CHAR);
	free(buffer);
}

void testMyStrCmp(){
	TEST(mystrcmp("", "") == 0);
	TEST(mystrcmp("", "a") == -1);
	TEST(mystrcmp("a", "") == 1);
	TEST(mystrcmp("a", "a") == 0);
	TEST(mystrcmp("ab", "ab") == 0);
	TEST(mystrcmp("ab\tcd e f", "ab\tcd e f") == 0);
	TEST(mystrcmp("ab\tcd e f\0fg", "ab\tcd e f") == 0);
	TEST(mystrcmp("ab\tcd e f", "ab\tcd e f\0fg") == 0);
	TEST(mystrcmp("ab", "ac") == -1);
	TEST(mystrcmp("ac", "ab") == 1);
	TEST(mystrcmp("a", "ab") == -1);
	TEST(mystrcmp("ab", "a") == 1);
	TEST(mystrcmp("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()",
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()") == 0);
	TEST(mystrcmp("abc", "ABC") == 1);
	TEST(mystrcmp("ABC", "abc") == -1);

	char *bigString = makeBigString();
	TEST(mystrcmp(bigString, bigString) == 0);
	TEST(mystrcmp(bigString, "") == 1);
	TEST(mystrcmp("", bigString) == -1);
	TEST(mystrcmp(bigString, "x") == 1);
	TEST(mystrcmp("x", bigString) == -1);
	free(bigString);
}

void testMyStrDup()
{
	testMyStrDupWith("");
	testMyStrDupWith(" ");
	testMyStrDupWith("0");
	testMyStrDupWith("123");
	testMyStrDupWith("a\nb\tc d");
	testMyStrDupWith("123\0xyz");
	testMyStrDupWith("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()");

	char *bigString = makeBigString();
	testMyStrDupWith(bigString);
	testMyStrDupWith(bigString);
	free(bigString);
}
void testMyStrDupWith(char* source)
{
	char *result = mystrdup(source);

	TEST(result != source && strcmp(result, source) == 0);
	if (strcmp(result, source) != 0) {
		printf("\tError with string: %s\n", source);
	}

	if (result != 0) {
		free(result);
	}
}


char* makeBigString()
{
	char *bigString = malloc(BIG_STRING_LENGTH * sizeof(*bigString) + 1);
	memset(bigString, 'x', BIG_STRING_LENGTH);
	bigString[BIG_STRING_LENGTH] = '\0';
	return bigString;
}




