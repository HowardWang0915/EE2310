/* EE2310 Lab14. Image Procesing
   107061112, 王昊文
   Date: 2018.12.24
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct sPIXEL { // a single pixel
unsigned char r, g, b; // three color components
} PIXEL;

typedef struct sIMG {	// an image of PPM style
	char header[3];		// header, either P3 or P6
	int W, H;			// width and height of the image
	int level;			// intensity level of each color component
	PIXEL **PX;			// two-dimensional array for all the pixels
} IMG;

IMG *PPMin(char *inFile);
/* This function opens the inFile, reads the image data and returns 
a pointer pointing to the newly created image data structure. */
void *PPMout(IMG *p1, char *outFile);
/* This function writes the image pointed by p1 
to the output file outFile. */
IMG *PPMcvt(IMG *p1, IMG *ee, IMG *nthu);
/* This function processes the image pointed by p1 performing the 
modifications stated above and returns the new image as a result. */

int main(int argc, char *argv[]) 
{ 	
	// p1 points to picture, ee points to ee logo, nthu points to nthu logo
	IMG *p1, *ee, *nthu;	

	p1 = PPMin(argv[1]);	// pic.ppm
	ee = PPMin(argv[2]);	// ee.ppm
	nthu = PPMin(argv[3]);	// nthu.ppm
	PPMout(PPMcvt(p1, ee, nthu), argv[4]);	// new.ppm
	
	return 0;
}

IMG *PPMin(char *inFile) 
{
	int i, j;	// loop index
	IMG *pic;	// pointer to picture
	FILE *fin;	
	
	pic = (IMG *)malloc(sizeof(IMG));	// give space to store data
	fin = fopen(inFile, "r");	// read
	fscanf(fin, "%s", pic->header);	// header
	fscanf(fin, "%d %d\n", &pic->W, &pic->H);	// width, height
	fscanf(fin, "%d\n", &pic->level);	// intensity level
	pic->PX = malloc(pic->W * sizeof(PIXEL *));	// space to store pixels
	for (i = 0; i < pic->W; i++) {
		// it is two dimensional
		pic->PX[i] = (PIXEL *)malloc(pic->H * sizeof(PIXEL));	
	}
	for (j = 0; j < pic->H; j++) {
		for (i = 0; i < pic->W; i++) {
			// store in r, g, b
			fscanf(fin, "%c", &pic->PX[i][j].r);
			fscanf(fin, "%c", &pic->PX[i][j].g);
			fscanf(fin, "%c", &pic->PX[i][j].b);
		}
	}
	fclose(fin);
	return pic;
}

void *PPMout(IMG *p1, char *outFile)
{
	int i, j;	// lopp index
	FILE *fout;	// pointer to file out

	fout = fopen(outFile, "w");	// write the new file
	fprintf(fout, "%s\n", p1->header);	// header
	fprintf(fout, "%d %d\n", p1->W, p1->H);	// width, height
	fprintf(fout, "%d\n", p1->level);	// intensity level
	for (j = 0; j < p1->H; j++) {	
		for (i = 0; i < p1->W; i++) {	// write the new r, g, b
			fprintf(fout, "%c", p1->PX[i][j].r);
			fprintf(fout, "%c", p1->PX[i][j].g);
			fprintf(fout, "%c", p1->PX[i][j].b);
		}
	}
	fclose(fout);
	return NULL;
}

IMG *PPMcvt(IMG *p1, IMG *ee, IMG *nthu)
{
	int i, j, temp;	//i, j: loop index, temp: for swapping
	for (j = 0; j < p1->H; j++) { 	// turn red to green
		for (i = 0; i < p1->W; i++) {	
			if (p1->PX[i][j].g < 65 && (p1->PX[i][j].r) / 
				(p1->PX[i][j].b + 1) > 1.6) {
					p1->PX[i][j].r = 255;
					p1->PX[i][j].g = 255;
					p1->PX[i][j].b = 0;
			}
		}
	}
	for (j = 0; j < ee->H; j++) {	// ee sign
		for (i = 0; i < ee->W; i++) {	
			// when the part is not white
			if (ee->PX[i][j].r != 255 && ee->PX[i][j].g != 255 
				&& ee->PX[i][j].b != 255) {
				// put the logo at right bottom
				p1->PX[p1->W - ee->W + i][p1->H - ee->H + j].r = ee->PX[i][j].r;
				p1->PX[p1->W - ee->W + i][p1->H - ee->H + j].g = ee->PX[i][j].g;
				p1->PX[p1->W - ee->W + i][p1->H - ee->H + j].b = ee->PX[i][j].b;
			}
		}
	}
	for (j = 0; j < nthu->H; j++) {	// nthu sign
		for (i = 0; i < nthu->W; i++) {
			// when the part is not white
			if (nthu->PX[i][j].r != 255 && nthu->PX[i][j].g != 255 
				&& nthu->PX[i][j].b != 255) {
				nthu->PX[i][j].r = 255;	// turn the nthu sign into purple
				nthu->PX[i][j].b = 255;
				p1->PX[i][j].r = nthu->PX[i][j].r;	// then put the logo 
				p1->PX[i][j].g = nthu->PX[i][j].g;
				p1->PX[i][j].b = nthu->PX[i][j].b;
			}
		}
	}
	// put a  box around me
	for (j = 215, i = 3128; i < 3240; i++) {
		p1->PX[i][j].r = 255;
		p1->PX[i][j].g = 255;
		p1->PX[i][j].b = 255;
	}
	for (j = 360, i = 3128; i < 3240; i++) {
		p1->PX[i][j].r = 255;
		p1->PX[i][j].g = 255;
		p1->PX[i][j].b = 255;
	}
	for (i = 3128, j = 215; j < 360; j++) {
		p1->PX[i][j].r = 255;
		p1->PX[i][j].g = 255;
		p1->PX[i][j].b = 255;
	}
	for (i = 3240, j = 215; j < 360; j++) {
		p1->PX[i][j].r = 255;
		p1->PX[i][j].g = 255;
		p1->PX[i][j].b = 255;
	}	
	return p1;
}
