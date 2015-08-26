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
class LogoAnimGafImpl : public LogoAnim
{
private:
    gaf::GAFObject* _gafAnim;
public:
    virtual void performWorkingAnim(bool loop = false) const;
    virtual void performTongueAnim(bool loop = false) const;
    virtual void performMouseOpenAnim(bool loop = false) const;
    virtual void performMouseCloseAnim(bool loop = false) const;
    virtual void performNormalAnim(bool loop = false) const;
    virtual Rect getBoundingBox() const;
    virtual bool init();
    CREATE_FUNC(LogoAnimGafImpl);
};
#endif /* defined(__cocosProject__LogoAnimGafImpl__) */
