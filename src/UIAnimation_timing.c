#include "UIAnimation.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

UIFloat UIAnimationTimingFunctionLinear(UIFloat p)
{
	return p;
}

UIFloat UIAnimationTimingFunctionEaseInQuad(UIFloat p)
{
	return p * p;
}

UIFloat UIAnimationTimingFunctionEaseOutQuad(UIFloat p)
{
	return -(p * (p - 2));
}

UIFloat UIAnimationTimingFunctionEaseInOutQuad(UIFloat p)
{
	if (p < 0.5)
	{
		return 2 * p * p;
	}
	else
	{
		return (-2 * p * p) + (4 * p) - 1;
	}
}

UIFloat UIAnimationTimingFunctionEaseInCubic(UIFloat p)
{
	return p * p * p;
}

UIFloat UIAnimationTimingFunctionEaseOutCubic(UIFloat p)
{
	UIFloat f = (p - 1);
	return f * f * f + 1;
}

UIFloat UIAnimationTimingFunctionEaseInOutCubic(UIFloat p)
{
	if (p < 0.5)
	{
		return 4 * p * p * p;
	}
	else
	{
		UIFloat f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

UIFloat UIAnimationTimingFunctionEaseInQuart(UIFloat p)
{
	return p * p * p * p;
}

UIFloat UIAnimationTimingFunctionEaseOutQuart(UIFloat p)
{
	UIFloat f = (p - 1);
	return f * f * f * (1 - p) + 1;
}

UIFloat UIAnimationTimingFunctionEaseInOutQuart(UIFloat p)
{
	if (p < 0.5)
	{
		return 8 * p * p * p * p;
	}
	else
	{
		UIFloat f = (p - 1);
		return -8 * f * f * f * f + 1;
	}
}

UIFloat UIAnimationTimingFunctionEaseInQuint(UIFloat p)
{
	return p * p * p * p * p;
}

UIFloat UIAnimationTimingFunctionEaseOutQuint(UIFloat p)
{
	UIFloat f = (p - 1);
	return f * f * f * f * f + 1;
}

UIFloat UIAnimationTimingFunctionEaseInOutQuint(UIFloat p)
{
	if (p < 0.5)
	{
		return 16 * p * p * p * p * p;
	}
	else
	{
		UIFloat f = ((2 * p) - 2);
		return 0.5 * f * f * f * f * f + 1;
	}
}

UIFloat UIAnimationTimingFunctionEaseInSine(UIFloat p)
{
	return sin((p - 1) * M_PI_2) + 1;
}

UIFloat UIAnimationTimingFunctionEaseOutSine(UIFloat p)
{
	return sin(p * M_PI_2);
}

UIFloat UIAnimationTimingFunctionEaseInOutSine(UIFloat p)
{
	return 0.5 * (1 - cos(p * M_PI));
}

UIFloat UIAnimationTimingFunctionEaseInCirc(UIFloat p)
{
	return 1 - sqrt(1 - (p * p));
}

UIFloat UIAnimationTimingFunctionEaseOutCirc(UIFloat p)
{
	return sqrt((2 - p) * p);
}

UIFloat UIAnimationTimingFunctionEaseInOutCirc(UIFloat p)
{
	if (p < 0.5)
	{
		return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
	}
	else
	{
		return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
	}
}

UIFloat UIAnimationTimingFunctionEaseInExpo(UIFloat p)
{
	return (p == 0.0) ? p : pow(2, 10 * (p - 1));
}

UIFloat UIAnimationTimingFunctionEaseOutExpo(UIFloat p)
{
	return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

UIFloat UIAnimationTimingFunctionEaseInOutExpo(UIFloat p)
{
	if (p == 0.0 || p == 1.0)
		return p;

	if (p < 0.5)
	{
		return 0.5 * pow(2, (20 * p) - 10);
	}
	else
	{
		return -0.5 * pow(2, (-20 * p) + 10) + 1;
	}
}

UIFloat UIAnimationTimingFunctionEaseInElastic(UIFloat p)
{
	return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
}

UIFloat UIAnimationTimingFunctionEaseOutElastic(UIFloat p)
{
	return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
}

UIFloat UIAnimationTimingFunctionEaseInOutElastic(UIFloat p)
{
	if (p < 0.5)
	{
		return 0.5 * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
	}
	else
	{
		return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
	}
}

UIFloat UIAnimationTimingFunctionEaseInBack(UIFloat p)
{
	return p * p * p - p * sin(p * M_PI);
}

UIFloat UIAnimationTimingFunctionEaseOutBack(UIFloat p)
{
	UIFloat f = (1 - p);
	return 1 - (f * f * f - f * sin(f * M_PI));
}

UIFloat UIAnimationTimingFunctionEaseInOutBack(UIFloat p)
{
	if (p < 0.5)
	{
		UIFloat f = 2 * p;
		return 0.5 * (f * f * f - f * sin(f * M_PI));
	}
	else
	{
		UIFloat f = (1 - (2 * p - 1));
		return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
	}
}

UIFloat UIAnimationTimingFunctionEaseInBounce(UIFloat p)
{
	return 1 - UIAnimationTimingFunctionEaseOutBounce(1 - p);
}

UIFloat UIAnimationTimingFunctionEaseOutBounce(UIFloat p)
{
	if (p < 4 / 11.0)
	{
		return (121 * p * p) / 16.0;
	}
	else if (p < 8 / 11.0)
	{
		return (363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0;
	}
	else if (p < 9 / 10.0)
	{
		return (4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0;
	}
	else
	{
		return (54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0;
	}
}

UIFloat UIAnimationTimingFunctionEaseInOutBounce(UIFloat p)
{
	if (p < 0.5)
	{
		return 0.5 * UIAnimationTimingFunctionEaseInBounce(p * 2);
	}
	else
	{
		return 0.5 * UIAnimationTimingFunctionEaseOutBounce(p * 2 - 1) + 0.5;
	}
}
