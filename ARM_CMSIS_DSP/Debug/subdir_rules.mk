################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main_cmsis_dsp.obj: ../main_cmsis_dsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/Julio/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="/Users/Julio/ECP108/ARM_CMSIS_DSP" --include_path="/Users/Julio/ECP108/ARM_CMSIS_DSP" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="main_cmsis_dsp.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-519777983:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-519777983-inproc

build-519777983-inproc: ../rtos_config.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/Users/Julio/ti/tirex-content/xdctools_3_32_00_06_core/xs" --xdcpath="/Users/Julio/ti/tirtos_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C123GH6PM -r release -c "/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"/Users/Julio/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include\" --include_path=\"/Users/Julio/ECP108/ARM_CMSIS_DSP\" --include_path=\"/Users/Julio/ECP108/ARM_CMSIS_DSP\" --include_path=\"/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b\" --include_path=\"/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix\" --include_path=\"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include\" --define=ccs=\"ccs\" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-519777983 ../rtos_config.cfg
configPkg/compiler.opt: build-519777983
configPkg/: build-519777983


