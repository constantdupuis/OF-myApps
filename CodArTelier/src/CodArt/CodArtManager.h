#pragma once

#include "ofMain.h"
#include "CodArt.h"
#include "Canvas.h"
#include "DrawerBase.h"
#include "DrawerManager.h"
#include "ofxXmlSettings.h"


namespace CodArTelier
{
    class CodArtManager {
    public:
        CodArtManager() {
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        vector<string> DrawerNames()
        {
            return drawer_manager_.DrawerNames();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="names"></param>
        /// <param name="descriptions"></param>
        /// <param name="ids"></param>
        void GetDrawersInfos(vector<string>& names, vector<string>& descriptions, vector<string>& ids)
        {
            for (const auto& drw : drawer_manager_.DrawersNfoNFactories())
            {
                names.push_back(drw->Name());
                descriptions.push_back(drw->Description());
                ids.push_back(drw->Id());
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="settings"></param>
        /// <returns></returns>
        shared_ptr<CodArt> CreateCodArtFromXmlSettings(ofxXmlSettings settings)
        {
            shared_ptr<CodArt> codart = make_shared<CodArt>();
            CanvasSettings canvas_settings;

            auto drawer_id = settings.getValue("codart:drawer:id", "none");

            codart->setName( settings.getValue("codart:name", "") );
            codart->setDescription( settings.getValue("codart:description", "") );

            canvas_settings.size_mode  = settings.getValue("codart:canvas:size_mode", "none");

            if( canvas_settings.size_mode == "none" )
            {
                ofLogError("CodArtManager") << "No size mode in config file.";
                return nullptr;
            }
            else if(canvas_settings.size_mode == CANVAS_SIZE_MODE_RAW)
            {
                canvas_settings.raw.width = settings.getValue("codart:canvas:raw:width", 0);
                canvas_settings.raw.height = settings.getValue("codart:canvas:raw:height", 0);
            }
            else if(canvas_settings.size_mode == CANVAS_SIZE_MODE_PAPER_FORMAT)
            {
                // TODO
                ofLogWarning("CodArtManager") << "CANVAS_SIZE_MODE_PAPER_FORMAT not yet implemented.";
                return nullptr;
            }
            else if(canvas_settings.size_mode == CANVAS_SIZE_MODE_VIEW_PERCENT)
            {
                canvas_settings.view_percentage.square_canvas = settings.getValue("codart:canvas:view_percentage:square_canvas", true);
                canvas_settings.view_percentage.resize_when_view_change = settings.getValue("codart:canvas:view_percentage:resize_when_view_change", true);
                canvas_settings.view_percentage.width = settings.getValue("codart:canvas:view_percentage:width", 90.0);
                canvas_settings.view_percentage.height = settings.getValue("codart:canvas:view_percentage:height", 90.0);
            }
            else
            {
                ofLogError("CodArtManager") << "Unknown canvas size mode [" << canvas_settings.size_mode << "] in config file.";
                return nullptr;
            }

            auto drawer = drawer_manager_.BuildDrawer(drawer_id);
            if (!drawer)
            {
                ofLogError("CodArtManager") << "CreateCodArt, drawer [" << drawer_id << "] doesn't exists!";
                return nullptr;
            }

            settings.pushTag("codart"); 
            settings.pushTag("drawer");
            drawer->ConfigureFromXmlSettings(settings);
            settings.popTag(); 
            settings.popTag();

            // Build CodArt with given parameters
            if (!codart->Setup(drawer, canvas_settings))
            {
                ofLogNotice("CodArtManager") << "CodArt creation failed, drawer id [" << drawer_id << "]";
                return nullptr;
            }

            ofLogNotice("CodArtManager") << "CodArt created with drawer id [" << drawer_id << "]";
            return codart;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="drawer_id"></param>
        /// <param name="canvas_settings"></param>
        /// <returns></returns>
        shared_ptr<CodArt> CreateCodArt(string drawer_id, CanvasSettings canvas_settings)
        {
            shared_ptr<CodArt> codart;
            codart = make_shared<CodArt>();

            auto drawer = drawer_manager_.BuildDrawer(drawer_id);
            if (!drawer)
            {
                ofLogError("CodArtManager") << "CreateCodArt, drawer [" << drawer_id << "] doesn't exists!";
                return nullptr;
            }

            // Build CodArt with given parameters
            if (codart->Setup(drawer, canvas_settings))
            {
                ofLogNotice("CodArtManager") << "CodArt created with drawer id [" << drawer_id << "]";
                return codart;
            }

            // log error 
            ofLogError("CodArtManager") << "Unable to create CodArt with drawer id [" << drawer_id << "]";
            return nullptr;
        }

    private:
        DrawerManager drawer_manager_;
    };
}
