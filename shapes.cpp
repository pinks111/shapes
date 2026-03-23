#include <iostream>
#include <ctime>

#include "App.h"
#include "Identi.h"
#include "Storage.h"

int main() {
    
     App app;
     Identi i1 = app.addObject(PrimitiveType::POINT);
     Identi i2 = app.addObject(PrimitiveType::POINT);
     Storage<Identi> stor(2);
     stor.addItem(i1);
     stor.addItem(i2);
     app.addArrange(MutualArrangeType::POINTCOINCIDENT,stor);

     Identi i3 = app.addObject
     (PrimitiveType::SEGMENT);
     Identi i4 = app.addObject(PrimitiveType::SEGMENT);

     Storage<Identi> stor1(2);
     stor.addItem(i3);
     stor.addItem(i4);
     
     app.addArrange(MutualArrangeType::SEGMENTSNORMAL,stor);

     Identi i5 = app.addObject(PrimitiveType::POINT);

     Storage<Identi> stor2(2);
     stor.addItem(i3);
     stor.addItem(i5);     

     app.addArrange(MutualArrangeType::POINTOBELONGSEGMENT,stor2);
     app.addArrange(MutualArrangeType::POINTOBELONGSEGMENT,stor2);

     Storage<Identi> stor3(1);
     stor.addItem(i3);     
     app.addArrange(MutualArrangeType::SEGMENTLENGTH,stor, 10.1 );


    return 0;
}
