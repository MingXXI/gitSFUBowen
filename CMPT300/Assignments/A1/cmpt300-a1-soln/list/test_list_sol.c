#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>


/*
 * Custom testing framework
 */
// Track results:
static int numTests = 0;
static int numTestPassed = 0;

// Macro to allow us to get the line number, and argument's text:
#define TEST(arg) testInternal((arg), __LINE__, #arg)

// Actual function used to check success/failure:
void testInternal(_Bool success, int lineNum, char* argStr) {
	numTests++;
	if (!success) {
		printf("ERROR %4d: test on line %d failed: %s\n",
				numTests, lineNum, argStr);
	} else {
		numTestPassed++;
	}
}


/*
 * Prototypes
 */
void dumpList(struct nodeStruct *head);
void printResults(char *title);

#define TERMINATOR -42
void testListSortFromArray(int data[]);
void testInsertAtHead();
void testInsertAtTail();
void testAddManyToHeadOrTail(_Bool addToHead);
void testSort();

/*
 * Main()
 */
int main(int argc, char** argv)
{
	const int NUM_TESTS = 5;
	char* ALL[] = {
			"daProgramName goes here",
			"1",
			"2",
			"3",
			"4",
			"5",
	};

	printf("Usage:\n");
	printf("  %s    -- Run all tests\n", argv[0]);
	printf("  %s 1 3 4   -- Run tests #1, 3, 4 only\n", argv[0]);
	printf("\n\n");
	if (argc == 1) {
		argc = 1 + NUM_TESTS;
		argv = ALL;
	}


	for (int argIdx = 1; argIdx < argc; argIdx ++) {
		if (strcmp(argv[argIdx], "1") == 0) {
			testInsertAtHead();
			printResults("... After insert @ head:\n");
		}
		if (strcmp(argv[argIdx], "2") == 0) {
			testInsertAtTail();
			printResults("... After insert @ tail:\n");
		}
		if (strcmp(argv[argIdx], "3") == 0) {
			testAddManyToHeadOrTail(true);
			printResults("... After insert many to head:\n");
		}
		if (strcmp(argv[argIdx], "4") == 0) {
			testAddManyToHeadOrTail(false);
			printResults("... After insert many to tail:\n");
		}
		if (strcmp(argv[argIdx], "5") == 0) {
			testSort();
			printResults("... After sort:\n");
		}
	}

	printResults("\nExecution finished.\n");
	return 0;
}

/*
 * Helper Functions
 */
void dumpList(struct nodeStruct *head)
{
	struct nodeStruct *current = head;
	while (current != NULL) {
		printf("%5d", current->item);
		current = current->next;
	}
	printf("\n");
}


void printResults(char *title)
{
	static int testsOnLastPass = 0;
	int testsSinceLast = numTests - testsOnLastPass;
	testsOnLastPass = numTests;

	printf("%s", title);
	printf("%4d/%d tests passed.\n", numTestPassed, numTests);
	printf("%4d/%d tests FAILED.\n", numTests - numTestPassed, numTests);
	printf("   (%d tests done since last summary.)\n", testsSinceLast);
	printf("\n");
}


/*
 * Testing Functions
 */

void testInsertAtHead()
{
	printf("Adding to head of empty list:\n");
	struct nodeStruct *list = NULL;

	struct nodeStruct* firstNode = List_createNode(0);
	TEST(List_countNodes(list) == 0);
	List_insertHead(&list, firstNode);
	TEST(List_countNodes(list) == 1);
	TEST(List_findNode(list, 0) == firstNode);
	TEST(List_findNode(list, 1) == NULL);
	List_deleteNode(&list, firstNode);
	TEST(List_countNodes(list) == 0);
	TEST(List_findNode(list, 0) == NULL);
	TEST(List_findNode(list, 1) == NULL);

	// Clear
	while (List_countNodes(list) > 0) {
		List_deleteNode(&list, list);
	}
}

void testInsertAtTail()
{
	printf("Adding to tail of empty list:\n");
	struct nodeStruct *list = NULL;

	struct nodeStruct* secondNode = List_createNode(1);
	TEST(List_countNodes(list) == 0);
	List_insertTail(&list, secondNode);
	TEST(List_countNodes(list) == 1);
	TEST(List_findNode(list, 0) == NULL);
	TEST(List_findNode(list, 1) == secondNode);
	List_deleteNode(&list, secondNode);
	TEST(List_countNodes(list) == 0);
	TEST(List_findNode(list, 0) == NULL);
	TEST(List_findNode(list, 1) == NULL);

	// Clear
	while (List_countNodes(list) > 0) {
		List_deleteNode(&list, list);
	}

}

void testAddManyToHeadOrTail(_Bool addToHead)
{
	const int NUM_NODES = 10;
	printf("Adding numbers 0 to %d at %s:\n",
			NUM_NODES-1,
			(addToHead ? "head" : "tail"));
	struct nodeStruct *list = NULL;
	struct nodeStruct *nodesArray[NUM_NODES];

	for (int count = 0; count < NUM_NODES; count++) {
		struct nodeStruct *node = List_createNode(count);

		// Add node to list, and store in array for checking later
		if (addToHead) {
			List_insertHead(&list, node);
			nodesArray[NUM_NODES - count - 1] = node;
		}
		else {
			List_insertTail(&list, node);
			nodesArray[count] = node;
		}
		TEST(List_countNodes(list) == count + 1);
	}

	// Check list:
	TEST(List_countNodes(list) == NUM_NODES);
	struct nodeStruct *current = list;
	for (int i = 0; i < NUM_NODES; i++) {
		TEST(List_findNode(list, i)->item == i);
		TEST(current == nodesArray[i]);
		current = current->next;
	}

	// Clear
	while (List_countNodes(list) > 0) {
		List_deleteNode(&list, list);
	}
}

void testSort()
{
	printf("Sorting:\n");
	testListSortFromArray((int[] ) { TERMINATOR });
	testListSortFromArray((int[] ) { 1, TERMINATOR });
	testListSortFromArray((int[] ) { 1, 2, TERMINATOR });
	testListSortFromArray((int[] ) { 2, 1, TERMINATOR });
	testListSortFromArray((int[] ) { 2, 1, 4, TERMINATOR });
	testListSortFromArray((int[] ) { 1, 3, 4, TERMINATOR });
	testListSortFromArray((int[] ) { 4, 3, 1, TERMINATOR });
	testListSortFromArray((int[] ) { 4, 1, 3, TERMINATOR });
	testListSortFromArray((int[] ) { 2, 4, 6, 3, 1, TERMINATOR });
	testListSortFromArray((int[] ) { -1, 0, 1, 2, 3, TERMINATOR });
	testListSortFromArray((int[] ) { 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, TERMINATOR });
	testListSortFromArray((int[] ) { 0, 1, 9, 1, -5, 22, 10, 0, -15, TERMINATOR });
}
void testListSortFromArray(int data[])
{
	struct nodeStruct *list = NULL;

	// FUTURE CHANGE:
	// Store node pointers as they are added to the list, and then verify
	// that all pointers remain valid after the sort. (Not a requirement for 2015).

	// Stuff data in:
	for (int i = 0; data[i] != TERMINATOR; i++) {
		struct nodeStruct *node = List_createNode(data[i]);
		List_insertTail(&list, node);
	}

	// Sort:
//	printf("List before (then after) sort:\n");
//	dumpList(list);
	List_sort(&list);
//	dumpList(list);

	// Check in sorted order:
	struct nodeStruct *current = list;
	while (current && current->next != NULL) {
		TEST(current->item <= current->next->item);
		current = current->next;
	}

	// Clear
	while (List_countNodes(list) > 0) {
		List_deleteNode(&list, list);
	}
}

