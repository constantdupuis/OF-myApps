#ifndef CANVASSETTINGS_H
#define CANVASSETTINGS_H

#include "ofMain.h"

namespace CodArTelier
{
    enum class CanvasSizeMode {Raw = 0, PaperFormat, ViewPercentage};

    struct CanvasSettings {
        CanvasSettings() {}
        ~CanvasSettings() {}

        CanvasSizeMode size_mode { CanvasSizeMode::ViewPercentage };
        union {
            struct {
                int width { 400 };
                int height { 400 };
            } raw;
            struct {
                string format_name {"A4"};
                int resolution {300};
            } paper_format;
            struct {
                float width {90.0f};
                float height {90.0f};
                bool square_canvas = false;
                bool resize_when_view_change = false;
            } view_percentage;
        };
    };
}

#endif // CANVASSETTINGS_H
