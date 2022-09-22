## Windows

We need the following things:

- [Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/es/downloads/?q=build+tools)
- SCons (can be installed via: `python -m pip install scons`)

### 1. Clone the repo and init submodules

```
git clone --recursive https://github.com/Pandita-Studio/godot-addons-cpp.git
cd godot-addons-cpp
git submodule update --init --recursive
```

### 2. Compiling godot link libraries

> Note: We have to do this just one time.

```
cd godot-cpp
scons platform=windows generate_bindings=yes -j4 bits=64
```

### 3. Compiling godot addons libraries

Inside `godot-addons-cpp` directory just run:

```
scons platform=windows
```

This will generate `dll` library inside `bin/` directory.

## Linux

ToDo