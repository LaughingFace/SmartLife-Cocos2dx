//
//  BodyData.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-7.
//
//

#ifndef __cocosProject__BodyData__
#define __cocosProject__BodyData__

#include <stdio.h>

#endif /* defined(__cocosProject__BodyData__) */
class BodyData{
public:
    static const int BODY_PEAK = 1;
    static const int BODY_CIRCLE = 2;
    int data_id;
    void* data;
};