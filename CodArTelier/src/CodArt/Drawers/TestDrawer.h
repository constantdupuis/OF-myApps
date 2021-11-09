#ifndef TESTDRAWER_H
#define TESTDRAWER_H

#include "../DrawerBase.h"
namespace CodArTelier
{
    namespace Drawer
    {
        class TestDrawer : public DrawerBase{
        public:
            TestDrawer( string id ) : DrawerBase(id) {

            }

            void Draw()
            {
                ofBackground( ofColor().red );
                ofFill();
                ofSetColor(ofColor().green);
                ofDrawLine(0,0, canvas_size_.x, canvas_size_.y);
                ofDrawLine(0, canvas_size_.y, canvas_size_.x , 0);
            }
        };

        class TestDrawerInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            TestDrawerInfoNFactory(){
                id_ = "TestDrawer";
                name_ = "Test Drawer";
                description_ = "Dessine de simples formes pour tester les drawers";
            }

            shared_ptr<DrawerBase> Build(){
                return make_shared<TestDrawer>(id_);
            }

        };
    }
}

#endif // TESTDRAWER_H
