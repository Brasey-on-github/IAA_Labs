CRAZYFLIE_BASE := ~/Desktop/projects/crazyflie-firmware/
#
# We override the default OOT_CONFIG here, we could also name
# our config to oot-config and that would be the default.
#
OOT_CONFIG := $(PWD)/config
# To include C file
obj-y += src/drone_controls.o
# To add some includes
EXTRA_CFLAGS += -I$(PWD)/src/includes
LIBSFLAGS += -lm
include $(CRAZYFLIE_BASE)/tools/make/oot.mk
