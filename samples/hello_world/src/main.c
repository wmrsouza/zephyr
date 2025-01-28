/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <inttypes.h>
#include <esp_attr.h>

/* __attribute__ ((section (".ext_ram.text"))) void hello_from_psram(void) */
EXT_RAM_NOINIT_ATTR void hello_from_psram(void)
{
	printf("hello_from_psram: 0x%"PRIX32"\n\r", (uint32_t)hello_from_psram);
	printf("Hello World (from PSRAM)! %s\n", CONFIG_BOARD_TARGET);
}

int main(void)
{
	hello_from_psram();

	return 0;
}
