/* arch/arm/plat-samsung/include/plat/fb.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - FB platform data definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __PLAT_S3C_FB_H
#define __PLAT_S3C_FB_H __FILE__

#include <linux/s3c-fb.h>

/**
 * struct s3c_fb_pd_win - per window setup data
 * @win_mode: The display parameters to initialise (not for window 0)
 * @virtual_x: The virtual X size.
 * @virtual_y: The virtual Y size.
 * @width: The width of display in mm
 * @height: The height of display in mm
 */
struct s3c_fb_pd_win {
	struct fb_videomode	win_mode;
	unsigned short		default_bpp;
	unsigned short		max_bpp;
	unsigned short		virtual_x;
	unsigned short		virtual_y;
	unsigned short		width;
	unsigned short		height;
};

/**
 * struct s3c_fb_platdata -  S3C driver platform specific information
 * @setup_gpio: Setup the external GPIO pins to the right state to transfer
 *		the data from the display system to the connected display
 *		device.
 * @default_win: default window layer number to be used for UI layer.
 * @vidcon0: The base vidcon0 values to control the panel data format.
 * @vidcon1: The base vidcon1 values to control the panel data output.
 * @win: The setup data for each hardware window, or NULL for unused.
 * @display_mode: The LCD output display mode.
 *
 * The platform data supplies the video driver with all the information
 * it requires to work with the display(s) attached to the machine. It
 * controls the initial mode, the number of display windows (0 is always
 * the base framebuffer) that are initialised etc.
 *
 */
struct s3c_fb_platdata {
	void	(*setup_gpio)(void);
	void	(*backlight_off)(void);
	void	(*backlight_ctrl)(unsigned int enable);
	void	(*lcd_off)(void);
	void	(*dsim_hs_ctrl)(struct device *dsim, unsigned int enable);
	int             (*dsim_on)(struct device *dsim);
	int             (*dsim_off)(struct device *dsim);
	int             (*dsim_displayon)(struct device *dsim);

	struct s3c_fb_pd_win	*win[S3C_FB_MAX_WIN];

	u32			 default_win;
	u32			 vidcon0;
	u32			 vidcon1;
	int			 ip_version;
	struct device		 *dsim0_device;
	struct s5p_platform_mipi_dsim *dsim_pd;
	u32			 bootlogo;
	int			(*clock_init)(void);
};

/**
 * s3c_fb_set_platdata() - Setup the FB device with platform data.
 * @pd: The platform data to set. The data is copied from the passed structure
 *      so the machine data can mark the data __initdata so that any unused
 *      machines will end up dumping their data at runtime.
 */
extern void s3c_fb_set_platdata(struct s3c_fb_platdata *pd);

/**
 * s5p_fimd0_set_platdata() - Setup the FB device with platform data.
 * @pd: The platform data to set. The data is copied from the passed structure
 *      so the machine data can mark the data __initdata so that any unused
 *      machines will end up dumping their data at runtime.
 */
extern void s5p_fimd0_set_platdata(struct s3c_fb_platdata *pd);

/**
 * s5p_fimd1_set_platdata() - Setup the FB device with platform data.
 * @pd: The platform data to set. The data is copied from the passed structure
 *      so the machine data can mark the data __initdata so that any unused
 *      machines will end up dumping their data at runtime.
 */
extern void s5p_fimd1_set_platdata(struct s3c_fb_platdata *pd);

/**
 * s3c64xx_fb_gpio_setup_24bpp() - S3C64XX setup function for 24bpp LCD
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface.
 */
extern void s3c64xx_fb_gpio_setup_24bpp(void);

/**
 * s5pc100_fb_gpio_setup_24bpp() - S5PC100 setup function for 24bpp LCD
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface.
 */
extern void s5pc100_fb_gpio_setup_24bpp(void);

/**
 * s5pv210_fb_gpio_setup_24bpp() - S5PV210/S5PC110 setup function for 24bpp LCD
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface.
 */
extern void s5pv210_fb_gpio_setup_24bpp(void);

/**
 * exynos4_fimd0_gpio_setup_24bpp() - Exynos4 setup function for 24bpp LCD0
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface 0.
 */
extern void exynos4_fimd0_gpio_setup_24bpp(void);

/**
 * exynos5_fimd1_gpio_setup_24bpp() - Exynos5 setup function for 24bpp LCD0
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface 1.
 */
extern void exynos5_fimd1_gpio_setup_24bpp(void);

/**
 * s5p64x0_fb_gpio_setup_24bpp() - S5P6440/S5P6450 setup function for 24bpp LCD
 *
 * Initialise the GPIO for an 24bpp LCD display on the RGB interface.
 */
extern void s5p64x0_fb_gpio_setup_24bpp(void);

/**
 * exynos5_fimd1_setup_clock() = Exynos5 setup function for parent clock.
 * @dev: device pointer
 * @parent: parent clock used for LCD pixel clock
 * @clk_rate: clock rate for parent clock
 */
extern int __init exynos5_fimd1_setup_clock(struct device *dev, const char *bus_clk,
					const char *parent, unsigned long clk_rate);

/**
 * exynos4_fimd_setup_clock() = Exynos4 setup function for parent clock.
 * @dev: device pointer
 * @parent: parent clock used for LCD pixel clock
 * @clk_rate: clock rate for parent clock
 */
extern int __init exynos4_fimd_setup_clock(struct device *dev, const char *bus_clk,
					const char *parent, unsigned long clk_rate);

#endif /* __PLAT_S3C_FB_H */
