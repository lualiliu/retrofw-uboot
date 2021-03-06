/*
 * (C) Copyright 2008  Ingenic Semiconductor
 *
 *  Author: <cwjia@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file contains the configuration parameters for the fuwa board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MIPS32		1  /* MIPS32 CPU core */
#define CONFIG_JzRISC		1  /* JzRISC core */
#define CONFIG_JZSOC		1  /* Jz SoC */
#define CONFIG_JZ4770		1  /* Jz4770 SoC */
#define CONFIG_F4770		1  /* f4770 validation board */
#define CONFIG_DDRC		1  /* use ddr controller */
#define CONFIG_DDR2_DIFFERENTIAL	1	/* differential DQS */

#ifdef CONFIG_MSC_U_BOOT
#define CONFIG_MSC_TYPE_SD
#endif

//#define CONFIG_SDRAM_MDDR
/* memory group */
// [MAY CHANGE] RAM
#ifdef CONFIG_SDRAM_MDDR
#include "asm/jz_mem_nand_configs/MDDR_H5MS5122DFR-J3M.h"
#elif defined CONFIG_SDRAM_DDR1
#include "asm/jz_mem_nand_configs/DDR1_H5DU516ETR-E3C.h"
#elif defined CONFIG_SDRAM_DDR2
//#include "asm/jz_mem_nand_configs/DDR2_V59C1G02168QB-3.h"
//#include "asm/jz_mem_nand_configs/DDR2_H5PS1G63EFR-G7C.h"
//#include "asm/jz_mem_nand_configs/DDR2_MT47H128M16RT-25E.h"
#include "asm/jz_mem_nand_configs/DDR2_W972GG6KB-25I.h"
//#include "asm/jz_mem_nand_configs/DDR2_H5PS1G63EFR-Y5C.h"
#elif defined CONFIG_MOBILE_SDRAM
#include "asm/jz_mem_nand_configs/MSDRAM_H55S5122DFR.h"
#else
#include "asm/jz_mem_nand_configs/SDRAM_.h"
#endif
// [MAY CHANGE] NAND
//#include "asm/jz_mem_nand_configs/NAND_K9GAG08U0M.h"
#include "asm/jz_mem_nand_configs/NAND_K9GAG08U0D.h"


#define JZ4760_NORBOOT_CFG	JZ4760_NORBOOT_8BIT	/* NOR Boot config code */

#define CFG_EXTAL		12000000	/* EXTAL freq: 12MHz */
#define CFG_CPU_SPEED		(1008 * 1000000)	/* CPU clock */
#define	CFG_HZ			(CFG_EXTAL / 256) /* incrementer freq */


/* this must be included AFTER CFG_EXTAL and CFG_CPU_SPEED */
#define CFG_UART_BASE  		UART2_BASE	/* Base of the UART channel */
#define CONFIG_BAUDRATE		57600
#define CFG_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200}

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_COMMANDS		(CONFIG_CMD_DFL | \
				 CFG_CMD_ASKENV | \
				 CFG_CMD_NAND   | \
				 CFG_CMD_MSC    | \
				 CFG_CMD_DHCP	| \
				 CFG_CMD_PING)
#define CONFIG_BOOTP_MASK	( CONFIG_BOOTP_DEFAUL )

/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
#include "jz4770_common.h"
#include <cmd_confdefs.h>

// [MAY CHANGE] Boot Arguments
#define CONFIG_BOOTDELAY	0
#define CONFIG_BOOTFILE	        "uImage"	/* file to load */
#if defined(CONFIG_SDRAM_MDDR)
#define CONFIG_BOOTARGS		"mem=64M console=ttyS2,57600n8 ip=off root=/dev/mtdblock2 rw"
#else
#define CONFIG_BOOTARGS		"mem=256M console=ttyS2,57600n8 ip=off rootfstype=ext3 root=/dev/mmcblk0p1 ro panic=5" 
#endif
#define CONFIG_BOOTCOMMAND	"msc  read 0x80600000 0x400000 0x300000;bootm"
#define CFG_AUTOLOAD		"n"		/* No autoload */

#define CONFIG_NET_MULTI
#define CONFIG_ETHADDR		00:2a:c6:2c:bd:fc    /* Ethernet address */

/*
 * Serial download configuration
 *
 */
#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#define CFG_LOADS_BAUD_CHANGE	1	/* allow baudrate change	*/

/*
 * Miscellaneous configurable options
 */
#define	CFG_LONGHELP				/* undef to save memory      */
#define	CFG_PROMPT		"F4770 # "	/* Monitor Command Prompt    */
#define	CFG_CBSIZE		256		/* Console I/O Buffer Size   */
#define	CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)  /* Print Buffer Size */
#define	CFG_MAXARGS		16		/* max number of command args*/

#define CFG_MALLOC_LEN		896*1024
#define CFG_BOOTPARAMS_LEN	128*1024

#define CFG_SDRAM_BASE		0x80000000     /* Cached addr */

#define CFG_INIT_SP_OFFSET	0x400000

#define	CFG_LOAD_ADDR		0x80600000     /* default load address	*/

#define CFG_MEMTEST_START	0x80100000
#define CFG_MEMTEST_END		0x80800000

#define CFG_RX_ETH_BUFFER	16	/* use 16 rx buffers on jz47xx eth */

/*
 * Configurable options for zImage if SPL is to load zImage instead of u-boot.
 */
#define CONFIG_LOAD_UBOOT       /* If it's defined, then spl load u-boot instead of zImage, and following options isn't used */
#define PARAM_BASE		0x80004000      /* The base of parameters which will be sent to kernel zImage */
#define CFG_ZIMAGE_SIZE	        (2 << 20)	/* Size of kernel zImage */
#define CFG_ZIMAGE_DST	        0x80100000	/* Load kernel zImage to this addr */
#define CFG_ZIMAGE_START	CFG_ZIMAGE_DST	/* Start kernel zImage from this addr	*/
#define CFG_CMDLINE		CONFIG_BOOTARGS
#define CFG_NAND_ZIMAGE_OFFS	(CFG_NAND_BLOCK_SIZE*4) /* NAND offset of zImage being loaded */
#define CFG_SPI_ZIMAGE_OFFS	(256 << 10) /* NAND offset of zImage being loaded */

/*-----------------------------------------------------------------------
 * Environment
 *----------------------------------------------------------------------*/
#if !defined(CONFIG_NAND_U_BOOT) && !defined(CONFIG_NAND_SPL) && !defined(CONFIG_MSC_U_BOOT) && !defined(CONFIG_MSC_SPL)
#define CFG_ENV_IS_IN_FLASH     1	/* use FLASH for environment vars	*/
#elif defined(CONFIG_MSC_U_BOOT)
#define CFG_ENV_IS_IN_MSC      1	/* use MSC  for environment vars	*/
#else
#define CFG_ENV_IS_IN_NAND	1	/* use NAND for environment vars	*/
#endif

#define CFG_NAND_BCH_BIT        8               /* Specify the hardware BCH algorithm for 4770 (4|8) */
#define CFG_NAND_ECC_POS        24               /* Ecc offset position in oob area, its default value is 3 if it isn't defined. */
#define CFG_NAND_SMCR1          0x1aaaaa00      /* 0x0fff7700 is slowest */
#define CFG_NAND_USE_PN         0               /* Use PN in jz4770 for TLC NAND */
#define CFG_NAND_BACKUP_NUM     1               /* TODO */

#define CFG_MAX_NAND_DEVICE     1
#define NAND_MAX_CHIPS          1
#define CFG_NAND_BASE           0xBA000000
#define NAND_ADDR_OFFSET        0x00800000
#define NAND_CMD_OFFSET         0x00400000
#define CFG_NAND_SELECT_DEVICE  1       /* nand driver supports mutipl. chips   */

/*
 * IPL (Initial Program Loader, integrated inside CPU)
 * Will load first 8k from NAND (SPL) into cache and execute it from there.
 *
 * SPL (Secondary Program Loader)
 * Will load special U-Boot version (NUB) from NAND and execute it. This SPL
 * has to fit into 8kByte. It sets up the CPU and configures the SDRAM
 * controller and the NAND controller so that the special U-Boot image can be
 * loaded from NAND to SDRAM.
 *
 * NUB (NAND U-Boot)
 * This NAND U-Boot (NUB) is a special U-Boot version which can be started
 * from RAM. Therefore it mustn't (re-)configure the SDRAM controller.
 *
 */
#define CFG_NAND_U_BOOT_DST	0xa0100000	/* Load NUB to this addr	*/
#define CFG_NAND_U_BOOT_START	0x80100000 //CFG_NAND_U_BOOT_DST /* Start NUB from this addr	*/

/*
 * Define the partitioning of the NAND chip (only RAM U-Boot is needed here)
 */
#define CFG_NAND_U_BOOT_OFFS	(CFG_NAND_BLOCK_SIZE * (CFG_NAND_BACKUP_NUM+1))	/* Offset to U-Boot image */

/* Size of U-Boot image */
#if CFG_NAND_BLOCK_SIZE > (512 << 10)
#define CFG_NAND_U_BOOT_SIZE    CFG_NAND_BLOCK_SIZE
#else
#define CFG_NAND_U_BOOT_SIZE	(512 << 10)
#endif

#ifdef CFG_ENV_IS_IN_NAND
#define CFG_ENV_SIZE		0x10000
#define CFG_ENV_OFFSET		(CFG_NAND_U_BOOT_OFFS + CFG_NAND_U_BOOT_SIZE)	/* environment starts here  */
#define CFG_ENV_OFFSET_REDUND	(CFG_ENV_OFFSET + CFG_NAND_BLOCK_SIZE)
#endif

/*
 * IPL (Initial Program Loader, integrated inside CPU)
 * Will load first 8k from MSC (SPL) into cache and execute it from there.
 *
 * SPL (Secondary Program Loader)
 * Will load special U-Boot version (MSUB) from MSC and execute it. This SPL
 * has to fit into 8kByte. It sets up the CPU and configures the SDRAM
 * controller and the MSC controller so that the special U-Boot image can be
 * loaded from MSC to SDRAM.
 *
 * MSUB (MMC/SD U-Boot)
 * This MSC U-Boot (MSUB) is a special U-Boot version which can be started
 * from RAM. Therefore it mustn't (re-)configure the SDRAM controller.
 *
 */
#define CFG_MSC_U_BOOT_DST	0x80100000	/* Load MSUB to this addr	 */
#define CFG_MSC_U_BOOT_START	CFG_MSC_U_BOOT_DST /* Start MSUB from this addr */

/*
 * Define the partitioning of the MMC/SD card (only RAM U-Boot is needed here)
 */
#define CFG_MSC_U_BOOT_OFFS	(16 << 10)	/* Offset to RAM U-Boot image	*/
#define CFG_MSC_U_BOOT_SIZE	(256 << 10)	/* Size of RAM U-Boot image	*/

#define CFG_MSC_BLOCK_SIZE	512

#ifdef CFG_ENV_IS_IN_MSC
#define CFG_ENV_SIZE		CFG_MSC_BLOCK_SIZE
#define CFG_ENV_OFFSET		((CFG_MSC_BLOCK_SIZE * 16) + CFG_MSC_U_BOOT_SIZE + (CFG_MSC_BLOCK_SIZE * 16))	/* environment starts here  */
#endif

/*======== Partition size ============ */
#define PTN_UBOOT_SIZE				(3* 0x100000)	/*include MBR(512bytes) before u-boot*/
#define PTN_MISC_SIZE               (1* 0x100000)
#define PTN_KERNEL_SIZE             (4* 0x100000)
#define PTN_RECOVERY_SIZE           (4* 0x100000)
#define PTN_SYSTEM_SIZE             (200* 0x100000)
#define PTN_USERDATA_SIZE           (256* 0x100000)
#define PTN_CACHE_SIZE              (32* 0x100000)	/* optional */
/*======== Partition offset ============ */
#define PTN_UBOOT_OFFSET			(0)		/* 0 is MBR offset,MBR in combination with UBOOT */
#define PTN_MISC_OFFSET             (PTN_UBOOT_OFFSET+ PTN_UBOOT_SIZE)
#define PTN_KERNEL_OFFSET           (PTN_MISC_OFFSET + PTN_MISC_SIZE)
#define PTN_RECOVERY_OFFSET       	(PTN_KERNEL_OFFSET + PTN_KERNEL_SIZE)
#define PTN_SYSTEM_OFFSET         	(PTN_RECOVERY_OFFSET+PTN_RECOVERY_SIZE)
#define PTN_USERDATA_OFFSET			(PTN_SYSTEM_OFFSET+PTN_SYSTEM_SIZE)  
#define PTN_CACHE_OFFSET			(PTN_USERDATA_OFFSET +PTN_USERDATA_SIZE)  /* optional */

/*-----------------------------------------------------------------------
 * MBR Partition info
 */
#define JZ_MBR_TABLE		/* configure the MBR below if JZ_MBR_TABLE defined*/
#define LINUX_FS_TYPE	0x83
#define VFAT_FS_TYPE	0x0B
/*======== Partition table ============ */
#define MBR_P1_OFFSET 	PTN_SYSTEM_OFFSET
#define MBR_P1_SIZE 	PTN_SYSTEM_SIZE
#define MBR_P1_TYPE 	LINUX_FS_TYPE

#define MBR_P2_OFFSET 	PTN_CACHE_OFFSET
#define MBR_P2_SIZE 	PTN_CACHE_SIZE
#define MBR_P2_TYPE 	LINUX_FS_TYPE

#define MBR_P3_OFFSET 	0x3a400000
#define MBR_P3_SIZE 	0x2000000
#define MBR_P3_TYPE 	LINUX_FS_TYPE

#define MBR_P4_OFFSET 	0x40000000
#define MBR_P4_SIZE 	0xa8c00000
#define MBR_P4_TYPE 	VFAT_FS_TYPE

/*-----------------------------------------------------------------------
 * SPI NOR FLASH configuration
 */
#define CFG_SPI_MAX_FREQ        1000000
#define CFG_SPI_U_BOOT_DST	0x80100000	/* Load NUB to this addr	*/
#define CFG_SPI_U_BOOT_START	CFG_SPI_U_BOOT_DST
#define CFG_SPI_U_BOOT_OFFS     (8 << 10)
#define CFG_SPI_U_BOOT_SIZE	(256 << 10)

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CFG_MAX_FLASH_SECT	(128)	/* max number of sectors on one chip */

#define PHYS_FLASH_1		0xB8000000 /* Flash Bank #1 */

/* The following #defines are needed to get flash environment right */
#define	CFG_MONITOR_BASE	TEXT_BASE
#define	CFG_MONITOR_LEN		(256*1024)  /* Reserve 256 kB for Monitor */

#define CFG_FLASH_BASE		PHYS_FLASH_1
/* Environment settings */
#ifdef CFG_ENV_IS_IN_FLASH

#define CFG_ENV_SECT_SIZE	0x20000 /* Total Size of Environment Sector */
#define CFG_ENV_SIZE		CFG_ENV_SECT_SIZE
#endif
#define CFG_ENV_ADDR		0xB8040000

#define CFG_DIRECT_FLASH_TFTP	1	/* allow direct tftp to flash */

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		16384
#define CFG_ICACHE_SIZE		16384
#define CFG_CACHELINE_SIZE	32

/*======================================================================
 * GPIO
 */
#define GPIO_LCD_PWM   		(32*4+1) /* GPE1 PWM1 */

#endif
