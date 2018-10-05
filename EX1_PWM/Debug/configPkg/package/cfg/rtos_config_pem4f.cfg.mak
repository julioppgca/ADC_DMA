# invoke SourceDir generated makefile for rtos_config.pem4f
rtos_config.pem4f: .libraries,rtos_config.pem4f
.libraries,rtos_config.pem4f: package/cfg/rtos_config_pem4f.xdl
	$(MAKE) -f /Users/Julio/ECP108/EX1_PWM/src/makefile.libs

clean::
	$(MAKE) -f /Users/Julio/ECP108/EX1_PWM/src/makefile.libs clean

