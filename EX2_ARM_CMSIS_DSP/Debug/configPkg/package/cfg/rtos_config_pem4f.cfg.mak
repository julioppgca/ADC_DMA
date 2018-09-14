# invoke SourceDir generated makefile for rtos_config.pem4f
rtos_config.pem4f: .libraries,rtos_config.pem4f
.libraries,rtos_config.pem4f: package/cfg/rtos_config_pem4f.xdl
	$(MAKE) -f /Users/Julio/ECP108/EX2_ARM_CMSIS_DSP/src/makefile.libs

clean::
	$(MAKE) -f /Users/Julio/ECP108/EX2_ARM_CMSIS_DSP/src/makefile.libs clean

