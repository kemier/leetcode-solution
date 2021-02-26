/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "list/list.h" //��ListΪ����
template <typename T>
class Queue : public List<T>
{                                                            //����ģ���ࣨ�̳�Listԭ�нӿڣ�
public:                                                      //size()��empty()�Լ��������Žӿھ���ֱ������
   void enqueue(T const &e) { List<T>::insertAsLast(e); }    //��ӣ�β������
   T dequeue() { return List<T>::remove(List<T>::first()); } //���ӣ��ײ�ɾ��
   T &front() { return List<T>::first()->data; }             //����
};

#include "queue_implementation.h"