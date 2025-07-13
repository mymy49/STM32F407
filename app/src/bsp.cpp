/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

FunctionQueue fq(16);

// PB6 I2C1 SCL
// PB7 I2C1 SDA

void initializeBoard(void)
{
	// LED 초기화
	Led::initialize();

	// usart2 초기화
	Usart::config_t usart2Config =
	{
		Uart::MODE_NORMAL,	//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,				//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,	//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		nullptr,			//void *rcvBuf;			// 수신 버퍼를 지정합니다.
		512					//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 지정합니다.
	};

	gpioA.setAsAltFunc(2, Gpio::PA2_USART2_TX);
	gpioA.setAsAltFunc(3, Gpio::PA3_USART2_RX);
	
	usart2.enableClock();
	usart2.initialize(usart2Config);
	usart2.enableInterrupt();

	// usart3 초기화
	Usart::config_t usart3Config =
	{
		Uart::MODE_NORMAL,	//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,				//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,	//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		nullptr,			//void *rcvBuf;			// 수신 버퍼를 지정합니다.
		512					//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 지정합니다.
	};

	gpioB.setAsAltFunc(10, Gpio::PB10_USART3_TX);
	gpioB.setAsAltFunc(11, Gpio::PB11_USART3_RX);
	
	usart3.enableClock();
	usart3.initialize(usart3Config);
	usart3.enableInterrupt();

	// usart4 초기화
	Usart::config_t usart4Config =
	{
		Uart::MODE_NORMAL,	//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,				//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,	//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		nullptr,			//void *rcvBuf;			// 수신 버퍼를 지정합니다.
		512					//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 지정합니다.
	};

	gpioA.setAsAltFunc(0, Gpio::PA0_UART4_TX);
	gpioA.setAsAltFunc(1, Gpio::PA1_UART4_RX);
	
	uart4.enableClock();
	uart4.initialize(usart4Config);
	uart4.enableInterrupt();

	// usart5 초기화
	Usart::config_t usart5Config =
	{
		Uart::MODE_NORMAL,	//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,				//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,	//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		nullptr,			//void *rcvBuf;			// 수신 버퍼를 지정합니다.
		512					//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 지정합니다.
	};

	gpioC.setAsAltFunc(12, Gpio::PC12_UART5_TX);
	gpioD.setAsAltFunc(2, Gpio::PD2_UART5_RX);
	
	uart5.enableClock();
	uart5.initialize(usart5Config);
	uart5.enableInterrupt();

	// usart6 초기화
	Usart::config_t usart6Config =
	{
		Uart::MODE_NORMAL,	//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,				//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,	//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		nullptr,			//void *rcvBuf;			// 수신 버퍼를 지정합니다.
		512					//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 지정합니다.
	};

	gpioC.setAsAltFunc(6, Gpio::PC6_USART6_TX);
	gpioC.setAsAltFunc(7, Gpio::PC7_USART6_RX);
	
	usart6.enableClock();
	usart6.initialize(usart6Config);
	usart6.enableInterrupt();
}

