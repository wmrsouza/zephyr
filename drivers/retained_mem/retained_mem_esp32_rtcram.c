/*
 * Copyright (c) 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT espressif_esp32_rtcram

#include <string.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/retained_mem.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(retained_mem_esp32_rtcram, CONFIG_RETAINED_MEM_LOG_LEVEL);

#ifdef CONFIG_RETAINED_MEM_MUTEXES
struct retained_mem_esp32_rtcram_data {
	struct k_mutex lock;
};
#endif

struct retained_mem_esp32_rtcram_config {
	uint8_t *addr;
	size_t size;
};

static inline void retained_mem_esp32_rtcram_lock_take(const struct device *dev)
{
#ifdef CONFIG_RETAINED_MEM_MUTEXES
	struct retained_mem_esp32_rtcram_data *data = dev->data;

	k_mutex_lock(&data->lock, K_FOREVER);
#else
	ARG_UNUSED(dev);
#endif
}

static inline void retained_mem_esp32_rtcram_lock_release(const struct device *dev)
{
#ifdef CONFIG_RETAINED_MEM_MUTEXES
	struct retained_mem_esp32_rtcram_data *data = dev->data;

	k_mutex_unlock(&data->lock);
#else
	ARG_UNUSED(dev);
#endif
}

static int retained_mem_esp32_rtcram_init(const struct device *dev)
{
#ifdef CONFIG_RETAINED_MEM_MUTEXES
	struct retained_mem_esp32_rtcram_data *data = dev->data;

	k_mutex_init(&data->lock);
#endif

	return 0;
}

static ssize_t retained_mem_esp32_rtcram_size(const struct device *dev)
{
	const struct retained_mem_esp32_rtcram_config *config = dev->config;

	return (ssize_t)config->size;
}

static int retained_mem_esp32_rtcram_read(const struct device *dev, off_t offset, uint8_t *buffer, size_t size)
{
	const struct retained_mem_esp32_rtcram_config *config = dev->config;

	retained_mem_esp32_rtcram_lock_take(dev);

	memcpy(buffer, (config->addr + offset), size);

	retained_mem_esp32_rtcram_lock_release(dev);

	return 0;
}

static int retained_mem_esp32_rtcram_write(const struct device *dev, off_t offset, const uint8_t *buffer,
			      size_t size)
{
	const struct retained_mem_esp32_rtcram_config *config = dev->config;

	retained_mem_esp32_rtcram_lock_take(dev);

	memcpy((config->addr + offset), buffer, size);

	retained_mem_esp32_rtcram_lock_release(dev);

	return 0;
}

static int retained_mem_esp32_rtcram_clear(const struct device *dev)
{
	const struct retained_mem_esp32_rtcram_config *config = dev->config;

	retained_mem_esp32_rtcram_lock_take(dev);

	memset(config->addr, 0, config->size);

	retained_mem_esp32_rtcram_lock_release(dev);

	return 0;
}

static DEVICE_API(retained_mem, retained_mem_esp32_rtcram_api) = {
	.size = retained_mem_esp32_rtcram_size,
	.read = retained_mem_esp32_rtcram_read,
	.write = retained_mem_esp32_rtcram_write,
	.clear = retained_mem_esp32_rtcram_clear,
};

#define RETAINED_MEM_ESP32_RTCRAM_DEVICE(inst)						\
	IF_ENABLED(CONFIG_RETAINED_MEM_MUTEXES,					\
		   (static struct retained_mem_esp32_rtcram_data retained_mem_esp32_rtcram_data_##inst;)	\
	)									\
	static const struct retained_mem_esp32_rtcram_config retained_mem_esp32_rtcram_config_##inst = {	\
		.addr = (uint8_t *)DT_INST_REG_ADDR(inst),			\
		.size = DT_INST_REG_SIZE(inst),					\
	};									\
	DEVICE_DT_INST_DEFINE(inst,						\
			      &retained_mem_esp32_rtcram_init,				\
			      NULL,						\
			      COND_CODE_1(CONFIG_RETAINED_MEM_MUTEXES,		\
					  (&retained_mem_esp32_rtcram_data_##inst), (NULL)	\
			      ),						\
			      &retained_mem_esp32_rtcram_config_##inst,			\
			      POST_KERNEL,					\
			      CONFIG_RETAINED_MEM_INIT_PRIORITY,		\
			      &retained_mem_esp32_rtcram_api);

DT_INST_FOREACH_STATUS_OKAY(RETAINED_MEM_ESP32_RTCRAM_DEVICE)
