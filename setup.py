from setuptools import Extension, setup


setup(
    name="drfrancintosh",
    version="0.1.0",
    description="Python bindings for the pi02w HDMI RGB565 helpers",
    ext_modules=[Extension("drfrancintosh.hdmi._hdmi", sources=["drfrancintosh/hdmi/hdmi.c"])],
    packages=["drfrancintosh", "drfrancintosh.hdmi"],
    zip_safe=False,
)