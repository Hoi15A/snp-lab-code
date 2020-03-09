#!/bin/bash

qrencode -t ASCII $(date -u +"%Y-%m-%dT%H:%M:%SZ")
