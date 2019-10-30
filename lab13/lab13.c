/* EE2310 Lab13. String Enocding
   107061112, 王昊文
   Date: 2018.12.17
*/

#include <stdio.h>
#include <stdlib.h>

char *read_input(void);	// reads input, also does the -0x30
void bin_shift(char *line);	// does the bit shifting and print result

int main(void) 
{ 	
	char *line;	// a pointer to a continuous location to store paragraph

	while (getchar() != '\n') // read begin
	{
	}	
	while (line = read_input()) {	// if not "end"
		bin_shift(line);	// shift bit
		free(line);	// prevent memory leak
	}
	return 0;
}
// reads input, and deal with the "end"
char *read_input(void)
{
	char temp1, temp2;	// for the case if the first word is 'e'
	char *word;		// points to the input
	char *head;		// records the head of the paragraph
	int line_len;	// line length
	
	line_len = getchar();	// first word is line length
	if (line_len == 'e') {	// for the case of "end", if first word = 'e'
		if ((temp1 = getchar()) == 'n') {	// if second word is 'n'
			if (getchar() == 'd') 	// if third word is 'd'
				return NULL;	// end of paragraph
			else {	// else if third word isn't 'd'
				line_len -= 0x30;	// line legnth == first word of line
				// give a space to store paragraph
				word = malloc(sizeof(char) * line_len * 4 / 3 + 1);	
				head = word;	// point to the head
				*word = 'n' - 0x30;	// the second word is n 
				word++;		
				*word = temp2 - 0x30;	// thrid word is not d
				word++;
			}
		}
		else { // first word is 'e', second word isn't 'n'
			line_len -= 0x30;
			word = malloc(sizeof(char) * line_len * 4 / 3 + 1);
			head = word;
			*word = temp1 - 0x30;
			word++;
		}

	}
	else {	// first word isn't 'e'
		line_len -= 0x30;
		word = malloc(sizeof(char) * line_len * 4 / 3 + 1);
		head = word;
	}
	while ((*word = getchar()) != '\n') { // until the end of line
		*word -= 0x30;	// every input - 0x30
		word++;
	}
	*(word) = '\0'; // end of string
	return head;
}

// shifts bits
void bin_shift(char *line)
{
	char three_word[4];	// process three word at a time
	while (*line != '\0') {	// if not end of line
		// perform the bitwise or to get the real character
		three_word[0] = (*line << 2 | *(++line) >> 4);	
		three_word[1] = (*line << 4 | *(++line) >> 2);
		three_word[2] = (*line << 6 | *(++line));
		three_word[3] = '\0';
			printf("%s", three_word);	// print every three word
		line++;
	}
	return;
}
