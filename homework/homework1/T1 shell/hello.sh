#!/bin/bash
time find -name "*.c" -o -name "*.h" | xargs grep -l "hello"
