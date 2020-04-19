SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),../../shared.mk)

TARGET     := bin/integer-rechner
MODULES    := src/calc.c src/scan.c src/stack.c src/eval.c src/error.c
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)

SNP_TESTLIB := ../../testlib

include $(SNP_SHARED_MAKEFILE)

