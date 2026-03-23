# Gfx

Just messing with computer graphics.

## Requirements

**To Build**

- [Docker](https://www.docker.com/get-started/)

**To Run (Linux)**

The pre-compiled binary is linked against GLIBC 2.36+. It requires the following system libraries to interface with the GPU and X11/Wayland:

**Ubuntu/Debian**

```bash
sudo apt update && sudo apt install libgl1-mesa-glx libx11-6 libxrandr2 libxinerama1 libxcursor1 libxi6
```

**Fedora**

```bash
sudo dnf install mesa-libGL libX11 libXrandr libXinerama libXcursor libXi
```

**Arch Linux**

```bash
sudo pacman -S mesa libx11 libxrandr libxinerama libxcursor libxi
```

## Building Locally

The project uses a Docker-based build system to ensure a consistent environment.

1. Clone the repository:

```bash
git clone https://github.com/AssoDePicche/gfx.git && cd gfx
```

2. Build it with Docker:

```bash
docker build --target exporter --output type=local,dest=. .
```

This will produce an executable named `Gfx-linux-x86_64` in the project root.

## Usage

After downloading the latest release or building locally, grant execution permissions and run:

```bash
chmod +x Gfx-linux-x86_64
```
