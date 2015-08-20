package org.cocos2dx.cpp.ConnectionGuide.connectGuidePage;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.AnimationFragment;

/**
 * Created by mathcoder23 on 15-7-13.
 */
public class SelectDevice extends AnimationFragment {
    private OnChangePage mOnChangePage;
    private Context mContext;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.guide_page_select_device, container, false);
        this.mContext = this.getActivity().getApplicationContext();
        return view;
    }

    @Override
    public void animationIn() {

    }

    @Override
    public void animationOut() {

    }

    @Override
    public void animationPerform() {

    }

    @Override
    public void setOnChangePage(OnChangePage onChangePage) {
        this.mOnChangePage = onChangePage;
    }
}
