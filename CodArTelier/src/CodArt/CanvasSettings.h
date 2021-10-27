#ifndef CANVASSETTINGS_H
#define CANVASSETTINGS_H

#include "ofMain.h"

namespace CorArtelier
{
    enum class CanvasSizeMode {Raw, PaperFormat, ViewPercentage};

    struct CanvasSettings {
        CanvasSizeMode size_mode { CanvasSizeMode::ViewPercentage };
        union size{
            struct raw{
                int width { 400 };
                int height { 400 };
                int resolution { 92 };
            };
            struct paper_format{
                string format_name {"A4"};
                int resolution {300};
            };
            struct view_percentage{
                float width {100.0f};
                float height {100.0f};
            };
        };
    };
}

#endif // CANVASSETTINGS_H
