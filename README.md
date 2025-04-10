# image2ascii

Image to ASCII converter written in C

# Dependencies

`stb_image.h` and `stb_image_resize2.h` from [stb] are used to parse and resize the input images.

# Usage

```console
./image2ascii <input> [width] [height]
```

Default output resolution is 160x80. If width is given without height, height is calculated as `width/2`.

Since characters' height is larger than their width, it is recommended to divide the target height by 2 and strecth the image.

[stb]: https://github.com/nothings/stb/tree/master
