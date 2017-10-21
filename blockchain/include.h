#pragma once

//include
#include "math.h"
#include "afxcmn.h" //HANDLE
#include "afxmt.h" //CCriticalSection
//define
#define QUEUE_LENGTH 100 //��Ϣ���г���
#define QUEUE_BUFFER 20 //��Ϣ������Ϣ����

#define TANGLE_LENGTH 1000 //tangle����(������)
#define TIP_LENGTH 100 //tip����(������)

#define TASK_NONE 0
#define TASK_DEVICE_INITIAL 1
#define TASK_DEVICE_CONNECT 2
#define TASK_DEVICE_MERGE 3
#define TASK_DEVICE_OPTIMIZE 4
#define TASK_DEVICE_INDEXDAG 5
#define TASK_DEVICE_WALK 6
#define TASK_DAG_TRANSACTION 7
#define TASK_DAG_VALIDATION 8

#define MATH_ROTATE(a,n) (((a)<<(n))|(((a)&0xffffffff)>>(32-(n))))
//typedef
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned __int64 uint64;
typedef char int8;
typedef short int16;
typedef long int32;
typedef __int64 int64;
//struct
struct route_t
{
	uint8 flag;//0-δ����,1-����
	uint32 device_index;//���豸����(������Ψһ�����ַ)
	uint32 hops;//��Ծ���
	uint32 *path;//·��·��
	route_t *next;
};
struct queue_t
{
	volatile uint32 device_index;//�豸����(������Ψһ�����ַ)
	volatile uint32 info;//��Ϣ����.0-INFO_TX,1-INFO_RX,2-INFO_DONE,3-INFO_TRANSACTION
	volatile uint8 buffer[QUEUE_BUFFER];//������Ϣ
};
struct transaction_t
{
	uint32 weight_self;//����Ȩ��
	uint32 weight_accu;//�ۻ�Ȩ��
	uint32 height;//�߶�(��������)
	uint32 depth;//���(����Զtip)
	uint32 integral;//���׻���
	//hash_t address;//��ַ
	//hash_t trunk;//������
	//hash_t branch;//�ӽ���
	//hash_t bundle;//��
	//hash_t tag;//��ǩ
	volatile uint8 dag;//����״̬.0-tip,1-tangle
	volatile uint8 tip;//�����Ƿ���֤.0-none,1-solid
	volatile uint8 flag;//��������.0-none,1-milestone
	transaction_t *trunk_point;//�����׽ڵ�ָ��
	transaction_t *branch_point;//�ӽ��׽ڵ�ָ��
};
struct device_t
{
	//device
	uint32 x;
	uint32 y;
	uint8 line;//0-����,1-����
	uint32 device_index;//�豸����(������Ψһ�����ַ)
	uint8 status;//0-��Ϊfree,1-��Ϊmaster,2-��Ϊslave
	route_t *route;//�����豸·������
	queue_t queue[QUEUE_LENGTH];//�豸����Ϣ����(����/����)
	//dag
	volatile uint32 dag_index;//��������.0-������,����-������
	transaction_t tangle[TANGLE_LENGTH];//��tangle����
	uint32 tangle_index;//��tangle����
	transaction_t tip[TIP_LENGTH];//tip����
	uint32 tip_index;//tip����
	//application
	uint32 account_id;//�˻�id
	uint32 account_money;//�˻��ֽ�
};
//function
template <class classtype>
classtype math_max(classtype a,classtype b) {return a>b?a:b;}//���ֵ
template <class classtype>
classtype math_min(classtype a,classtype b) {return a<b?a:b;}//��Сֵ
void mem_swap8(uint8 *result,uint32 len);
void mem_word2byte(uint8 *a,uint32 b);
uint32 mem_byte2word(uint8 *a);
int32 math_hashcode(int8 *a,uint32 length);
double math_distance(uint32 x1,uint32 y1,uint32 x2,uint32 y2);
