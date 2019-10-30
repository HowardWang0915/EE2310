#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSTR 5000

int readLine(char para[LSTR]);
void center(char* para);
void lAlign(char* para);
void rAlign(char* para);
int n;

int main(int argc, char* argv[])
{
    char align;
    char para[LSTR] = {};

    n = atoi(argv[1]);
    align = argv[2][0];
    //printf("%d %c\n", n, align);

    // char para[LSTR]="I really like to know you better.  If you don't mind.  Make me feel better.";
    //char para[LSTR] = "\"He has been phenomenal,\" Bryant said.  \"We have watched some tape on him.  We came up with a strategy that we thought would be effective, but he was knocking down his jump shot, penetrating and he got around our guards.\"";

    while(readLine(para)) {
        scanf("%*c");  // consume the \n
        // printf("%s\n", para);
        if(align == 'c') {  
            center(para);
        }
        else if(align == 'r') {
            rAlign(para);
        }
        else if(align == 'l') { 
            lAlign(para);
        }
        memset(para, 0, 5000);  // clean para array
    }
	return 0;
}


int readLine(char para[LSTR]) {

    scanf("%[^\n]s", para);  // read the whole paragraph until \n is reached.
    if (para[0] == 'E' && para[1] == 'O' && para[2] == 'F') {  // end of file
        return 0;
    }
    else {
        return 1;
    }
}

void center(char* para){
    int i, pos, space, start, length, left_empty, ppos;

    pos = n - 1;
    start = 0; 	// starting word
    //check if it is end of paragraph '\0'
    while(para[pos] != '\0') {  // Not the end of line
        if(para[pos + 1] != ' ') {
            while(para[pos] != ' ') {  // reverse back to find previous paragraph break point which is a white space.
                pos = pos - 1;
            }
            // There are two possibilities: One space between words or two spaces between two sentences.
            if(para[pos-1] == ' ') {  // two spaces
                pos = pos - 2;
                length = pos - start + 1;	// 補償
                space = 2;
            }
            else {  // one spaces
                pos = pos - 1;
                length = pos - start + 1;
                space = 1;
            }
        }
        else {
            length = n;
            if(para[pos+2] == ' '){
                space = 2;
            }
            else{
                space = 1;
            }
        }
        // Print this line(substring) in center
        left_empty = (n - length)/2;
        for(i=0; i<left_empty; i++){  // print the padding white space in left side.
            printf("%c", ' ');
        }
        for(i=0; i<length; i++){
            ppos = start + i;
            printf("%c", *(para+ppos));
        }
        printf("\n");
        // initial for next round
        start = pos + 1 + space;
        pos = pos + n + space;
    }
    // last line in paragraph
    length = 0;
    while(para[start+length] != '\0'){
        length = length + 1;
    }        // Print this line(substring) in center
    left_empty = (n - length)/2;
    for(i=0; i<left_empty; i++){  // print the padding white space in left side.
        printf("%c", ' ');
    }
    for(i=0; i<length; i++){
        ppos = start + i;
        printf("%c", *(para+ppos));
    }
    printf("\n");
}

void rAlign(char* para){
    int i, pos, space, start, length, left_empty, ppos;

    pos = n-1;  // array index starts with 0
    start = 0;
    //check if it is end of paragraph '\0'
    while(para[pos] != '\0'){  // Not the end of line
        if(para[pos+1] != ' '){
            while(para[pos] != ' '){  // reverse back to find previous paragraph break point which is a white space.
                pos = pos - 1;
            }
            // There are two possibilities: One space between words or two spaces between two sentences.
            if(para[pos-1] == ' '){  // two spaces
                pos = pos - 2;
                length = pos - start + 1;
                space = 2;
            }
            else{  // one spaces
                pos = pos - 1;
                length = pos - start + 1;
                space = 1;
            }
        }
        else{
            length = n;
            if(para[pos+2] == ' '){
                space = 2;
            }
            else{
                space = 1;
            }
        }
        // Print this line(substring) in right aligned
        left_empty = n - length;  // Calculate the padding white space
        for(i=0; i<left_empty; i++){  // print the padding white space in left side.
            printf("%c", ' ');
        }
        for(i=0; i<length; i++){
            ppos = start + i;
            printf("%c", *(para+ppos));
        }
        printf("\n");
        start = pos + 1 + space;
        pos = pos + n + space;
    }
    // last line in paragraph
    length = 0;
    while(para[start+length] != '\0'){
        length = length + 1;
    }
    left_empty = n - length;
    for(i=0; i<left_empty; i++){  // print the padding white space in left side.
        printf("%c", ' ');
    }
    for(i=0; i<length; i++){
        ppos = start + i;
        printf("%c", *(para+ppos));
    }
    printf("\n");
}

void lAlign(char* para){
    int i, pos, space, start, length, ppos;

    pos = n-1;
    start = 0;
    //check if it is end of paragraph '\0'
    while(para[pos] != '\0'){  // Not the end of line
        if(para[pos+1] != ' '){  // if next point is an white space, then we can print to this position. No need to reverse search.
            while(para[pos] != ' '){  // reverse back to find previous paragraph break point which is a white space.
                pos = pos - 1;
            }
            // Next line should start with the first characters
            if(para[pos-1] == ' '){  // two spaces
                pos = pos - 2;
                length = pos - start + 1;
                space = 2;
            }
            else{  // one spaces
                pos = pos - 1;
                length = pos - start + 1;
                space = 1;
            }
        }
        else{
            length = n;
            if(para[pos+2] == ' '){ // next start point has to be a character
                space = 2;
            }
            else{
                space = 1;
            }
        }
        for(i=0; i<length; i++){
            ppos = start + i;
            printf("%c", *(para+ppos));
        }
        printf("\n");
        start = pos + 1 + space;
        pos = pos + n + space;
    }
    // last line in paragraph
    length = 0;
    while(para[start+length] != '\0'){
        length = length + 1;
    }
    for(i=0; i<length; i++){
        ppos = start + i;
        printf("%c", *(para+ppos));
    }
    printf("\n");
}
