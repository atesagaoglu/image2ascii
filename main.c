#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize2.h"

char map[] = "@#$?x+;,. ";

int main(int argc, char** argv) {

    // default resolution
    int target_width = 160;
    int target_height = 80;

    if (argc < 2 || argc > 4) {
        printf("Usage: image2ascii <image> [width] [height]\n");
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        target_width = atoi(argv[2]);
        target_height = target_width / 2;
    } else if (argc == 4) {
        target_width = atoi(argv[2]);
        target_height = atoi(argv[3]);
    }

    // resize to fit terminal window
    unsigned char* in;
    unsigned char* resized_img =
        calloc(target_width * target_height * STBIR_RGB, sizeof(unsigned char));

    int width, height, num_ch;
    in = stbi_load(argv[1], &width, &height, &num_ch, STBIR_RGB);
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
    printf("h: %d, w: %d\n", height, width);

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
