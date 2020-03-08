# snp-lab-code
Code für die Praktika zur Vorlesung Systemnahe Programmierung

## Personal docs

### How to fix upstream Makefiles

Due to the Makefiles clearly only targetting the SNP vagrant VMs I've had to make a bunch of adjustments to fix them.

Following fixes need to be applied if not done already:
- `SNP_SHARED_MAKEFILE` should use a relative path to the shared.mk and not the hardcoded `~/snp/` directory.
- `SNP_TESTLIB` variable needs to be set with a relative path to `testlib`