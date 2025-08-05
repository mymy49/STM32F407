/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>
#include <targets/st/bitfield.h>

FunctionQueue fq(16);

ToneGenerator gen(i2s3);

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

	// I2C1 초기화
	gpioB.setAsAltFunc(6, Gpio::PB6_I2C1_SCL, Gpio::OSPEED_MID, Gpio::OTYPE_OPEN_DRAIN);
	gpioB.setAsAltFunc(7, Gpio::PB7_I2C1_SDA, Gpio::OSPEED_MID, Gpio::OTYPE_OPEN_DRAIN);

	I2c::config_t i2c1Config = 
	{
		I2c::MODE_MAIN,			//mode_t mode;			// 통신 모드 (Main 전용)
		I2c::SPEED_STANDARD,	//speed_t speed;			// 통신 속도 (Main 전용)
	};

	i2c1.initialize(i2c1Config);

	// I2S3 초기화
	gpioC.setAsAltFunc(7, Gpio::PC7_I2S3_MCK);
	gpioC.setAsAltFunc(10, Gpio::PC10_I2S3_CK);
	gpioC.setAsAltFunc(12, Gpio::PC12_I2S3_SD);
	gpioA.setAsAltFunc(4, Gpio::PA4_I2S3_WS);

	I2s::config_t i2s3Config = 
	{
		I2s::MODE_MAIN_TX,	//mode_t mode;
		I2s::BIT_16BIT,		//dataBit_t dataBit;
		I2s::CHLEN_16BIT,	//chlen_t chlen;
		I2s::STD_PHILIPS,	//std_t std;
		48000,				//int32_t sampleRate;
		true				//bool mckoe;
	};

	i2s3.enableClock();
	i2s3.initialize(i2s3Config);
	i2s3.enableInterrupt();

	// Tone Generator 초기화
	gen.initialize();
}

void initializeSystem(void)
{
	// Power Controller 클럭 활성화
	clock.enableApb1Clock(RCC_APB1ENR_PWREN_Pos);

	// SYSCFG 클럭 활성화
	clock.enableApb2Clock(RCC_APB2ENR_SYSCFGEN_Pos);

	// 외부 크리스탈 클럭 활성화
#if defined(HSE_CLOCK_FREQ)
	clock.enableHse(HSE_CLOCK_FREQ);
#endif

	using namespace define::clock;
	
	clock.enableMainPll(
#if defined(HSE_CLOCK_FREQ)
		pll::src::HSE,				// uint8_t src
		HSE_CLOCK_FREQ / 1000000,	// uint8_t m
#else
		pll::src::HSI,				// uint8_t src
		16000000 / 1000000,			// uint8_t m
#endif
		288,						// uint16_t n
		pll::pdiv::DIV2,			// uint8_t pDiv Sysclk
		pll::qdiv::DIV6,			// uint8_t qDiv
		pll::rdiv::DIV7				// uint8_t rDiv	
	);

#if I2S1_ENABLE || I2S2_ENABLE || I2S3_ENABLE
#if defined(I2S_CKIN_CLOCK_FREQ)
	clock.setI2sCkinClockFrequency(I2S_CKIN_CLOCK_FREQ);
	clock.setI2sClockSource(Clock::I2S_SRC_EXT);
#else
	clock.enableI2sPll(
#if defined(HSE_CLOCK_FREQ)
		258,						// uint16_t n
		HSE_CLOCK_FREQ / 1000000,	// uint16_t m
#else
		258,						// uint16_t n
		16000000 / 1000000,			// uint16_t m
#endif
		pll::pdiv::DIV8,			// uint8_t pDiv
		pll::qdiv::DIV15,			// uint8_t qDiv
		pll::rdiv::DIV3				// uint8_t rDiv	
	);

	clock.setI2sClockSource(Clock::I2S_SRC_PLL);
#endif
#endif

	flash.setLatency(144000000, 33);

	clock.setSysclk(
		sysclk::src::PLL,			// uint8_t sysclkSrc;
		sysclk::ahbDiv::NO_DIV,		// uint8_t ahb;
		sysclk::apbDiv::DIV4,		// uint8_t apb1;
		sysclk::apbDiv::DIV2,		// uint8_t apb2;
		33							// uint8_t vcc
	);
	
	// Flash Prefetch, D/I 캐시 활성화
	flash.enableDataCache();
	flash.enableInstructionCache();
	flash.enablePrefetch();
	
	// GPIO 클럭 활성화
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOAEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOBEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOCEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIODEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOEEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOFEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOGEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOHEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOIEN_Pos);
}
