/***************************************************************************
 *   Copyright (C) 2005 by Dominic Rath                                    *
 *   Dominic.Rath@gmx.de                                                   *
 *                                                                         *
 *   Copyright (C) 2007,2008 Øyvind Harboe                                 *
 *   oyvind.harboe@zylin.com                                               *
 *                                                                         *
 *   Copyright (C) 2009 SoftPLC Corporation                                *
 *       http://softplc.com                                                *
 *   dick@softplc.com                                                      *
 *                                                                         *
 *   Copyright (C) 2009 Zachary T Welch                                    *
 *   zw@superlucidity.net                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "interfaces.h"

/** @file
 * This file includes declarations for all built-in jtag interfaces,
 * which are then listed in the jtag_interfaces array.
 *
 * Dynamic loading can be implemented be searching for shared libraries
 * that contain a jtag_interface structure that can added to this list.
 */

#if BUILD_ZY1000 == 1
extern struct jtag_interface zy1000_interface;
#elif defined(BUILD_MINIDRIVER_DUMMY)
extern struct jtag_interface minidummy_interface;
#else // standard drivers
#if BUILD_PARPORT == 1
extern struct jtag_interface parport_interface;
#endif
#if BUILD_DUMMY == 1
extern struct jtag_interface dummy_interface;
#endif
#if BUILD_FT2232_FTD2XX == 1
extern struct jtag_interface ft2232_interface;
#endif
#if BUILD_FT2232_LIBFTDI == 1
extern struct jtag_interface ft2232_interface;
#endif
#if BUILD_USB_BLASTER_LIBFTDI == 1 || BUILD_USB_BLASTER_FTD2XX == 1
extern struct jtag_interface usb_blaster_interface;
#endif
#if BUILD_AMTJTAGACCEL == 1
extern struct jtag_interface amt_jtagaccel_interface;
#endif
#if BUILD_EP93XX == 1
extern struct jtag_interface ep93xx_interface;
#endif
#if BUILD_AT91RM9200 == 1
extern struct jtag_interface at91rm9200_interface;
#endif
#if BUILD_GW16012 == 1
extern struct jtag_interface gw16012_interface;
#endif
#if BUILD_PRESTO_LIBFTDI == 1 || BUILD_PRESTO_FTD2XX == 1
extern struct jtag_interface presto_interface;
#endif
#if BUILD_USBPROG == 1
extern struct jtag_interface usbprog_interface;
#endif
#if BUILD_JLINK == 1
extern struct jtag_interface jlink_interface;
#endif
#if BUILD_VSLLINK == 1
extern struct jtag_interface vsllink_interface;
#endif
#if BUILD_RLINK == 1
extern struct jtag_interface rlink_interface;
#endif
#if BUILD_ARMJTAGEW == 1
extern struct jtag_interface armjtagew_interface;
#endif
#endif // standard drivers

/**
 * The list of built-in JTAG interfaces, containing entries for those
 * drivers that were enabled by the @c configure script.
 *
 * The list should be defined to contain either one minidriver interface
 * or some number of standard driver interfaces, never both.
 */
struct jtag_interface *jtag_interfaces[] = {
#if BUILD_ZY1000 == 1
		&zy1000_interface,
#elif defined(BUILD_MINIDRIVER_DUMMY)
		&minidummy_interface,
#else // standard drivers
#if BUILD_PARPORT == 1
		&parport_interface,
#endif
#if BUILD_DUMMY == 1
		&dummy_interface,
#endif
#if BUILD_FT2232_FTD2XX == 1
		&ft2232_interface,
#endif
#if BUILD_FT2232_LIBFTDI == 1
		&ft2232_interface,
#endif
#if BUILD_USB_BLASTER_LIBFTDI == 1 || BUILD_USB_BLASTER_FTD2XX == 1
		&usb_blaster_interface,
#endif
#if BUILD_AMTJTAGACCEL == 1
		&amt_jtagaccel_interface,
#endif
#if BUILD_EP93XX == 1
		&ep93xx_interface,
#endif
#if BUILD_AT91RM9200 == 1
		&at91rm9200_interface,
#endif
#if BUILD_GW16012 == 1
		&gw16012_interface,
#endif
#if BUILD_PRESTO_LIBFTDI == 1 || BUILD_PRESTO_FTD2XX == 1
		&presto_interface,
#endif
#if BUILD_USBPROG == 1
		&usbprog_interface,
#endif
#if BUILD_JLINK == 1
		&jlink_interface,
#endif
#if BUILD_VSLLINK == 1
		&vsllink_interface,
#endif
#if BUILD_RLINK == 1
		&rlink_interface,
#endif
#if BUILD_ARMJTAGEW == 1
		&armjtagew_interface,
#endif
#endif // standard drivers
		NULL,
	};

void jtag_interface_modules_load(const char *path)
{
	// @todo: implement dynamic module loading for JTAG interface drivers
}
