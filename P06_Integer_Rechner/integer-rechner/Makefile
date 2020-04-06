SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),"~/snp/shared.mk")

TARGET     := bin/integer-rechner
MODULES    := src/calc.c src/scan.c src/stack.c src/eval.c src/error.c
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)

include $(SNP_SHARED_MAKEFILE)

