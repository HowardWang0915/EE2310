/* EE2310 Lab02. Roman Numerals
   107061112, 王昊文
   Date: 2018.10.01 */

#include <stdio.h>						// include standard library.

int main(void)							// main program starts.
{
	int dec,kilo,hun,ten,digit;			// declare decimal(user input), kilo
										/* (forth digit), hundred(third digit),
										ten(second digit),digit(last digit). */
	printf("Input an integer between 1 and 3000: ");// prompt.
	scanf("%d", &dec);					// read decimal.	
	if (dec <= 3000 && dec > 0)				// restrict the range.
	{
		kilo = dec/1000;					// find out what is the forth digit.
		switch(kilo){					// test what is the value of kilo.
		case 0:							// does nothing.
		break;							
		case 1: printf("M");			// print out the roman number.
		break;
		case 2: printf("MM");			// print out the roman number.
		break;
		case 3: printf("MMM");			// print out the roman number.
		break;
		}								// There are only 3 possible forth digit.
		hun = ((dec%1000)/100);			// find out what is the third digit.
		switch(hun){					// there are 9 possible third digit.
		case 0:							// does nothing.
		break;
		case 1: printf("C");			// print out the roman number.
		break;
		case 2: printf("CC");			// print out the roman number.
		break;
		case 3: printf("CCC");			// print out the roman number.
		break;
		case 4: printf("CD");			// print out the roman number.
		break;
		case 5: printf("D");			// print out the roman number.
		break;
		case 6: printf("DC");			// print out the roman number.
		break;
		case 7: printf("DCC");			// print out the roman number.
		break;
		case 8: printf("DCCC");			// print out the roman number.
		break;
		case 9: printf("CM");			// print out the roman number.
		break;
		}
		ten = ((dec%100)/10);			// find out what is the second digit.
		switch(ten){					// there are 9 possible second digit.
		case 0:
		break;
		case 1: printf("X");			// print out the roman number.
		break;
		case 2: printf("XX");			// print out the roman number.
		break;
		case 3: printf("XXX");			// print out the roman number.
		break;
		case 4: printf("XL");			// print out the roman number.
		break;
		case 5: printf("L");			// print out the roman number.
		break;
		case 6: printf("LX");			// print out the roman number.
		break;
		case 7: printf("LXX");			// print out the roman number.
		break;
		case 8: printf("LXXX");			// print out the roman number.
		break;
		case 9: printf("XC");			// print out the roman number.
		break;
		}
		digit = (dec%10);				// find out what is the first digit.
		switch(digit){					// there are 9 possible first digit.
		case 0:							// does nothing.
		break;
		case 1: printf("I");			// print out the roman number.
		break;
		case 2: printf("II");			// print out the roman number.
		break;
		case 3: printf("III");			// print out the roman number.
		break;
		case 4: printf("IV");			// print out the roman number.
		break;
		case 5: printf("V");			// print out the roman number.
		break;
		case 6: printf("VI");			// print out the roman number.
		break;
		case 7: printf("VII");			// print out the roman number.
		break;
		case 8: printf("VIII");			// print out the roman number.
		break;
		case 9: printf("IX");			// print out the roman number.
		break;
		}
	printf("\n");						// The assignment assigns a text wrap.
	return 0;							// main program ends.
	}
}
















