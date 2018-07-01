#pragma once
#include "Singleton.h"
#include "Enemy.h"

/**
  *这是一个boss类

  * @param len1 最后一行的字符个数 也就是每次要发出的子弹数
  * @param len2 子弹起始位置
  * @param BossDead 表示boss是否死亡
  * @param flag 控制boss的左右移动
  */		   
class CBoss:public CEnemy
{
public:
	bool BossDead;///<控制boss死亡和激活
	bool flag;///<控制boss移动
	int len1;///<最后一行的字符个数 也就是每次要发出的子弹数
	int len2;///<子弹起始位置
	int AttributeOj;
public:
	/**
	  *更新boss的移动 
	*/
	void Update();
	/**
	  *初始化boss的数据 包括读boss图形文件 获去图形的最大行列 \n
	  *控制存放和去除不需要的字符 如回车符 空格符等
	*/
	void Init();
	CBoss();
	~CBoss();
};

