################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
project_includes/EK_TM4C123GXL.obj: ../project_includes/EK_TM4C123GXL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --include_path="/Users/Julio/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="/Users/Julio/ECP108/EX2_ARM_CMSIS_DSP" --include_path="/Users/Julio/ECP108/EX2_ARM_CMSIS_DSP" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="project_includes/EK_TM4C123GXL.d_raw" --obj_directory="project_includes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

project_includes/adc_dma_samples.obj: ../project_includes/adc_dma_samples.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --include_path="/Users/Julio/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="/Users/Julio/ECP108/EX2_ARM_CMSIS_DSP" --include_path="/Users/Julio/ECP108/EX2_ARM_CMSIS_DSP" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Users/Julio/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="project_includes/adc_dma_samples.d_raw" --obj_directory="project_includes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


