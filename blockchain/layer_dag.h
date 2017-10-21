#pragma once

//include
#include "crypt_hash.h"
#include "layer_device.h"
//define
#define DAG_TIP 0 //������dag��
#define DAG_TANGLE 1 //������dag��

#define TIP_NONE 0 //tip���ɿ�(δ����������֤)
#define TIP_SOLID 1 //tip�ɿ�(����������֤)

#define MILESTONE_NONE 0 //milestone���ɿ�(δ�����˱���֤)
#define MILESTONE_SOLID 1 //milestone�ɿ�(�����˱���֤)

#define CACHE_LENGTH 10 //cache�ڵ����
//typedef
//struct
//function
uint8 process_dag(device_t *device);