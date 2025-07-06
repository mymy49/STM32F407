/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef DEV_LED__H_
#define DEV_LED__H_

namespace Led
{
	/*
		LED를 초기화합니다.
	*/
	void initialize(void);

	/*
		녹색 LED를 제어합니다.
		.
		@ en : true 설정시 LED를 켭니다.
	*/
	void setGreen(bool en);

	/*
		 주황색 LED를 제어합니다.
		.
		@ en : true 설정시 LED를 켭니다.
	*/
	void setOrange(bool en);

	/*
		적색 LED를 제어합니다.
		.
		@ en : true 설정시 LED를 켭니다.
	*/
	void setRed(bool en);

	/*
		파란색 LED를 제어합니다.
		.
		@ en : true 설정시 LED를 켭니다.
	*/
	void setBlue(bool en);
};

#endif

