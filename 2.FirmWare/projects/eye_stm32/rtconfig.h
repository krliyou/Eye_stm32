#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* RT-Thread Kernel */

#define RT_NAME_MAX 10
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512

/* kservice optimization */

#define RT_KSERVICE_USING_STDLIB
/* end of kservice optimization */
#define RT_DEBUG
#define RT_DEBUG_COLOR
#define RT_DEBUG_INIT_CONFIG
#define RT_DEBUG_INIT 1
#define RT_DEBUG_MODULE_CONFIG
#define RT_DEBUG_MODULE 1


/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP
/* end of Memory Management */

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart4"
/* end of Kernel Device Object */
#define RT_VER_NUM 0x40101
/* end of RT-Thread Kernel */
#define ARCH_ARM
#define RT_USING_CPU_FFS
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M7

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10


/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V2
#define RT_SERIAL_USING_DMA
#define RT_USING_PIN
#define RT_USING_SPI

/* Using USB */

/* end of Using USB */
/* end of Device Drivers */

/* C/C++ and POSIX layer */

#define RT_LIBC_DEFAULT_TIMEZONE 8

/* POSIX (Portable Operating System Interface) layer */


/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */

/* end of Interprocess Communication (IPC) */
/* end of POSIX (Portable Operating System Interface) layer */
/* end of C/C++ and POSIX layer */

/* Network */

/* end of Network */

/* Utilities */

/* end of Utilities */
/* end of RT-Thread Components */

/* RT-Thread Utestcases */

/* end of RT-Thread Utestcases */

/* krliyou Fimware Drivers */

/* end of krliyou Fimware Drivers */

/* krliyou Fimware Libraries */

/* Krliyou Fimware Modules */

/* end of Krliyou Fimware Modules */

/* Krliyou Fimware Packages */

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32H7

/* Hardware Drivers Config */

/* BOARD_STM32H750_UltraPI */

#define SOC_STM32H750XB
/* end of BOARD_STM32H750_UltraPI */

/* Board extended module */

/* end of Board extended module */

/* Onboard Peripheral Drivers */

#define BSP_USING_USB_TO_USART
/* end of Onboard Peripheral Drivers */

/* On-chip Peripheral Drivers */

#define BSP_SCB_ENABLE_I_CACHE
#define BSP_SCB_ENABLE_D_CACHE
#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART4
#define BSP_UART4_RX_BUFSIZE 256
#define BSP_UART4_TX_BUFSIZE 0
#define BSP_USING_SPI
#define BSP_USING_SPI2
/* end of On-chip Peripheral Drivers */

/* External Libraries */

/* end of External Libraries */
/* end of Hardware Drivers Config */

#endif
