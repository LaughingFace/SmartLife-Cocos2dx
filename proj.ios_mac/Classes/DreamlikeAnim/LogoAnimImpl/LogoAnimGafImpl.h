//
//  LogoAnimGafImpl.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#ifndef __cocosProject__LogoAnimGafImpl__
#define __cocosProject__LogoAnimGafImpl__

#include <stdio.h>

#endif /* defined(__cocosProject__LogoAnimGafImpl__) */
#include "LogoAnim.h"
#include "Sources/GAF.h"
class LogoAnimGafImpl : public LogoAnim
{
private:
    gaf::GAFObject* _gafAnim;
public:
    virtual void performWorkingAnim(bool loop = false);
    virtual void performTongueAnim(bool loop = false);
    virtual void performMouseOpenAnim(bool loop = false);
    virtual void performMouseCloseAnim(bool loop = false);
    virtual void performNormalAnim(bool loop = false);
    virtual bool init();
    CREATE_FUNC(LogoAnimGafImpl);
};