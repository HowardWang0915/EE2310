/* EE2310 Lab09. Word Processing
   107061112, 王昊文
   Date: 2018 / 11 / 19
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LSTR 5000

int max_length;	// this will store manimum length of every line

int readline(char para[LSTR]);	// reads input
void center(char *para);		// center
void lAlign(char *para);		// left align
void rAlign(char *para);		// right align

/********************************************************************
* main: In this function, it will check for the max line length.    *
* or aligning foramt.												*
********************************************************************/
int main(int acgc, char *argv[]) 
{
	char align;	// align format
	char para[LSTR] = {};	// array to store the strings
	int i;
	align = *argv[2];		// the third word is the align format
	max_length = atoi(argv[1]);	// max line length is the second word
	while(readline(para)) {		// when input != EOF
	 	// print
		if(align == 'c') 
			center(para);
		else if (align == 'r') 
		 	rAlign(para);
		else if (align == 'l') 
		 	lAlign(para);
  	 	for (i = 0; i < LSTR; i++) 
			para[i] = 0;	// clean para array
	}
	return 0;
}
/********************************************************************
* readline: this function will read the input. Also, it will check  *
* 			for '\n' and EOF to determinate when it should stop		*
********************************************************************/
int readline(char para[LSTR])
{
	int i = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		para[i] = ch;
		if (para[i] == ' ' &&  para[i - 1] == '.') {
			para[++i] = ' ';
			i++;
		}
		else
			i++;
	}
	para[i] = '\0';
	if (para[0] == 'E' && para[1] == 'O' && para[2] == 'F')   // end of file
	 	return 0; 
	else
		return 1;
}
/********************************************************************
* center: simply centers the texts.									*
********************************************************************/
void center(char *para)
{
	int i;	// loop index
	int pos = max_length - 1;	// pos is the current checking index
	int length;			// the actual length of line
	// blank_Space counts the spaces between current line and the next line
	int blank_Space;	
	int start = 0;	// which pos should next line start to print
	int empty;		// how many lines empty in the line
	while (para[pos] != '\0') {	// when it is not end of paragraph
		if (para[pos + 1] != ' ') {		// if the last word is not ' '
			while (para[pos] != ' ') {	// to find the nearest ' '
				pos--;
			}
			// there might be one or two spaces
			if (para[pos - 1] == ' ') {	// two spaces
				pos -= 2;
				length = pos - start + 1;
				blank_Space = 1;
			}
			else {	// one space
				pos--;
				length = pos - start + 1;
				blank_Space = 1;
			}
		}
		else {	// word = max_length
			length = max_length;
			if (para[pos + 2] == ' ')
				blank_Space = 2;	// it may be '.'
			else 
				blank_Space = 1;
		}
		// line empty should be the mid number of max - actual length
		empty = (max_length - length) / 2;	
		for (i = 0; i < empty; i++)	// white spaces
			printf(" ");
		for (i = 0; i < length; i++) {	// print words 
			printf("%c", *(para + start + i));
		}
		printf("\n");
		start = pos + 1 + blank_Space;	// next first word position
		pos += (max_length + blank_Space);	// check from next line's end
	}
	/* last line */
	length = 0;
	// to find out remaining word's length
	while (para[start + length] != '\0') {
		length++;
	}
	empty = (max_length - length) / 2;	// count left empty spaces
	for (i = 0; i < empty; i++) 
		printf(" ");
	for (i = 0; i < length; i++) // right empty is included in here
		printf("%c", *(para + start + i));
	printf("\n");
	
}
// right align
void rAlign(char *para)
{
	// the checking part is same as center
	int i;
	int pos = max_length - 1;
	int length;
	int blank_Space;
	int start = 0;
	int empty;
	while (para[pos] != '\0') {
		if (para[pos + 1] != ' ') {
			while (para[pos] != ' ') {
				pos--;
			}
			if (para[pos - 1] == ' ') {
				pos -= 2;
				length = pos - start + 1;
				blank_Space = 1;
			}
		
			else {
				pos--;
				length = pos - start + 1;
				blank_Space = 1;
			}
		}
		else {
			length = max_length;
			if (para[pos + 2] == ' ')
				blank_Space = 2;
			else 
				blank_Space = 1;
		}
		// = center shift right
		empty = (max_length - length);
		for (i = 0; i < empty; i++)
			printf(" ");
		for (i = 0; i < length; i++) {
			printf("%c", *(para + start + i));
		}
		printf("\n");
		start = pos + 1 + blank_Space;
		pos += (max_length + blank_Space);
	}
	// last line
	length = 0;
	while (para[start + length] != '\0') {
		length++;	// find out actual length
	}
	empty = max_length - length;
	for (i = 0; i < empty; i++) 
		printf(" ");
	for (i = 0; i < length; i++) 
		printf("%c", *(para + start + i));
	printf("\n");
}
// left align
void lAlign(char *para)
{
	// same as center
	int i;
	int pos = max_length - 1;
	int length;
	int blank_Space;
	int start = 0;
	while (para[pos] != '\0') {
		if (para[pos + 1] != ' ') {
			while (para[pos] != ' ') {
				pos--;
			}
			if (para[pos - 1] == ' ') {
				pos -= 2;
				length = pos - start + 1;
				blank_Space = 1;
			}
			else {
				pos--;
				length = pos - start + 1;
				blank_Space = 1;
			}
		}
		else {
			length = max_length;
			if (para[pos + 2] == ' ')
				blank_Space = 2;
			else 
				blank_Space = 1;
		}
		for (i = 0; i < length; i++) {	// no need to print blank
			printf("%c", *(para + start + i));
		}
		printf("\n");
		start = pos + 1 + blank_Space;
		pos += (max_length + blank_Space);
	}
	// after cutting the paragraph, no need to shift
	// last line of paragraph
	length = 0;
	while (para[start + length] != '\0') {
		length++;
	}
	for (i = 0; i < length; i++) 
		printf("%c", *(para + start + i));
	printf("\n");
}
