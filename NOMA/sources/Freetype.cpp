/* 
 * File:   Freetype.cpp
 * Author: laurasirventcollado
 * 
 * Created on 1 de marzo de 2014, 20:06
 */

#include "../headers/Freetype.h"
#include <cmath>

namespace freetype_mod {

    void font_data::init(const char * fname, unsigned int h) {
        this->h = h;

        FT_Library library;

        FT_Init_FreeType(&library);

        FT_Face face;

        //This is where we load in the font information from the file.
        //Of all the places where the code might die, this is the most likely,
        //as FT_New_Face will die if the font file does not exist or is somehow broken.
        FT_New_Face(library, fname, 0, &face);
        
        /*FT_Glyph glyph;
        FT_Get_Glyph(face->glyph, &glyph);
        
        FT_Matrix matrix;
        double angle = 0.1;
        matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
        matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
        matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
        matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
        
        FT_Glyph_Transform(glyph, &matrix, 0);*/
        
        //For some twisted reason, Freetype measures font size
        //in terms of 1/64ths of pixels.  Thus, to make a font
        //h pixels high, we need to request a size of h*64.
        //(h << 6 is just a prettier way of writting h*64)
        FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);

        for (unsigned short i = 0; i < 256; i++) chars[i] = new char_data(i, face);
        

        //We don't need the face information now that the display
        //lists have been created, so we free the assosiated resources.
        FT_Done_Face(face);

        FT_Done_FreeType(library);

    }

    void font_data::clean() {
        for (int i = 0; i < 256; i++) delete chars[i];
    }

    ///So while glRasterPos won't let us set the raster position using
    ///window coordinates, these hacky functions will let us move the current raster
    ///position a given delta x or y.

    inline void move_raster_x(int x) {
        glBitmap(0, 0, 0, 0, x, 0, NULL);
    }

    inline void move_raster_y(int y) {
        glBitmap(0, 0, 0, 0, 0, y, NULL);
    }


    ///Much like Nehe's glPrint function, but modified to work
    ///with freetype fonts.
    ///For this hack, I've taken out the newline processing, though it's easy to
    ///see how you could use the move_raster() functions to put newline processing back
    ///in.
    
    int getWidth(const font_data &ft_font, wchar_t *text){
        
        int width = 0;
        
        /*wchar_t text[256];
        va_list ap;
        va_start ( ap, fmt );
        vswprintf ( text, 256, fmt, ap );
        va_end ( ap );*/
        
         for (int i = 0; text[i]; i++) {
            const char_data &cdata = *ft_font.chars[text[i]];
            width += cdata.width;
        }
        
        return width;
    }
    
    int getHeight(const font_data &ft_font, wchar_t *text){
        
        int height = 0;
        /*wchar_t text[256];
        va_list ap;
        va_start ( ap, fmt );
        vswprintf ( text, 256, fmt, ap );
        va_end ( ap );*/
        
        for (int i = 0; text[i]; i++) {
            const char_data &cdata = *ft_font.chars[text[i]];
            if(i == 0)
                height = cdata.height;
            else{
                if(cdata.height > height)
                    height = cdata.height;
            }
        }
        
        return height;
        
    }

    void print(const font_data &ft_font, wchar_t *text) {

        /*wchar_t text[256]; // Holds Our String
        va_list ap; // Pointer To List Of Arguments

        if (fmt == NULL) // If There's No Text
            *text = 0; // Do Nothing

        else {
            va_start(ap, fmt); // Parses The String For Variables
            vswprintf(text, 256, fmt, ap); // And Converts Symbols To Actual Numbers
            va_end(ap); // Results Are Stored In Text
        }*/

        /*std::cout<<"Freetype prev:";
        for(int i = 0; i < 256; i++)
            std::cout<<fmt[i]<<",";
        std::cout<<std::endl;*/
        
       /* wchar_t text[256];
        
        if (fmt == NULL) // If There's No Text
            *text = 0; // Do Nothing
        
        va_list ap;
        va_start ( ap, fmt );
        vswprintf ( text, 256, fmt, ap );
        
        
        va_end ( ap );*/

        glPushAttrib(GL_CURRENT_BIT | GL_PIXEL_MODE_BIT | GL_ENABLE_BIT);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDisable(GL_LIGHTING);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //we'll be nice people and save the old pixel unpack alignment-
        //while setting the unpack allignment to one couldn't possibly
        //hurt anyone else's pixel drawing, it might slow it down.
        GLint old_unpack;
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &old_unpack);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        float color[4];
        glGetFloatv(GL_CURRENT_COLOR, color);

        glPixelTransferf(GL_RED_SCALE, color[0]);
        glPixelTransferf(GL_GREEN_SCALE, color[1]);
        glPixelTransferf(GL_BLUE_SCALE, color[2]);
        glPixelTransferf(GL_ALPHA_SCALE, color[3]);

        //std::cout<<"Freetype: ";
        for (int i = 0; text[i]; i++) {
            //std::cout<<text[i]<<",";
            const char_data &cdata = *ft_font.chars[text[i]];

            move_raster_x(cdata.left);
            move_raster_y(cdata.move_up);

            glDrawPixels(cdata.w, cdata.h, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, cdata.data);

            move_raster_y(-cdata.move_up);
            move_raster_x(cdata.advance - cdata.left);

        }
        //std::cout<<std::endl;

        glPixelStorei(GL_UNPACK_ALIGNMENT, old_unpack);
        glPopAttrib();
    }

}