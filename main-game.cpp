#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include "byteconversion.h"
#include "framebufferimage.h"
#include "getch.h"

using namespace std;

void draw(imageData *image);

void cleanUp();
void usage();

int frameBufferFD = 0;
char *frameBuffer = 0;
int width = 0, height = 0, screensize = 0;
int depth = 32;

int main() {
	// Show Press Enter
  DIR *imageFolder;
  char* imagePath;
  int selection = 0, images = 0;
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  long int dx, dy;
  bool escape = false;
  int i, n;
  char paths[5][255];  

  strcpy(imagePath,"menu");
  
  // Build an array of paths to the menu item images
  struct dirent **namelist;
  n = scandir(imagePath, &namelist, 0, alphasort);
  if (n < 0) {
    cleanUp();
    printf("Could not read image directory.\n");
    return 1;
  }

  system("setterm -cursor off");
  system("stty -echo");

  for (i = 0; i < n; i++) {
    if(strstr(namelist[i]->d_name, ".bmp") == NULL) continue;

    strcpy(paths[images], imagePath);
    strcat(paths[images], "/");
    strcat(paths[images], namelist[i]->d_name);
    images++;
    free(namelist[i]);
  }
  free(namelist);

  if(images == 0) {
    cleanUp();
    printf("Error: no images found.\n");
    return 1;
  }

  frameBufferFD = open("/dev/fb0", O_RDWR);
  if(!frameBufferFD) {
    cleanUp();
    printf("Error: cannot open framebuffer device.\n");
    return 1;
  }

  if (ioctl(frameBufferFD, FBIOGET_VSCREENINFO, &vinfo)) {
    cleanUp();
    printf("Error reading variable information.\n");
    return 1;
  }

  if(ioctl(frameBufferFD, FBIOGET_FSCREENINFO, &finfo)) {
    cleanUp();
    printf("Error reading fixed information.\n");
    return 1;
  }

  screensize = finfo.smem_len;
  depth = vinfo.bits_per_pixel;
  width = finfo.line_length / (depth/8);
  height = (screensize / (depth/8)) / width;
  frameBuffer = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, frameBufferFD, 0);
      
  draw(getMeta(paths[0]));
  for(;;) {
    unsigned char keyPress = getch();
    if(keyPress == '\n')
      break;
  }

  cleanUp();
	
	// Show Tingkat 2
	draw(getMeta(paths[1]));
	int status = system("./rolling-game");
	if(status == 0) {
		// Show Tingkat 3
		cleanUp();
		draw(getMeta(paths[2]));
		int status2 = system("./shooter-game");
		if(status2 == 0) {
			// Show Tingkat 4
			cleanUp();
			draw(getMeta(paths[3]));
			int status3 = system("./map-game");
			if(status3 == 0) {
				// Show Lulus
				cleanUp();
				draw(getMeta(paths[4]));
			} else {
				// Game Over
				printf("Game Over!\n");
				exit(1);
			}
		} else {
			// Game Over
			printf("Game Over!\n");
			exit(1);
		}
	} else {
		// Game Over
		printf("Game Over!\n");
		exit(1);
	}
	
	return 0;
}

void cleanUp()
{
  close(frameBufferFD);
  munmap(frameBuffer, screensize);
  
  system("setterm -cursor on");
  system("stty echo");
  system("clear");
}

void draw(imageData *meta)
{
  FILE *image;
  unsigned char *pixelBuffer = (unsigned char *) malloc(4);
  unsigned char *revertBuffer = (unsigned char *) malloc(4);
  unsigned int paddingHorizontal, paddingVertical;
  unsigned int dx, dy;
  unsigned int offsetBottom, offsetLeft, offsetRight;
  int i;
  int color = 0x00;
  unsigned int Bpp, imageWidth, imageHeight, imageOffset;
  bool isValid;
  char *imagePath;

  if(meta == NULL) {
    memset(frameBuffer, color, screensize);
    return;
  }

  Bpp = meta->bpp/8;
  imageWidth = meta->width;
  imageHeight = meta->height;
  imageOffset = meta->offset;
  imagePath = meta->path;
  isValid = meta->isValid;

  // Calculate the offsets for a centered menu
  dx = width - imageWidth;
  dy = height - imageHeight;

  if(dx > 0) paddingVertical = dx / 2;
  if(dy > 0) paddingHorizontal = dy / 2;

  // Draw the border
  offsetBottom = width * (paddingHorizontal + imageHeight) * Bpp;
  memset(frameBuffer, color, width * paddingHorizontal * Bpp);
  memset(frameBuffer + offsetBottom, color, width * paddingHorizontal * Bpp);
  
  for(i = 0; i < height; i++) {
    offsetLeft  = width * i * Bpp;
    offsetRight = offsetLeft + (paddingVertical + imageWidth) * Bpp;
    memset(frameBuffer + offsetLeft,  color, paddingVertical * Bpp);
    memset(frameBuffer + offsetRight, color, paddingVertical * Bpp);
  }

    // Draw the menu item
    image = fopen(imagePath, "r");
    fseek(image, imageOffset, SEEK_SET);

    int off;
    for(i = imageHeight - 1; i >= 0; i--) {
      off  = width * paddingHorizontal * Bpp;
      off += width * Bpp * i;
      off += paddingVertical * Bpp;

      int k;
      for(k = 0; k < imageWidth; k++) {
        fread(pixelBuffer, sizeof(char), Bpp, image);

        int j;
        for(j = 1; j <= Bpp; j++)
          revertBuffer[j-1] = pixelBuffer[j];
        revertBuffer[Bpp] = pixelBuffer[0];

        memcpy(frameBuffer + off + Bpp * k, revertBuffer, Bpp);
      }
    }
    
    fclose(image);

  free(pixelBuffer);
  free(revertBuffer);
  free(meta);
}

void usage()
{
  printf("Usage: ./fbmenu IMAGE_FOLDER\n");
  exit(1);
}
