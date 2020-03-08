SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),../../shared.mk)

TARGET     := bin/boundinbox
SOURCES    := src/main.c
TSTSOURCES := tests/tests.c
LIBS       := -lm

SNP_TESTLIB := ../../testlib

include $(SNP_SHARED_MAKEFILE)
