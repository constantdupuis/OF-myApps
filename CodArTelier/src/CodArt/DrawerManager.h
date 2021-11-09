#ifndef DRAWERMANAGER_H
#define DRAWERMANAGER_H

#include "ofMain.h"
#include "DrawerBase.h"
#include "CodArt/Drawers/ArdoiseFbm.h"
#include "CodArt/Drawers/TestDrawer.h"

namespace CodArTelier
{
    class DrawerManager{
    public:
        DrawerManager() {

            shared_ptr<DrawerInfoAndFactoryBase> d = make_shared<CodArTelier::Drawer::ArdoiseFbmInfoNFactory>();
            ofLog(OF_LOG_NOTICE, "DrawerManager") << "Register drawer [" << d->Name() << "] id [" << d->Id() << "]";
            drawers_info_factory_.push_back( d );
            drawers_names_.push_back( d->Name());
            drawers_info_n_factory_by_id_[d->Id()] = d;

            d = make_shared<CodArTelier::Drawer::TestDrawerInfoNFactory>();
            ofLog(OF_LOG_NOTICE, "DrawerManager") << "Register drawer [" << d->Name() << "] id [" << d->Id() << "]";
            drawers_info_factory_.push_back( d );
            drawers_names_.push_back( d->Name());
            drawers_info_n_factory_by_id_[d->Id()] = d;

        }

        vector<string>& DrawerNames()
        {
            return drawers_names_;
        }

        const vector<shared_ptr<DrawerInfoAndFactoryBase>>& DrawersNfoNFactories()
        {
            return drawers_info_factory_;
        }

        shared_ptr<DrawerInfoAndFactoryBase> GetDrawerInfoNFactory( int drawerIdx )
        {
            if( drawerIdx > -1 && drawerIdx < drawers_info_factory_.size())
            {
                return drawers_info_factory_[drawerIdx];
            }
            ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer index out of range !";
            return nullptr;
        }

        shared_ptr<DrawerInfoAndFactoryBase> GetDrawerInfoNFactory( string drawerId )
        {
            if( drawers_info_n_factory_by_id_.find(drawerId) == drawers_info_n_factory_by_id_.end())
            {
                ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer ID ["<< drawerId <<"] not found !";
                return nullptr;
            }

            return drawers_info_n_factory_by_id_[drawerId];
        }

        shared_ptr<DrawerBase> BuildDrawer(int drawerIdx)
        {
            if( drawerIdx > -1 && drawerIdx < drawers_info_factory_.size())
            {
                return drawers_info_factory_[drawerIdx]->Build();
            }
            ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer index out of range !";
            return nullptr;
        }

        shared_ptr<DrawerBase> BuildDrawer(string drawerId)
        {
            if( drawers_info_n_factory_by_id_.find(drawerId) == drawers_info_n_factory_by_id_.end())
            {
                ofLog(OF_LOG_ERROR,"DrawerManager") << "DuildDrawer - Drawer ID ["<< drawerId <<"] not found !";
                return nullptr;
            }

            return drawers_info_n_factory_by_id_[drawerId]->Build();
        }

    private:
        std::vector<shared_ptr<DrawerInfoAndFactoryBase>> drawers_info_factory_;
        std::vector<std::string> drawers_names_;
        std::map<string, shared_ptr<DrawerInfoAndFactoryBase>> drawers_info_n_factory_by_id_;
    };
}

#endif // DRAWERMANAGER_H
