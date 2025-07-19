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
#include <string.h>

void thread_blinkGreenLed(void);
void thread_blinkOrangeLed(void);
void thread_blinkRedLed(void);
void thread_blinkBlueLed(void);
void thread_sendUart(void *var);

const char *gHelloWord = "Hello Word!!\n\r";
uint32_t gSize = strlen(gHelloWord);

int main(void)
{
	Accelerometer3D::accData_t accData;
	float ratio;

	// 운영체체 초기화
	initializeYss();
	
	// 보드 초기화
	initializeBoard();

	// Function Queue 기능을 활용하여 순차 처리를 한다.
	fq.start();
	
	while(1)
	{
		thread::yield();
		accData = accelerometer.getAccData();
		
		if(accData.x > 0.f)
		{
			ratio = accData.x / 9.2f;
			if(ratio > 1.f)
				ratio = 1.f;
			pwm4Ch4.setDutyRatio(ratio);
			pwm4Ch2.setDutyRatio(0);
		}
		else
		{
			ratio = accData.x / 9.2f * -1.f;
			if(ratio > 1.f)
				ratio = 1.f;
			pwm4Ch4.setDutyRatio(0);
			pwm4Ch2.setDutyRatio(ratio);
		}

		if(accData.y > 0.f)
		{
			ratio = accData.y / 9.2f;
			if(ratio > 1.f)
				ratio = 1.f;
			pwm4Ch3.setDutyRatio(ratio);
			pwm4Ch1.setDutyRatio(0);
		}
		else
		{
			ratio = accData.y / 9.2f * -1.f;
			if(ratio > 1.f)
				ratio = 1.f;
			pwm4Ch3.setDutyRatio(0);
			pwm4Ch1.setDutyRatio(ratio);
		}

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
