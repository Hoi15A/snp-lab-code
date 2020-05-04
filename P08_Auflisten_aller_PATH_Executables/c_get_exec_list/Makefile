SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),"~/snp/shared.mk")

TARGET     := bin/c-get-exec-list
MODULES    := 
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)


include $(SNP_SHARED_MAKEFILE)

# CFLAGS  += -Werror
