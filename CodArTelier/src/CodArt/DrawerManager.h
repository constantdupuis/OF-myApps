#ifndef DRAWERMANAGER_H
#define DRAWERMANAGER_H

#include "ofMain.h"
#include "DrawerBase.h"
#include "CodArt/Drawers/ArdoiseFbm.h"

namespace CodArTelier
{
    class DrawerManager{
    public:
        DrawerManager() {

            shared_ptr<DrawerInfoAndFactoryBase> d = make_shared<CodArTelier::Drawer::ArdoiseFbmInfoNFactory>();
            ofLog(OF_LOG_NOTICE, "DrawerManager") << "Register drawer [" << d->Name() << "] id [" << d->Id() << "]";
            drawers_.push_back( d );
            drawers_names_.push_back( d->Name());
            drawers_by_id_[d->Id()] = d;
        }

        const vector<string>& DrawerNames()
        {
            return drawers_names_;
        }

        shared_ptr<DrawerBase> BuildDrawer(int drawerIdx)
        {
            if( drawerIdx > -1 && drawerIdx < drawers_.size())
            {
                return drawers_[drawerIdx]->Build();
            }
            ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer index out of range !";
            return nullptr;
        }

        shared_ptr<DrawerBase> BuildDrawer(string drawerId)
        {
            if( drawers_by_id_.find(drawerId) == drawers_by_id_.end())
            {
                ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer ID ["<< drawerId <<"] not found !";
                return nullptr;
            }

            return drawers_by_id_[drawerId]->Build();
        }

    private:
        std::vector<shared_ptr<DrawerInfoAndFactoryBase>> drawers_;
        std::vector<std::string> drawers_names_;
        std::map<string, shared_ptr<DrawerInfoAndFactoryBase>> drawers_by_id_;
    };
}

#endif // DRAWERMANAGER_H
