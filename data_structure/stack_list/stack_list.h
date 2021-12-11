/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "list/list.h" //���б�Ϊ���࣬������ջģ����
template <typename T>
class Stack : public List<T>
{                                                       //���б����/ĩ����Ϊջ��/��
public:                                                 //size()��empty()�Լ��������Žӿڣ�����ֱ������
   void push(T const &e) { List<T>::insertAsLast(e); }  //��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
   T pop() { return List<T>::remove(List<T>::last()); } //��ջ����Ч��ɾ���б����Ԫ��
   T &top() { return List<T>::last()->data; }           //ȡ����ֱ�ӷ����б����Ԫ��
};
