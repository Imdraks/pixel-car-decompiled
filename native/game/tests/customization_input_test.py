#!/usr/bin/env python3
"""Compatibility entry point for the original-art PC garage input suite."""
import runpy
from pathlib import Path
runpy.run_path(str(Path(__file__).with_name('pc_garage_input_test.py')),run_name='__main__')
