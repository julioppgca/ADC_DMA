## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em4f linker.cmd package/cfg/rtos_config_pem4f.oem4f

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/rtos_config_pem4f.xdl
	$(SED) 's"^\"\(package/cfg/rtos_config_pem4fcfg.cmd\)\"$""\"/Users/Julio/ECP108/EX2_ARM_CMSIS_DSP/.config/xconfig_rtos_config/\1\""' package/cfg/rtos_config_pem4f.xdl > $@
	-$(SETDATE) -r:max package/cfg/rtos_config_pem4f.h compiler.opt compiler.opt.defs
