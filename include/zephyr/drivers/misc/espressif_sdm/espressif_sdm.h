/*
 * Copyright (c) 2026 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for the Espressif sigma-delta modulator
 * @ingroup espressif_sdm_interface
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_MISC_ESPRESSIF_SDM_ESPRESSIF_SDM_H_
#define ZEPHYR_INCLUDE_DRIVERS_MISC_ESPRESSIF_SDM_ESPRESSIF_SDM_H_

#include <stdint.h>

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup espressif_sdm_interface Espressif SDM
 * @ingroup misc_interfaces
 * @since 4.5
 * @version 0.1.0
 * @{
 */

/**
 * @brief Set the pulse density of one SDM channel.
 *
 * The channel must be described by a child node of @p dev. Density zero
 * produces a PDM stream that is high about half of the time. Values toward
 * 127 spend more time high; values toward -128 spend more time low. The
 * output is closest to random noise between -90 and 90.
 *
 * @param dev SDM device instance.
 * @param channel Channel index. Must match the ``reg`` value of a child node.
 * @param density Pulse density, from -128 to 127.
 *
 * @retval 0 Density updated.
 * @retval -EINVAL @p channel is not described in the devicetree.
 */
int espressif_sdm_set_pulse_density(const struct device *dev, uint8_t channel, int8_t density);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_MISC_ESPRESSIF_SDM_ESPRESSIF_SDM_H_ */
