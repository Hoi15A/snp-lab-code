#!/bin/sh

date -u +"%Y-%m-%dT%H:%M:%SZ" | qrencode -t ASCII
