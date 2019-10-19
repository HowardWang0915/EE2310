/* EE2310 Lab04. Calender of the Month
   107061112, 王昊文
   Date: 2018.10.05
*/
#include <stdio.h>              // include standard library

int main(void)					// main program starts
{
	/* m as input month, i as the counter to find the first day,
	startDay  as the first day, date as the print out date */
	int m, i, startDay, date;		
	printf("Input a month of 2018: "); 	// prompt
	scanf("%d", &m);
	if (m >= 1 && m <= 12) {     		// restriction
		printf("    ");					// blank of the calender
		switch (m) {					// find out the month
			case 1: printf("January");
				break;
			case 2: printf("February");
				break;
			case 3: printf("March");
				break;
			case 4: printf("April");
				break;
			case 5: printf("May");
				break;
			case 6: printf("June");
				break;
			case 7: printf("July");
				break;
			case 8: printf("August");
				break;
			case 9: printf("September");
				break;
			case 10: printf("October");
				break;
			case 11: printf("November");
				break;
			case 12: printf("December");
		}
		printf(" 2018\n");				// format of the calender
		printf("    Sun Mon Tue Wed Thu Fri Sat\n");
		/* find out the first day of a Month, startDay starts at 
		2 because January starts at Monday (Saturday as 7, 
		Sunday as 1) */ 
		for (i = 1, startDay = 2; i < m; i++) {
		// Month with 31 days
			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8|| \
			i == 10 || i == 12) 
				startDay += 31; 	// remainder = start day of a month
			// Month with 30 days
			else if (i == 4 || i == 6 ||i == 9 || i == 11) 
				startDay += 30;
			else if (i == 2)
				startDay += 28;

			startDay = startDay % 7;
		}
		// print blanks wrt startDay
		for (i = 0; i < startDay; i++) {
			printf("   ");
		}

		// month with 31 days
		if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8|| m == 10 \
		|| m == 12) {
			for (date = 1; date <= 31; date++) {	// print out dates of a month
				printf("%2d  ", date);
				if (startDay++ % 7 == 0)		// if it is Saturday, print \n
					printf("\n    ");
			}
		}
		// month with 30 days
		else if (m == 4 || m == 6 || m == 9 || m == 11) {
			for (date = 1; date <= 30; date++) {	// print out dates of a month
				printf("%2d  ", date);
				if (startDay++ % 7 == 0)		// if it is Saturday, print \n
					printf("\n    " );
			}
		}
		else if (m == 2) {   			// February is a special case
			for (date = 1; date <= 28; date++) {	// print out dates of a month
				printf("%2d  ", date);
				if (startDay++ % 7 == 0)		// if it is Saturday, print \n
					printf("\n    ");
			}
		}
	printf("\n");
	}
	else 			// if the number is out of range, print error
		printf("    Input error, program aborts!\n");
	return 0;
}
