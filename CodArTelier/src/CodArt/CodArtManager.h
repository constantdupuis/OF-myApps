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
