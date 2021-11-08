#ifndef CANVASSETTINGS_H
#define CANVASSETTINGS_H

#include "ofMain.h"

#define CANVAS_SIZE_MODE_RAW "Raw"
#define CANVAS_SIZE_MODE_PAPER_FORMAT "PaperFormat"
#define CANVAS_SIZE_MODE_VIEW_PERCENT "ViewPercent"

namespace CodArTelier
{
    struct CanvasSizeModeRawSize {
        int width;
        int height;
    };

    struct CanvasSizeModePaperformat
    {
        string format_name;
        int resolution;
    };

    struct CanvasSizeModeViewPercentage
    {
        float width;
        float height;
        bool square_canvas;
        bool resize_when_view_change;
    };

    struct CanvasSettings {
        string size_mode {CANVAS_SIZE_MODE_VIEW_PERCENT};

        CanvasSizeModeRawSize raw {400,400};
        CanvasSizeModePaperformat paper_format {"A4", 300};
        CanvasSizeModeViewPercentage view_percentage {90.0f, 90.0f, false, false};
    };
}

#endif // CANVASSETTINGS_H