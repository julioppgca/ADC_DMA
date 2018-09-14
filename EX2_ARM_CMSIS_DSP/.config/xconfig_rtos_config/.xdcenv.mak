#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Users/Julio/ti/tirtos_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;/Users/Julio/Robotica/adc_driver/ADC_DMA_Project/.config
override XDCROOT = /Users/Julio/ti/tirex-content/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Users/Julio/ti/tirtos_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;/Users/Julio/Robotica/adc_driver/ADC_DMA_Project/.config;/Users/Julio/ti/tirex-content/xdctools_3_32_00_06_core/packages;..
HOSTOS = MacOS
endif
