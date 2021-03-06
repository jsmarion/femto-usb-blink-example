/**
 * \file
 *
 * \brief Unit tests for HMATRIX driver.
 *
 * Copyright (c) 2012 - 2014 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the HMATRIX driver.
 * It contains one test case for the HMATRIX module:
 * - Test running speed between two matrix configurations.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.atmel.com/">Atmel</a>.\n
 * Support and FAQ: http://www.atmel.com/design-support/
 */

/* Global g_ul_ms_ticks in milliseconds since start of application */
volatile uint32_t g_ul_ms_ticks = 0;

/**
 * \brief Handler for System Tick interrupt.
 *
 * Process System Tick Event.
 * Increment the g_ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ul_ms_ticks++;
}

/**
 * \brief Toggle led at the given time.
 *
 * \param ul_dly_ticks  Delay to wait for, in milliseconds.
 *
 * \return Led toggle times.
 */
static uint32_t toggle_led_test(uint32_t ul_dly_ticks)
{
	uint32_t ul_cnt = 0;
	uint32_t ul_cur_ticks;

	ul_cur_ticks = g_ul_ms_ticks;
	do {
		ul_cnt++;
		LED_Toggle(LED0);
	} while ((g_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);

	return ul_cnt;
}

/**
 * \brief Test running speed between different master configurations.
 *
 * \param test Current test case.
 */
static void run_hmatrix_test_master(const struct test_case *test)
{
	enum hmatrix_master_id ul_master_id;
	enum hmatrix_slave_id ul_slave_id;
	uint32_t ul_cnt1, ul_cnt2;
	struct hmatrix_master_ch_conf master_config;
	struct hmatrix_slave_ch_conf slave_config;

	/* Enable the HMATRIX access. */
	hmatrix_enable();
	hmatrix_master_ch_get_config_defaults(&master_config);
	hmatrix_slave_ch_get_config_defaults(&slave_config);

	/* Config all slave with default setting */
	for (ul_slave_id = HMATRIX_SLAVE_ID_FLASH;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}

	/* Compare 1: First, test with single access master */
	master_config.burst_type = HMATRIX_BURST_SINGLE_ACCESS;
	for (ul_master_id = HMATRIX_MASTER_ID_CPU_IDCORE;
			ul_master_id < HMATRIX_MASTER_ID_NUM; ul_master_id++) {
		hmatrix_master_ch_set_config(ul_master_id, &master_config);
	}
	ul_cnt1 = toggle_led_test(1000);

	/* Compare 1: Second, test with 16 beat burst access master */
	master_config.burst_type = HMATRIX_BURST_SIXTEEN_BEAT;
	for (ul_master_id = HMATRIX_MASTER_ID_CPU_IDCORE;
			ul_master_id < HMATRIX_MASTER_ID_NUM; ul_master_id++) {
		hmatrix_master_ch_set_config(ul_master_id, &master_config);
	}
	ul_cnt2 = toggle_led_test(1000);

	test_assert_true(test, (ul_cnt1 < ul_cnt2), "running speed test failed!");

	/* Disable the HMATRIX access. */
	hmatrix_disable();
}

/**
 * \brief Test running speed between different slave configurations.
 *
 * \param test Current test case.
 */
static void run_hmatrix_test_slave(const struct test_case *test)
{
	enum hmatrix_master_id ul_master_id;
	enum hmatrix_slave_id ul_slave_id;
	uint32_t ul_cnt1, ul_cnt2, ul_cnt3;
	struct hmatrix_master_ch_conf master_config;
	struct hmatrix_slave_ch_conf slave_config;

	/* Enable the HMATRIX access. */
	hmatrix_enable();
	hmatrix_master_ch_get_config_defaults(&master_config);
	hmatrix_slave_ch_get_config_defaults(&slave_config);

	/* Config all master with default setting */
	for (ul_master_id = HMATRIX_MASTER_ID_CPU_IDCORE;
			ul_master_id < HMATRIX_MASTER_ID_NUM; ul_master_id++) {
		hmatrix_master_ch_set_config(ul_master_id, &master_config);
	}

	/* First, test with Round-Robin arbitration without default master */
	slave_config.def_master_type = HMATRIX_DEFAULT_MASTER_NONE;
	for (ul_slave_id = HMATRIX_SLAVE_ID_FLASH;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}
	ul_cnt1 = toggle_led_test(1000);

	/* Compare 1: test with Round-Robin arbitration with last access master */
	slave_config.def_master_type = HMATRIX_DEFAULT_MASTER_PREVIOUS;
	for (ul_slave_id = HMATRIX_SLAVE_ID_FLASH;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}
	ul_cnt2 = toggle_led_test(1000);

	test_assert_true(test, (ul_cnt1 < ul_cnt2), "running speed test failed!");

	/* Compare 2: test with Round-Robin arbitration with fixed master */
	slave_config.def_master_type = HMATRIX_DEFAULT_MASTER_FIXED;
	slave_config.fixed_def_master_number = HMATRIX_MASTER_ID_CPU_IDCORE;
	hmatrix_slave_ch_set_config(HMATRIX_SLAVE_ID_FLASH, &slave_config);
	slave_config.fixed_def_master_number = HMATRIX_MASTER_ID_CPU_SYS;
	for (ul_slave_id = HMATRIX_SLAVE_ID_PBA;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}
	ul_cnt3 = toggle_led_test(1000);

	test_assert_true(test, (ul_cnt1 < ul_cnt3), "running speed test failed!");

	/* Disable the HMATRIX access. */
	hmatrix_disable();
}

/**
 * \brief Test running speed between different arbitration configurations.
 *
 * \param test Current test case.
 */
static void run_hmatrix_test_arbitration(const struct test_case *test)
{
	enum hmatrix_master_id ul_master_id;
	enum hmatrix_slave_id ul_slave_id;
	uint32_t ul_cnt1, ul_cnt2;
	struct hmatrix_master_ch_conf master_config;
	struct hmatrix_slave_ch_conf slave_config;
	hmatrix_prs priority_setting;

	/* Enable the HMATRIX access. */
	hmatrix_enable();
	hmatrix_master_ch_get_config_defaults(&master_config);
	hmatrix_slave_ch_get_config_defaults(&slave_config);

	/* Config all master with default setting */
	for (ul_master_id = HMATRIX_MASTER_ID_CPU_IDCORE;
				ul_master_id < HMATRIX_MASTER_ID_NUM; ul_master_id++) {
			hmatrix_master_ch_set_config(ul_master_id, &master_config);
		}

	/* Compare 1: First, test with Round-Robin arbitration */
	for (ul_slave_id = HMATRIX_SLAVE_ID_FLASH;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}
	ul_cnt1 = toggle_led_test(1000);

	/* Compare 1: Second, test with fixed arbitration */
	slave_config.arbitration_type = HMATRIX_ARBITRATION_FIXED_PRIORITY;
	priority_setting.HMATRIXB_PRAS = 0x03;
	priority_setting.HMATRIXB_PRBS = 0x00;
	hmatrix_set_slave_priority(HMATRIX_SLAVE_ID_FLASH, &priority_setting);
	hmatrix_slave_ch_set_config(HMATRIX_SLAVE_ID_FLASH, &slave_config);
	priority_setting.HMATRIXB_PRAS = 0x30;
	priority_setting.HMATRIXB_PRBS = 0x00;
	for (ul_slave_id = HMATRIX_SLAVE_ID_PBA;
			ul_slave_id < HMATRIX_SLAVE_ID_NUM; ul_slave_id++) {
		hmatrix_set_slave_priority(ul_slave_id, &priority_setting);
		hmatrix_slave_ch_set_config(ul_slave_id, &slave_config);
	}
	ul_cnt2 = toggle_led_test(1000);

	test_assert_true(test, (ul_cnt1 < ul_cnt2), "running speed test failed!");

	/* Disable the HMATRIX access. */
	hmatrix_disable();
}

/**
 * \brief Run HMATRIX driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Configure systick for 1 ms */
	SysTick_Config(sysclk_get_cpu_hz() / 1000);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(hmatrix_master_test, NULL, run_hmatrix_test_master, NULL,
			"Running speed test with different master configuration.");
	DEFINE_TEST_CASE(hmatrix_slave_test, NULL, run_hmatrix_test_slave, NULL,
			"Running speed test with different slave configuration.");
	DEFINE_TEST_CASE(hmatrix_arbitration_test, NULL,
			run_hmatrix_test_arbitration, NULL,
			"Running speed test with different arbitration configuration.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(hmatrix_tests) = {
		&hmatrix_master_test,
		&hmatrix_slave_test,
		&hmatrix_arbitration_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(hmatrix_suite, hmatrix_tests,
			"SAM HMATRIX driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&hmatrix_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
