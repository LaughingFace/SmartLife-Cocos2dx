//
//  GoodsData.h
//  cocosProject
//
//  Created by mathcder23-mac on 15-8-4.
//
//

#ifndef __cocosProject__GoodsData__
#define __cocosProject__GoodsData__

#include <stdio.h>
#include <string>
#include <vector>
#endif /* defined(__cocosProject__GoodsData__) */
using namespace std;
class GoodsData{
private:
     bool _isCreate = false;
     static bool _init ;
     std::string _resPath;
     static int _currentId;
     static vector<GoodsData> _goodsDatas;
     //model instance;
     static GoodsData* _goodsDataSock;
     static GoodsData* _goodsDataBriefs;
     static GoodsData* _goodsDataTowel;
     static bool init();
public:
     //model select
     static const int GOODS_SOCK;
     static const int GOODS_BRIEFS;
     static const int GOODS_TOWEL;
     GoodsData(std::string resPath);
     
     
     static GoodsData* getGoodsData(int id);
     static GoodsData* getGoodsDataList();
     
     bool isCreate();
     std::string getResPath();
     void setCreate(bool b);
     void setResPath(std::string resPath);
     static GoodsData* getNext();
};
