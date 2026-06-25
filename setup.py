from setuptools import Extension, setup


setup(
    name="drfrancintosh",
    version="0.1.0",
    description="Python bindings for the pi02w HDMI RGB565 helpers",
    ext_modules=[Extension("hdmi._hdmi", sources=["hdmi/hdmi.c"])],
    packages=["hdmi"],
    zip_safe=False,
)