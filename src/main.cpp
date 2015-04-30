#include <stdio.h>
#include <FreeImage.h>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#define UNUSED (void)

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Error! No Font Specified!\n");
        return 1;
    }


    FIBITMAP* bitmap = FreeImage_Allocate(4096, 4096, 32);

    FT_Library library;

    FT_Init_FreeType(&library);

    FT_Face face;

    FT_New_Face(library, argv[1], 0, &face);

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();
    writer.String("glyphs");
    writer.StartArray();
    int tileSize = 64;
    int tileCount = 64;
    FT_Set_Pixel_Sizes(face, 0, tileSize);
    for (int c = 32, id = 0; c < 4096; ++c, ++id)
    {
        FT_Load_Char(face, c, FT_LOAD_RENDER);

        FT_Bitmap bmp = face->glyph->bitmap;

        FT_Glyph_Metrics metrics = face->glyph->metrics;

        int i = 0, j = 0;
        for (j = 0; j < bmp.rows; ++j)
        {
            for (i = 0; i < bmp.width; ++i)
            {
                RGBQUAD value = {bmp.buffer[j * bmp.width + i],
                                 bmp.buffer[j * bmp.width + i],
                                 bmp.buffer[j * bmp.width + i],
                                 bmp.buffer[j * bmp.width + i]};
                FreeImage_SetPixelColor(
                    bitmap, (id % tileCount) * tileSize + i,
                    (id / tileCount) * tileSize + bmp.rows - j, &value);
            }
        }

        writer.StartObject();
        {
            writer.String("id");
            writer.Uint(c);
            writer.String("char");
            writer.String((const char*)&c);
            writer.String("metrics");
            writer.StartObject();
            writer.String("width");
            writer.Int(metrics.width / 64);
            writer.String("height");
            writer.Int(metrics.height / 64);
            writer.String("horiBearingX");
            writer.Int(metrics.horiBearingX / 64);
            writer.String("horiBearingY");
            writer.Int(metrics.horiBearingY / 64);
            writer.String("horiAdvance");
            writer.Int(metrics.horiAdvance / 64);
            writer.String("vertBearingX");
            writer.Int(metrics.vertBearingX / 64);
            writer.String("vertBearingY");
            writer.Int(metrics.vertBearingY / 64);
            writer.String("vertAdvance");
            writer.Int(metrics.vertAdvance / 64);
        }
        writer.EndObject();

        writer.EndObject();
    }

    writer.EndArray();
    writer.EndObject();

    FILE* fp = fopen("glyphs.json", "w");

    fputs(s.GetString(), fp);

    fclose(fp);

    if (FreeImage_Save(FIF_BMP, bitmap, "font.bmp", BMP_DEFAULT))
    {
        printf("Saved file to font.bmp\n");
    }

    FreeImage_Unload(bitmap);

    return 0;
}
