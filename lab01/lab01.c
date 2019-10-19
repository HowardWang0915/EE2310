/* EE231002 Lab01. Typhoon scale
107061112,王昊文
107.09.17*/

#include <stdio.h>																/*library*/					
int main(void)																	/*Beginning of main*/
{
	float mile, meter;															/*declare variables*/

	printf("Input speed in miles per hour: ");									/*print the first line*/
	scanf("%f", &mile);															/*user input mph*/
	meter = (1609.344/3600)*mile;												/*switching from mph to meter*/
	printf("The speed in metric system is %f meters per second.\n", meter);		/*output result*
	return 0;																	/*program ends and return 0*/
}
