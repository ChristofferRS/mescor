project('start', 'c')

base_inc = include_directories([
    'src',
    'modified',
    'src/boards/evkmimxrt1170/xip',
    'src/components/common_task',
    'src/components/flash/nand',
    'src/components/internal_flash',
    'src/components/lists',
    'src/components/log',
    'src/components/mem_manager',
    'src/components/messaging',
    'src/components/osa',
    'src/components/phy',
    'src/components/serial_manager',
    'src/components/uart',
    'src/devices/MIMXRT1176',
    'src/devices/MIMXRT1176/drivers',
    'src/devices/MIMXRT1176/utilities/debug_console',
    'src/devices/MIMXRT1176/utilities/str',
    'src/devices/MIMXRT1176/xip',
    'src/middleware/usb/device',
    'src/middleware/usb/host',
    'src/middleware/usb/host/class',
    'src/middleware/usb/include',
    'src/middleware/usb/output/source/device',
    'src/middleware/usb/output/source/device/class',
    'src/middleware/usb/phy',
])

base_src = files([
    'board_hardware.c',
    'clock_config.c',
    'usb_device_cdc_eem.c',
    'src/middleware/usb/output/source/device/class/usb_device_msc.c',
    'src/middleware/usb/output/source/device/class/usb_device_msc_ufi.c',
    'modified/board.c',
    'modified/pin_mux.c',
    'modified/usb_device_class.c',
    'src/components/flash/nand/flexspi/fsl_flexspi_nand_flash.c',
    'src/components/lists/fsl_component_generic_list.c',
    'src/components/phy/device/phyrtl8211f/fsl_phyrtl8211f.c',
    'src/components/phy/mdio/enet/fsl_enet_mdio.c',
    'src/components/serial_manager/fsl_component_serial_manager.c',
    'src/components/serial_manager/fsl_component_serial_port_uart.c',
    'src/components/uart/fsl_adapter_lpuart.c',
    'src/devices/MIMXRT1176/drivers/fsl_anatop_ai.c',
    'src/devices/MIMXRT1176/drivers/fsl_caam.c',
    'src/devices/MIMXRT1176/drivers/fsl_clock.c',
    'src/devices/MIMXRT1176/drivers/fsl_common.c',
    'src/devices/MIMXRT1176/drivers/fsl_common_arm.c',
    'src/devices/MIMXRT1176/drivers/fsl_csi.c',
    'src/devices/MIMXRT1176/drivers/fsl_dac12.c',
    'src/devices/MIMXRT1176/drivers/fsl_dcdc.c',
    'src/devices/MIMXRT1176/drivers/fsl_dmamux.c',
    'src/devices/MIMXRT1176/drivers/fsl_edma.c',
    'src/devices/MIMXRT1176/drivers/fsl_enet.c',
    'src/devices/MIMXRT1176/drivers/fsl_flexspi.c',
    'src/devices/MIMXRT1176/drivers/fsl_gpio.c',
    'src/devices/MIMXRT1176/drivers/fsl_gpc.c',
    'src/devices/MIMXRT1176/drivers/fsl_gpt.c',
    'src/devices/MIMXRT1176/drivers/fsl_lpadc.c',
    'src/devices/MIMXRT1176/drivers/fsl_lpi2c.c',
    'src/devices/MIMXRT1176/drivers/fsl_lpspi.c',
    'src/devices/MIMXRT1176/drivers/fsl_lpuart.c',
    'src/devices/MIMXRT1176/drivers/fsl_mu.c',
    'src/devices/MIMXRT1176/drivers/fsl_ocotp.c',
    'src/devices/MIMXRT1176/drivers/fsl_pdm.c',
    'src/devices/MIMXRT1176/drivers/fsl_pdm_edma.c',
    'src/devices/MIMXRT1176/drivers/fsl_pmu.c',
    'src/devices/MIMXRT1176/drivers/fsl_pwm.c',
    'src/devices/MIMXRT1176/drivers/fsl_pxp.c',
    'src/devices/MIMXRT1176/drivers/fsl_romapi.c',
    'src/devices/MIMXRT1176/drivers/fsl_sema4.c',
    'src/devices/MIMXRT1176/drivers/fsl_semc.c',
    'src/devices/MIMXRT1176/drivers/fsl_snvs_hp.c',
    'src/devices/MIMXRT1176/drivers/fsl_snvs_lp.c',
    'src/devices/MIMXRT1176/drivers/fsl_soc_src.c',
    'src/devices/MIMXRT1176/drivers/fsl_tempsensor.c',
    'src/devices/MIMXRT1176/drivers/fsl_wdog.c',
    'src/devices/MIMXRT1176/drivers/fsl_xbara.c',
    'src/devices/MIMXRT1176/utilities/debug_console/fsl_debug_console.c',
    'src/devices/MIMXRT1176/utilities/str/fsl_str.c',
    'src/middleware/usb/device/usb_device_dci.c',
    'src/middleware/usb/device/usb_device_ehci.c',
    'src/middleware/usb/host/class/usb_host_dfu.c',
    'src/middleware/usb/host/class/usb_host_hub.c',
    'src/middleware/usb/host/class/usb_host_hub_app.c',
    'src/middleware/usb/host/usb_host_devices.c',
    'src/middleware/usb/host/usb_host_ehci.c',
    'src/middleware/usb/host/usb_host_framework.c',
    'src/middleware/usb/host/usb_host_hci.c',
    'src/middleware/usb/output/source/device/class/usb_device_cdc_acm.c',
    'src/middleware/usb/output/source/device/class/usb_device_hid.c',
    'src/middleware/usb/output/source/device/usb_device_ch9.c',
    'src/middleware/usb/phy/usb_phy.c',
])

m7_src = files([
  'src/devices/MIMXRT1176/drivers/cm7/fsl_cache.c',
  'src/devices/MIMXRT1176/gcc/startup_MIMXRT1176_cm7.S',
  'src/devices/MIMXRT1176/system_MIMXRT1176_cm7.c',
  ])

m4_src = files([
  'src/devices/MIMXRT1176/drivers/cm4/fsl_cache.c',
  'src/devices/MIMXRT1176/gcc/startup_MIMXRT1176_cm4.S',
  'src/devices/MIMXRT1176/system_MIMXRT1176_cm4.c',
  ])

base_c_args = []
base_c_args += '-DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1'
base_c_args += '-DLWIP_ENET_FLEXIBLE_CONFIGURATION'
base_c_args += '-DLWIP_POSIX_SOCKETS_IO_NAMES=0'
base_c_args += '-DSDK_DEBUGCONSOLE_UART'
base_c_args += '-DSDK_DELAY_USE_DWT'
base_c_args += '-DSERIAL_PORT_TYPE_UART=1'
base_c_args += '-DUSB_HOST_CONFIG_DFU'
base_c_args += '-DUSE_SDRAM'
base_c_args += '-D__STARTUP_CLEAR_BSS'
base_c_args += '-D__STARTUP_INITIALIZE_NONCACHEDATA'
base_c_args += '-D__USE_SHMEM'
base_c_args += '-DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING'
base_c_args += '-DDATA_SECTION_IS_CACHEABLE=1'

m7_c_args = []
m7_c_args += '-DCPU_MIMXRT1176CVM8A_cm7'
m7_c_args += '-DXIP_BOOT_HEADER_ENABLE=1'
m7_c_args += '-DXIP_EXTERNAL_FLASH=1'

m4_c_args = []
m4_c_args += '-DCPU_MIMXRT1176CVM8A_cm4'


deps = []
deps  += dependency('libc', fallback: ['picolibc', 'picolibc_dep'])
deps  += dependency('cmsis', fallback: ['cmsis', 'cmsis_dep'])

m7_lib = static_library('m7_lib',
  include_directories : base_inc,
  sources : base_src + m7_src,
  c_args : base_c_args + m7_c_args,
  dependencies : deps,
  )

m4_lib = static_library('m4_lib',
  include_directories : base_inc,
  sources : base_src + m4_src,
  c_args : base_c_args + m4_c_args,
  dependencies : deps,
  )

m7_dep = declare_dependency(
  include_directories : base_inc,
  link_with : m7_lib,
  compile_args : base_c_args + m7_c_args,
  )
m4_dep = declare_dependency(
  include_directories : base_inc,
  link_with : m4_lib,
  compile_args : base_c_args + m4_c_args,
  )
start_dep = m4_dep
