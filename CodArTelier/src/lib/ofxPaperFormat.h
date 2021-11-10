#ifndef OFXPAPERFORMAT_H
#define OFXPAPERFORMAT_H

#include "ofMain.h"

class ofxPaperFormat{
public:
    enum class Orientation { Portrait, Landscape};
    enum class APaperFormat { A0 = 0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10};

    glm::vec2 PaperToPixels( string paper_format_name, int dpi, Orientation orientation ){
        bool found = false;
        int index = 0;
        for( const auto& f : a_paper_size_name_)
        {
            if( f == paper_format_name)
            {
                return PaperToPixels((APaperFormat)index, dpi, orientation);
            }
            index++;
        }
        return glm::vec2(-1.0, -1.0f);
    }

    glm::vec2 PaperToPixels( APaperFormat paper_format_name, int dpi, Orientation orientation ){
        glm::vec2 size = paper_size_inch_[(int)paper_format_name] * dpi;
        if( orientation == Orientation::Landscape)
        {
            std::swap(size.x, size.y);
        }
        return size;
    }

    std::vector<string>& APaperFormatNames() {
        return a_paper_size_name_;
    }

private:
    std::vector<string> a_paper_size_name_ {"A0", "A1", "A2", "A3", "A4","A5","A6","A7", "A8","A9","A10"};
    const std::vector<glm::vec2> paper_size_inch_ {
        {33.1f, 46.8f}, // A0
        {23.4f, 33.1f}, // A1
        {16.5f, 23.4f}, // A2
        {11.7f, 16.5f}, // A3
        {8.27f, 11.7f}, // A4
        {5.83f, 8.27f}, // A5
        {4.13f, 5.83f}, // A6
        {2.91f, 4.13f}, // A7
        {2.05f, 2.91f}, // A8
        {1.46f, 2.05f}, // A9
        {1.02f, 1.46f} // A10
    };
};

#endif // OFXPAPERFORMAT_H
