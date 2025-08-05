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

EulerAngle2Axis angle;


// PB6 I2C1 SCL
// PB7 I2C1 SDA

void initializeBoard(void)
{
	// LED 초기화
	Led::initialize();

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
		LIS302DL::DATARATE_100HZ,	//uint8_t datarate;
		LIS302DL::FULLSCALE_9p2G	//uint8_t fullscale;
	};

	accelerometer.initialize(accConfig);

	// EulerAngle2Axis 초기화
	EulerAngle2Axis::config_t angleConfig = 
	{
		&accelerometer,					//Accelerometer3Axis *obj;
		EulerAngle2Axis::UNIT_DEGREE,	//unit_t unit;
		0.10,							//float threshold;
		4,								//float ratio;
		100								//uint32_t stableTime;
	};

	angle.initialize(angleConfig);
	angle.run();
}

