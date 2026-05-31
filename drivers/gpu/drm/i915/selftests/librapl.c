// SPDX-License-Identifier: MIT
/*
 * Copyright © 2020 Intel Corporation
 */

#include <asm/msr.h>

#include "librapl.h"

u64 librapl_energy_uJ(void)
{
	unsigned long long power;
	u32 units;

	if (rdmsrq_safe(MSR_RAPL_POWER_UNIT, &power))
		return 0;

	units = (power & 0x1f00) >> 8;

	if (rdmsrq_safe(MSR_PP1_ENERGY_STATUS, &power))
		return 0;

	return (1000000 * power) >> units; /* convert to uJ */
}
