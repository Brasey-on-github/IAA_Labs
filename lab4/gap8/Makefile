io=uart
PMSIS_OS = freertos

APP = stm_gap8_cpx
APP_SRCS += src/stm_gap8_cpx.c lib/cpx/src/com.c lib/cpx/src/cpx.c
APP_INC=lib/cpx/inc inc
APP_CFLAGS += -O3 -g
APP_CFLAGS += -DconfigUSE_TIMERS=1 -DINCLUDE_xTimerPendFunctionCall=1

CONFIG_GAP_LIB_JPEG = 1

RUNNER_CONFIG = $(CURDIR)/config.ini

include $(RULES_DIR)/pmsis_rules.mk
