#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <fstream>

#pragma pack(push, 1)
struct TGA_Header {
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
};
#pragma pack(pop)

struct TGAColor {
    union {
        struct {
            unsigned char r, g, b, a;
        };
        unsigned char raw[4];
        unsigned int  val;
    };
    int bytespp;

    TGAColor(): val(0), bytespp(1) {
    }

    TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A), bytespp(4) {
    }

    TGAColor(int v, int bpp) : val(v), bytespp(bpp) {
    }

    TGAColor(const TGAColor &c) : val(c.val), bytespp(c.bytespp) {
    }

    TGAColor(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
        for (int i = 0; i < bpp; i++ )
            raw[i] = p[i];
    }

    TGAColor & operator = (const TGAColor &c) {
        if (this != &c) {
            bytespp = c.bytespp;
            val = c.val;
        }
        return *this;
    }

};


class TGAImage {

    /* This is kind of Java private access modifier? */
    protected:
        unsigned char *data;

        int width,
            height,
            bytespp;  // Bytes per pixel?

        bool load_rle_data(std::ifstream &in);
        bool unload_rle_data(std::ofstream &out);
    
    public:
        enum Format {
            GRAYSCALE = 1,
            RGB = 3,
            RGBA = 4
        };

        TGAImage();
        TGAImage(int w, int h, int bpp);
        TGAImage(const TGATImage &img);
        ~TGAImage();
        TGAImage & operator =(const TGAImage &img);


        TGAColor get(int x, int y);

        bool read_tga_file(const char *filename);
        bool write_tga_file(const char *filename, bool rle=true);
        bool flip_horizontally();
        bool flip_vertically();
        bool scale(int w, int h);
        bool set(int x, int y, TGAColor c);

        int get_width();
        int get_height();
        int get_bytespp();

        unsigned char *buffer();

        void clear();
};

#endif // __IMAGE_H__
