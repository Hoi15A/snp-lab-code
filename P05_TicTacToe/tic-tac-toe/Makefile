SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),../shared.mk)

TARGET     := bin/tic-tac-toe
MODULES    := src/model.c src/view.c src/control.c
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)

SNP_TESTLIB := ../testlib

include $(SNP_SHARED_MAKEFILE)

