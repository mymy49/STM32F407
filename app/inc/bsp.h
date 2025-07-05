/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef BSP__H_
#define BSP__H_

#include <util/FunctionQueue.h>

// 보드의 장치들을 초기화 한다.
void initializeBoard(void);

extern FunctionQueue fq;

#endif

