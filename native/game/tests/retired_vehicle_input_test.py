#!/usr/bin/env python3
"""Compatibility entry point: the removed model was confirmed as a Huracan and restored."""
from pathlib import Path
import runpy
runpy.run_path(str(Path(__file__).with_name('lamborghini_identity_input_test.py')), run_name='__main__')
