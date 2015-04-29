#include <stdio.h>
#include <FreeImage.h>


#include <ft2build.h>
#include FT_FREETYPE_H
#define UNUSED (void)

int main(int argc, char** argv)
{
    UNUSED argc;
    UNUSED argv;

    FIBITMAP *bitmap = FreeImage_Allocate(640, 480, 32);

    FT_Library library;

    FT_Init_FreeType(&library);

    FT_Face face;

    FT_New_Face(library, "/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 0, &face);
    //FT_New_Face(library, "/usr/share/fonts/gnu-free/FreeSerif.ttf", 0, &face);

    FT_Set_Pixel_Sizes(face, 0, 128);


    FT_Load_Char(face, 99, FT_LOAD_RENDER);

    FT_Bitmap bmp = face->glyph->bitmap;

    printf("w: %d h: %d\n", bmp.width, bmp.rows);
    printf("w: %d h: %d\n", face->glyph->bitmap_left, face->glyph->bitmap_top);

    int i = 0, j = 0;
    for(j = 0; j < bmp.rows; ++j)
    {
        for(i = 0; i < bmp.width; ++i)
        {
          RGBQUAD value = {bmp.buffer[j * bmp.width + i],
                           bmp.buffer[j * bmp.width + i],
                           bmp.buffer[j * bmp.width + i],
                           bmp.buffer[j * bmp.width + i]};
            FreeImage_SetPixelColor(bitmap, i, bmp.rows - j, &value);
        }
    }

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
