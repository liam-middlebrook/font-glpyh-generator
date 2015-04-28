#include <stdio.h>
#include <FreeImage.h>

#define UNUSED (void)

int main(int argc, char** argv)
{
    UNUSED argc;
    UNUSED argv;

    FIBITMAP *bitmap = FreeImage_Allocate(640, 480, 32);

    for(int i = 0; i < 640; ++i)
    {
        // BGRA
        RGBQUAD value = {255, 0, 0, 128};

        FreeImage_SetPixelColor(bitmap, i, 128, &value);
    }

    for(int i = 0; i < 640; ++i)
    {
        // BGRA
        RGBQUAD value = {0, 255, 0, 0};

        FreeImage_SetPixelColor(bitmap, i, 64, &value);
    }

    for(int i = 0; i < 640; ++i)
    {
        // BGRA
        RGBQUAD value = {0, 0, 255, 0};

        FreeImage_SetPixelColor(bitmap, i, 256, &value);
    }

    if(FreeImage_Save(FIF_BMP, bitmap, "mybitmap.bmp", BMP_DEFAULT))
    {
        printf("Saved file to mybitmap.bmp\n");
    }

    FreeImage_Unload(bitmap);

    return 0;
}
