#include <dev/dev_led.h>
#include <yss/instance.h>

namespace Led
{
	void initialize(void)
	{
		gpioD.setAsOutput(12);
		gpioD.setAsOutput(13);
		gpioD.setAsOutput(14);
		gpioD.setAsOutput(15);

		setGreen(false);
		setOrange(false);
		setRed(false);
		setBlue(false);
	}

	void setGreen(bool en)
	{
		gpioD.setOutput(12, en);
	}

	void setOrange(bool en)
	{
		gpioD.setOutput(13, en);
	}

	void setRed(bool en)
	{
		gpioD.setOutput(14, en);
	}

	void setBlue(bool en)
	{
		gpioD.setOutput(15, en);
	}
};