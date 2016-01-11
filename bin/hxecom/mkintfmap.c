/* @(#)17	1.2  src/htx/usr/lpp/htx/bin/hxecom/mkintfmap.c, exer_com, htxubuntu 1/6/09 06:50:27 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <linux/version.h>
#include <asm/ioctl.h>

#define _DEBUG_MKMAP_ 0

#define PDIAGEX_IOCTL   0x01

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#define IOCTL_NUM _IOWR
#else
#define IOCTL_NUM _IOWR_BAD
#endif

#define PDIAGEX_MAP_INTF            IOCTL_NUM(PDIAGEX_IOCTL, 35, 1024)
#define PDIAGEX_GET_INTF_CNT        IOCTL_NUM(PDIAGEX_IOCTL, 36, 1024)

#define INTF_MAP_LINE_SIZE  135

main(int argc, char *argv[])
{
	int fid,fd,rc;
	unsigned int num_of_intf=0;
	char *fbuff= NULL;

	if(0x1 == argc) {
		printf("\nmkintfmap: PCI device name missing\n");
		return(0);
	}

	if(!strncmp(argv[1],"eth", 3))
	{
		num_of_intf = 1; //Input to the ioctl..(1) implies device class ethernet
	}

#if _DEBUG_MKMAP_
	printf("The device class option passed is %d\n",num_of_intf);
#endif

	if((fid = fopen("/tmp/intf_map.txt", "w+")))
	{

		fd= open("/dev/miscchar", O_RDWR);
		if (fd < 0) {
			printf("\nmkintfmap:error opening char device file miscchar\n");
			return -1;
		}

		if( (rc = ioctl(fd, PDIAGEX_GET_INTF_CNT, &num_of_intf))== 0)
		{
			fbuff=(char *)malloc(num_of_intf*INTF_MAP_LINE_SIZE *sizeof(char));
			if( fbuff == NULL )
			{
				printf("mkintfmap: Malloc failed\n");
				return(0);
			}
			#if _DEBUG_MKMAP_
			printf("Number of interface lines are = %d\n",num_of_intf);
			#endif
		}
		if( (rc = ioctl(fd, PDIAGEX_MAP_INTF,fbuff))== 0)
		{
			int buflen = strlen(fbuff);
			if( fwrite(fbuff,1,buflen,fid) < buflen)
					printf("mkintfmap: fwrite error\n");

			close(fd);
		}
		else
			printf("mkintfmap: IOCTL failed \n");
		fclose(fid);
	}
	else
	{
		printf("mkintfmap:There is some problem in opening the file /tmp/intf_map.txt \n");
	}
	return(0);
}

