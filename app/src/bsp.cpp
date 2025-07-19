/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

FunctionQueue fq(16);

LIS302DL accelerometer;

// PB6 I2C1 SCL
// PB7 I2C1 SDA

void initializeBoard(void)
{
	// SPI1 초기화
	gpioA.setAsAltFunc(5, Gpio::PA5_SPI1_SCK);
	gpioA.setAsAltFunc(6, Gpio::PA6_SPI1_MISO);
	gpioA.setAsAltFunc(7, Gpio::PA7_SPI1_MOSI);
	
	spi1.enableClock();
	spi1.initializeAsMain();
	spi1.enableInterrupt();
	
	// LIS302DL 초기화
	gpioE.setAsOutput(3);

	LIS302DL::config_t accConfig = 
	{
		spi1,						//Spi &peri;
		{&gpioE, 3},				//pin_t chipSelect;
		LIS302DL::DATARATE_100H,	//uint8_t datarate;
		LIS302DL::FULLSCALE_9p2G	//uint8_t fullscale;
	};

	accelerometer.initialize(accConfig);

	// PWM 초기화
	gpioD.setAsAltFunc(12, Gpio::PD12_TIM4_CH1);
	gpioD.setAsAltFunc(13, Gpio::PD13_TIM4_CH2);
	gpioD.setAsAltFunc(14, Gpio::PD14_TIM4_CH3);
	gpioD.setAsAltFunc(15, Gpio::PD15_TIM4_CH4);
	
	pwm4Ch1.enableClock();
	pwm4Ch1.initialize(3000);
	pwm4Ch1.start();
	pwm4Ch1.setDutyRatio(0);

	pwm4Ch2.initialize(3000);
	pwm4Ch2.start();
	pwm4Ch2.setDutyRatio(0);

	pwm4Ch3.initialize(3000);
	pwm4Ch3.start();
	pwm4Ch3.setDutyRatio(0);

	pwm4Ch4.initialize(3000);
	pwm4Ch4.start();
	pwm4Ch4.setDutyRatio(0);
}

