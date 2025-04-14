# image2ascii

Image to ASCII converter written in C

# Dependencies

`stb_image.h` and `stb_image_resize2.h` from [stb] are used to parse and resize
the input images.

# Usage

```console

make
./image2ascii <input> [width] [height]
```

Default output resolution is 160x80. If width is given without height, image is
scaled up or down accordingly. Please note that height is divided by 2 to avoid
strected look.

Since characters' height is larger than their width, it is recommended to
enter the half of the desired height avoid strected look.

[stb]: https://github.com/nothings/stb/tree/master
