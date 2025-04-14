#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize2.h"

char map[] = "@#$?x+;,. ";

int main(int argc, char** argv) {

    // default resolution
    int target_width = 160;
    int target_height = 80;

    int computeHeight = 0;

    if (argc < 2 || argc > 4) {
        printf("Usage: image2ascii <image> [width] [height]\n");
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        target_width = atoi(argv[2]);
        if (target_width <= 0) {
            printf("[width] must be a positive integer\n");
            exit(EXIT_FAILURE);
        }

        computeHeight = 1;
    } else if (argc == 4) {
        target_width = atoi(argv[2]);
        if (target_width <= 0) {
            printf("[width] must be a positive integer\n");
            exit(EXIT_FAILURE);
        }
        target_height = atoi(argv[3]);
        if (target_height <= 0) {
            printf("[height] must be a positive integer\n");
            exit(EXIT_FAILURE);
        }
    }

    // resize to fit terminal window
    unsigned char* in;

    int width, height, num_ch;
    in = stbi_load(argv[1], &width, &height, &num_ch, STBIR_RGB);
    if (in == NULL) {
        printf("Couldn't open %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (computeHeight) {
        double factor = (double)width / target_width;
        target_height = (int)(height / factor) / 2;
    }

    unsigned char* resized_img =
        calloc(target_width * target_height * STBIR_RGB, sizeof(unsigned char));
    if (resized_img == NULL) {
        printf("Couldn't allocate space.\n");
        exit(EXIT_FAILURE);
    }

    stbir_resize_uint8_linear(in,
                              width,
                              height,
                              0,
                              resized_img,
                              target_width,
                              target_height,
                              0,
                              3);

    width = target_width;
    height = target_height;

    int written = 0;
    for (int i = 0; i < width * height * 3; i += 3) {
        int r = resized_img[i];
        int g = resized_img[i + 1];
        int b = resized_img[i + 2];

        // see ITU BT.709 at https://www.itu.int/rec/R-REC-BT.709
        double br = ((0.2126 * r) + (0.7152 * g) + (0.0722 * b)) / 255;
        printf("%c", map[(int)floor(9 * br)]);
        written++;

        if (written == width) {
            written = 0;
            printf("\n");
        }
    }

    free(in);
    free(resized_img);

    return 0;
}
