# drfrancintosh

Python bindings for the `hdmi` RGB565 conversion helpers.

Distribution name: `drfrancintosh`
Import module: `hdmi`

## Install

From a local checkout:

```bash
pip install .
```

Or with uv:

```bash
uv pip install .
```

## Use

```python
from hdmi import rgba_to_rgb16, rgb_to_rgb16

rgb565 = rgba_to_rgb16(rgba_bytes, width, height)
```

Both helpers return packed RGB565 bytes for the given image buffer.# rpi02w_lowlevel
