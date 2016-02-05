/* @(#)13       1.12.3.1  src/htx/usr/lpp/htx/inc/sys/misclib.h, libmisc, htxubuntu 9/29/11 08:29:38 */

#include <linux/version.h>
#include <linux/ioctl.h>

/* IOCTL numbers for the PDIAGEX calls */

#define PDIAGEX_IOCTL   0x01


#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#define IOCTL_NUM _IOWR
#else
#define IOCTL_NUM _IOWR_BAD
#endif

#define PDIAGEX_DD_DIAGNOSE          1
#define PDIAGEX_DD_RESTORE           2
#define PDIAGEX_OPEN                 3
#define PDIAGEX_CLOSE                4
#define PDIAGEX_DD_DMA_SETUP         5
#define PDIAGEX_DD_DMA_COMPLETE      6
#define PDIAGEX_DD_WATCH_FOR_INTR    7
#define PDIAGEX_DD_READ              8
#define PDIAGEX_DD_WRITE             9
#define PDIAGEX_CONFIG_READ          10
#define PDIAGEX_CONFIG_WRITE         11
#define PDIAGEX_OPEN_MISC	     12
#define PDIAGEX_CLOSE_MISC           13
#define PDIAGEX_PIN_USER_MEM	     14
#define PDIAGEX_UNPIN_USER_MEM       15
#define PDIAGEX_BINDPROCESSOR	     16
#define PDIAGEX_STATE		     20
#define CACHE_BYTES		     21
#define TRAP_HTX		     22
#define MIOPCFGET		     23
#define MIOPCFPUT		     24
#define FPU_EXP                      25
#define PDIAGEX_SET_EEH              26
#define PDIAGEX_READ_SLOT_RESET      27
#define PDIAGEX_SET_SLOT_RESET       28
#define PDIAGEX_OPEN_ERROR_INJECT    29
#define PDIAGEX_CLOSE_ERROR_INJECT   30
#define PDIAGEX_INJECT_ERROR         31
#define PDIAGEX_INIT_INJECT_ERROR    32
#define PDIAGEX_SLOT_ERR_DETAIL      33
#define PDIAGEX_CONFIGURE_BRIDGE     34
#define PROCESSOR_ID		     37
#define PDIAGEX_RESTORE_BARS	     40
#define TRAP_HTX64		     41
#define EFF2PHYSICAL                 42
