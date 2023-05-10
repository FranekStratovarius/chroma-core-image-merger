#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char** argv)
{
	int width, height ,channels;
	unsigned char *color_image = stbi_load("color_areas.png", &width, &height, &channels, 0);
	if(color_image == NULL) {
		printf("could not load color image\n");
		return 1;
 	}
	unsigned char *greyscale_image = stbi_load("greyscale.png", &width, &height, &channels, 4);
	if(greyscale_image == NULL) {
		printf("could not load greyscale image\n");
		return 1;
 	}

	unsigned char *output_image = (unsigned char*)malloc(width * height * 4 * sizeof(unsigned char));
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			int greyscale = (
				greyscale_image[width * channels * y + x * channels]
				+ greyscale_image[width * channels * y + x * channels + 1]
				+ greyscale_image[width * channels * y + x * channels + 2]
			) / 4;
			output_image[width * 4 * y + x * 4]		= color_image[width * channels * y + x * channels];
			output_image[width * 4 * y + x * 4 + 1]	= greyscale;
			output_image[width * 4 * y + x * 4 + 2]	= 0;
			output_image[width * 4 * y + x * 4 + 3]	= greyscale_image[width * channels * y + x * channels + 3];
		}
	}

	int _result = stbi_write_png("out.png", width, height, 4, output_image, width * 4);

	stbi_image_free(color_image);
	stbi_image_free(greyscale_image);
	free(output_image);

	return 0;
}
