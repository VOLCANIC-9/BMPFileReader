#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short ReadLE2(FILE *fp){
    unsigned char buf[2];
    unsigned short result = 0;
    int i;

    fread(buf, 1, 2, fp);
	
    for (i = 1; i >= 0; i--) {
        result = (result << 8) | (unsigned short) buf[i];
    }

    return result;
}

unsigned int ReadLE4(FILE *fp){
    unsigned char buf[4];
    unsigned int result = 0;
    int i;

    fread(buf, 1, 4, fp);
	
    for (i = 3; i >= 0; i--) {
        result = (result << 8) | (unsigned int) buf[i];
    }
}

int main(void){
	
	FILE *FP;
	
	BITMAPFILEHEADER *header;
	
	char           filetype[3] = {'\0', '\0', '\0'};
    unsigned int   filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned long  offset;
	int            headersize;
    unsigned char  buf00[4];
    int            i;
	unsigned int   headersize00;
    int            width;
    int            height;
    unsigned short planes;
    unsigned short bitcount;
	unsigned int   compression;
    unsigned int   size_image;
    int            x_pix_per_meter;
    int            y_pix_per_meter;
    unsigned int   clr_used;
    unsigned int   clr_important;
	unsigned int*  data[100000]= {0};
	unsigned int   tmp;

     /*Pleas replace the path with your image directory*/

        FP= fopen("Path", "rb");
	
		 if(FP == NULL){
		   printf("Argument Exception");
		 }
		 
		 fread(&filetype, 1, 2, FP);
		 
		 filesize = (unsigned int) ReadLE4(FP);
		 
		 fread(&reserved1, 2, 1, FP);
		 
		 fread(&reserved2, 2, 1, FP);
		 
		 offset = (unsigned long) ReadLE4(FP);
		 
		 fread(buf00, 1, 4, FP);
		 
            for(i = 3; i >= 0; i--) {
             headersize = (headersize << 8) | (int) buf00[i];
            }

         fseek(FP, 14, SEEK_SET);
		 
    		 if (headersize == 12) {
             
			 headersize00 = (unsigned int) ReadLE4(FP);
			 
			 width = (int) ReadLE2(FP);
			 
			 height = (int) ReadLE2(FP);
			 
			 planes = (unsigned short) ReadLE2(FP);
			 
			 bitcount = (unsigned short) ReadLE2(FP);
			 
			 	for(i = 0; i < 3*width*height; i++){
			 
			     fread(&data[i], sizeof(unsigned int), 1, FP);
				 
			    }
			 
             } else if (headersize == 40) {
             
			 headersize00 = (unsigned int) ReadLE4(FP);
			 
			 width = (int) ReadLE4(FP);
			 
			 height = (int) ReadLE4(FP);
			 
			 planes = (unsigned short) ReadLE2(FP);
			 
			 bitcount = (unsigned short) ReadLE2(FP);
			 
			 compression = (unsigned int) ReadLE4(FP);
			 
			 size_image = (unsigned int) ReadLE4(FP);
			 
			 x_pix_per_meter = (int) ReadLE4(FP);
			 
			 y_pix_per_meter = (int) ReadLE4(FP);
			 
			 clr_used = (unsigned int) ReadLE4(FP);
			 
			 clr_important = (unsigned int) ReadLE4(FP);
			 
			  
				for(i = 0; i < 3*width*height; i++){
			 
			     fread(&data[i], sizeof(unsigned int), 1, FP);
				 
			    }
			 
             } else {
             printf("Unsupported BITMAP. %ld\n", headersize);
             exit(1);
            }
		 
		 fclose(FP);
	 
	 
	 
	 for(i = 0; i < 3*width*height; i += 3){
         
         tmp = data[i];
         data[i] = data[i+2];
         data[i+2] = tmp;
         
		}
	 
	return 0;
	
}
