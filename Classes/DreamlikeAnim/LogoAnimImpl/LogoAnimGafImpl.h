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
#include "../LogoAnim.h"
#include "../../Sources/GAF.h"
using namespace gaf;
class LogoAnimGafImpl : public LogoAnim
{
private:
    gaf::GAFObject* _gafAnim;
    void finishedNormalAnim();
public:
    virtual void performWorkingAnim(bool loop = false) ;
    virtual void performTongueAnim(bool loop = false) ;
    virtual void performMouseOpenAnim(bool loop = false) ;
    virtual void performMouseCloseAnim(bool loop = false) ;
    virtual void performNormalAnim(bool loop = false) ;
    virtual Rect getBoundingBox() const;
    virtual bool init();
    CREATE_FUNC(LogoAnimGafImpl);
};
#endif /* defined(__cocosProject__LogoAnimGafImpl__) */
