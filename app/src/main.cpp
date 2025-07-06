/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <task.h>
#include <util/runtime.h>
#include <yss/debug.h>

void thread_blinkGreenLed(void);
void thread_blinkOrangeLed(void);
void thread_blinkRedLed(void);
void thread_blinkBlueLed(void);

int main(void)
{
	// 운영체체 초기화
	initializeYss();
	
	// 보드 초기화
	initializeBoard();

	// Function Queue 기능을 활용하여 순차 처리를 한다.
	fq.start();
	
	// LED 깜박이는 쓰레드를 스케줄러에 등록
	thread::add(thread_blinkGreenLed, 512);
	thread::add(thread_blinkOrangeLed, 512);
	thread::add(thread_blinkRedLed, 512);
	thread::add(thread_blinkBlueLed, 512);

	while(1)
	{
		debug_printf("%d\r", (uint32_t)runtime::getMsec());
		thread::yield();
	}
}

void thread_blinkGreenLed(void)
{
	while(1)
	{
		Led::setGreen(true);
		thread::delay(250);
		Led::setGreen(false);
		thread::delay(250);
	}
}

void thread_blinkOrangeLed(void)
{
	while(1)
	{
		Led::setOrange(true);
		thread::delay(500);
		Led::setOrange(false);
		thread::delay(500);
	}
}

void thread_blinkRedLed(void)
{
	while(1)
	{
		Led::setRed(true);
		thread::delay(1000);
		Led::setRed(false);
		thread::delay(1000);
	}
}

void thread_blinkBlueLed(void)
{
	while(1)
	{
		Led::setBlue(true);
		thread::delay(2000);
		Led::setBlue(false);
		thread::delay(2000);
	}
}
