//
//  GoodsData.cpp
//  cocosProject
//
//  Created by mathcder23-mac on 15-8-4.
//
//

#include "GoodsData.h"
const int GoodsData::GOODS_SOCK = 1;
const int GoodsData::GOODS_BRIEFS = 2;
const int GoodsData::GOODS_TOWEL = 3;

GoodsData* GoodsData::_goodsDataSock;
GoodsData* GoodsData::_goodsDataBriefs;
GoodsData* GoodsData::_goodsDataTowel;
std::vector<GoodsData> GoodsData::_goodsDatas;
bool GoodsData::_init = false;
int GoodsData::_currentId = -1;
bool GoodsData::isCreate(){
     return _isCreate;
}
void GoodsData::setCreate(bool b){
     _isCreate = b;
}
void GoodsData::setResPath(std::string resPath){
     _resPath = resPath;
}
std::string GoodsData::getResPath(){
     return _resPath;
}
GoodsData::GoodsData(std::string resPath){
     setResPath(resPath);
}
GoodsData* GoodsData::getGoodsData(int id)
{
     
     switch(id)
     {
          case GOODS_SOCK:
               if (NULL == _goodsDataSock){
                    _goodsDataSock = new GoodsData("sock.png");
               }
               return _goodsDataSock;
          case GOODS_BRIEFS:
               if (NULL == _goodsDataBriefs){
                    _goodsDataBriefs = new GoodsData("briefs.png");
               }
               return _goodsDataBriefs;
          case GOODS_TOWEL:
               if (NULL == _goodsDataTowel)
                    _goodsDataTowel = new GoodsData("maojing.png");
               return _goodsDataTowel;
          default:
               return NULL;
     }
     
}
GoodsData* GoodsData::getGoodsDataList(){
     init();
    _goodsDatas[_currentId % _goodsDatas.size()].setCreate(false);
     return &_goodsDatas[_currentId % _goodsDatas.size()];
}
GoodsData* GoodsData::getNext(){
    init();
    if (_currentId >= 0)
    _goodsDatas[_currentId % _goodsDatas.size()].setCreate(false);
    _currentId ++;
    return &_goodsDatas[_currentId % _goodsDatas.size()];
}
bool GoodsData::init(){
     if (_init)
     {
          return _init;
     }
     _goodsDatas.push_back(GoodsData("sock.png"));
     _goodsDatas.push_back(GoodsData("briefs.png"));
     _goodsDatas.push_back(GoodsData("maojing.png"));
     _init = true;

}