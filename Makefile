.PHONY: build clean install install-dev test venv help

help:
	@echo "Available targets:"
	@echo "  make venv        - Create virtual environment (required on RPi)"
	@echo "  make build       - Build distribution packages (wheel + source)"
	@echo "  make install     - Install package locally"
	@echo "  make install-dev - Install in editable mode (development)"
	@echo "  make test        - Test the installation"
	@echo "  make clean       - Remove build artifacts"

venv:
	@echo "Creating virtual environment..."
	python3 -m venv .venv
	. .venv/bin/activate && pip install --upgrade pip build
	@echo "✓ Virtual environment created. Activate with: source .venv/bin/activate"

build:
	@echo "Building distribution packages..."
	. .venv/bin/activate && python -m pip install --upgrade build
	. .venv/bin/activate && python -m build
	@echo "✓ Build complete. Packages in dist/"

install:
	@echo "Installing package..."
	. .venv/bin/activate && pip install .

install-dev:
	@echo "Installing in editable mode..."
	. .venv/bin/activate && pip install -e .

test:
	@echo "Testing installation..."
	. .venv/bin/activate && python -c "from drfrancintosh import hdmi; print('✓ Import successful'); print(f'  - rgba_to_rgb16: {hdmi.rgba_to_rgb16}'); print(f'  - rgb_to_rgb16: {hdmi.rgb_to_rgb16}')"

clean:
	@echo "Cleaning build artifacts..."
	rm -rf build/
	rm -rf dist/
	rm -rf *.egg-info
	rm -rf drfrancintosh.egg-info/
	rm -rf .eggs/
	rm -rf __pycache__/
	find . -type d -name __pycache__ -exec rm -rf {} + 2>/dev/null || true
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.so" -delete
	@echo "✓ Clean complete"
