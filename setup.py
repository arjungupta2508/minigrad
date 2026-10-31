from setuptools import setup

setup(
    cffi_modules=["minigrad_build.py:ffibuilder"],
)