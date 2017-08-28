
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	if (wtable-> nWords == wtable->maxWords) {
	    wtable->maxWords = wtable->maxWords*2;
	    int newsize = wtable->maxWords*sizeof(WordInfo);
	    wtable->wordArray = (WordInfo*) realloc(wtable->wordArray, newsize);
	    for (int i = wtable->nWords; i < wtable->maxWords; i++) {
	        llist_init(&wtable->wordArray[i].positions);
	    }
	}
	
	// Word not found.

	// Make sure that the array has space.
	// Expand the wordArray here.

	// Add new word and position
	
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
	int i;
	for (i = 0; i < wtable->nWords; i++) {
	    if (strcmp(wtable->wordArray[i].word, word) == 0) {
	        return &wtable->wordArray[i].positions; 
	    }
	}
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

void toLower(char *s);
char lower(char s);
// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here
	int c;
	wordLength = 0;
	while ((c = fgetc(fd)) != EOF) {
	   charCount++;
	   if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122))) {
	       if (wordLength == 0) {
	           continue;
	       }
	       word[wordLength] = '\0';
	       return word;
	   }
	   word[wordLength++] = c;
        }
	if (wordLength) {return word;}
	
	return NULL;
}


// Converts string to lower case
void toLower(char *s) {
	// Write your code here
	int len  = strlen(s);
	int i;
	for (i = 0; i < len; i++) {
	    if (s[i] >= 'A' && s[i] <= 'Z') {
	        s[i] += 32;
	    }
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	// Write your code here
	FILE *fd = fopen(fileName, "r");
	if (fd == NULL) {return 0;}
	
	char *w;
	wordPos = 0;
	charCount = 0;

	while ((w = nextword(fd)) != NULL) {
	     wordCount++;
	     toLower(w);
	     wordPos = charCount - wordLength - 1;
	     if (verbose == 1) {
	         printf("%d: word=%s, pos=%d\n", wordCount - 1, w, wordPos);
	     }
	     wtable_add(wtable, word, wordPos);
	}
	return 0;
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	int i, j;
	for (i = 0; i < wtable->nWords; i++) {
	    for (j = 0; j < wtable->nWords - 1; j++) {
	        WordInfo temp;
		char * word2 = wtable->wordArray[j + 1].word;
		if (strcmp(wtable->wordArray[j].word, word2) > 0) {
		    temp = wtable->wordArray[j + 1];
		    wtable->wordArray[j + 1] = wtable->wordArray[j];
		    wtable->wordArray[j] = temp;
		}
	    }
	}
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	FILE *fd = fopen(fileName, "r");
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n", word, fileName);
	int i;
	for (i = 0; i < wtable->nWords; i++) {
	    if (strcmp(wtable->wordArray[i].word, word) == 0) {
	        int ith = 0;
		int pos;
		while (llist_get_ith(&wtable->wordArray[i].positions, ith, &pos)) {
		    printf("---------- pos=%d-----\n", pos);
		    printf("......");
		    fseek(fd, pos, SEEK_SET);
		    int c, j;
		    for (j = 0; j < 200; j++) {
		        c = fgetc(fd);
			if (c == EOF) {
			    return 1;
			}
			printf("%c", c);
		    }
		    printf("......\n");
		    ith++;
		}
	    }
	}
}

