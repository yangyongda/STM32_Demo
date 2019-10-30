/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "sdio_sdcard.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

//¶ÁÈ¡×´Ì¬
DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	SD_Error status;
	if(drv)
	{
		return STA_NOINIT;
	}
	//SD³õÊ¼»¯
	status = SD_Init();
	if(status!=SD_OK)
	{
		return STA_NOINIT;
	}
	else
	{
		return RES_OK;
	}
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	if(count>1)	
	{
		SD_ReadMultiBlocks(buff,sector*BLOCK_SIZE,BLOCK_SIZE,count);  
		SD_WaitReadOperation();	 

		while(SD_GetStatus() != SD_TRANSFER_OK);
	}
	else  
	{
		SD_ReadBlock(buff,sector*BLOCK_SIZE,BLOCK_SIZE);
		SD_WaitReadOperation();	 
		
		while(SD_GetStatus() != SD_TRANSFER_OK);
	}
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	if(count>1)	
	{
		SD_WriteMultiBlocks((uint8_t *)buff, sector*BLOCK_SIZE, BLOCK_SIZE, count);
		SD_WaitWriteOperation(); 
		while(SD_GetStatus() != SD_TRANSFER_OK);  
	}
	else  
	{
		SD_WriteBlock((uint8_t *) buff, sector*BLOCK_SIZE, BLOCK_SIZE);
		SD_WaitWriteOperation(); 
		while(SD_GetStatus() != SD_TRANSFER_OK);  
	}
	return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}


DWORD get_fattime(void)
{
	return 0; 
}

