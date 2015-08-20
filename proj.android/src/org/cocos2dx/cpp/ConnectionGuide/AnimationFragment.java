package org.cocos2dx.cpp.ConnectionGuide;

import android.support.v4.app.Fragment;

/**
 * Created by mathcoder23 on 15-7-9.
 */
public abstract class AnimationFragment extends Fragment {
    public abstract void animationIn();
    public abstract void animationOut();
    public abstract void animationPerform();
    public abstract void setOnChangePage(OnChangePage onChangePage);
    public interface OnChangePage{
        void nextPage();
        void nextPage(AnimationFragment fragment);
        void previousPage();
        void initFinished(AnimationFragment fragment);
    }
}
