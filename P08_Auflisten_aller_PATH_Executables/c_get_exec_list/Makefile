SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),../../shared.mk)

TARGET     := bin/c-get-exec-list
MODULES    := 
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)

SNP_TESTLIB := ../../testlib

include $(SNP_SHARED_MAKEFILE)

# CFLAGS  += -Werror
CFLAGS  += -std=gnu99