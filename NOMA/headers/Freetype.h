/* 
 * File:   Freetype.h
 * Author: laurasirventcollado
 *
 * Created on 1 de marzo de 2014, 20:06
 */

#ifndef FREETYPE_H
#define	FREETYPE_H

// FreeType Headers
#include "../Freetype/include/ft2build.h"
#include "../Freetype/include/freetype.h"
#include "../Freetype/include/ftglyph.h"
#include "../Freetype/include/ftoutln.h"
#include "../Freetype/include/fttrigon.h"

// OpenGL Headers
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <vector>
#include <string>
#include <iostream>
#include <wchar.h>

//MSVC will spit out all sorts of useless warnings if
//you create vectors of strings, this pragma gets rid of them.
#pragma warning(disable: 4786) 


///Wrap everything in a namespace, that we can use common
///function names like "print" without worrying about
///overlapping with anyone else's code.
namespace freetype_mod {

    //Inside of this namespace, give ourselves the ability
    //to write just "vector" instead of "std::vector"
    using std::vector;

    //Ditto for string.
    using std::string;

    ///This is the datastructure that I'm using to store everything I need
    ///to render a character glyph in opengl.  

    struct char_data {
        int w, h;
        int width, height;
        int advance;
        int left;
        int move_up;
        unsigned char * data;

        char_data(char ch, FT_Face face) {

            // Load The Glyph For Our Character.
            FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);

            // Move The Face's Glyph Into A Glyph Object.
            FT_Glyph glyph;
            FT_Get_Glyph(face->glyph, &glyph);
            
            FT_BBox bbox;
            FT_Glyph_Get_CBox(glyph,FT_GLYPH_BBOX_TRUNCATE,&bbox);

            width = glyph->advance.x;
            height = bbox.yMax - bbox.yMin;
            
            // Convert The Glyph To A Bitmap.
            
            FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;

            // This Reference Will Make Accessing The Bitmap Easier.
            FT_Bitmap& bitmap = bitmap_glyph->bitmap;

            advance = face->glyph->advance.x >> 6;
            left = bitmap_glyph->left;
            w = bitmap.width;
            h = bitmap.rows;
            move_up = bitmap_glyph->top - bitmap.rows;
            width = advance;

            data = new unsigned char[2 * w * h];
            for (int x = 0; x < w; x++) for (int y = 0; y < h; y++) {
                    const int my = h - 1 - y;
                    data[2 * (x + w * my)] = 255;
                    data[2 * (x + w * my) + 1] = bitmap.buffer[x + w * y];
                }
        }

        ~char_data() {
            delete [] data;
        }
    };

    //This holds all of the information related to any
    //freetype font that we want to create.  

    struct font_data {
        char_data * chars[256];

        float h;

        //The init function will create a font of
        //of the height h from the file fname.
        void init(const char * fname, unsigned int h);

        //Free all the resources assosiated with the font.
        void clean();
    };

    //The flagship function of the library - this thing will print
    //out text at the current raster position using the font ft_font.
    //The current modelview matrix will also be applied to the text. 
    void print(const font_data &ft_font, wchar_t *text);
    
    int getWidth(const font_data &ft_font, wchar_t *text);
    int getHeight(const font_data &ft_font, wchar_t *text);

}

#endif	/* FREETYPE_H */

