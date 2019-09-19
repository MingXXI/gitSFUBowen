
# Compile on Linux

Use `Makefile`. Run:

    make

# Compile on MacOS

First install `freeglut` which is a drawing and event loop library
for OpenGL. If you have not installed HomeBrew first install that
from [the HomeBrew webpage](https://brew.sh/) using the default
install location. Then:

    brew install freeglut

Then use `Makefile.macos`. Run:

    make -f Makefile.macos
