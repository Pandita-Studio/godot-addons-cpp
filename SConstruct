#!python
import os
import sys

env = DefaultEnvironment()

if sys.platform.startswith("linux"):
    host_platform = "linux"
elif sys.platform == "darwin":
    host_platform = "osx"
elif sys.platform == "win32" or sys.platform == "msys":
    host_platform = "windows"
else:
    raise ValueError(
        "Could not detect platform automatically, please specify with "
        "platform=<platform>"
    )

is64 = sys.maxsize > 2 ** 32

if (
    env["TARGET_ARCH"] == "amd64"
    or env["TARGET_ARCH"] == "emt64"
    or env["TARGET_ARCH"] == "x86_64"
    or env["TARGET_ARCH"] == "arm64-v8a"
):
    is64 = True

opts = Variables([], ARGUMENTS)

# Define our options
opts.Add(EnumVariable('target', "Compilation target", 'debug', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', "Compilation platform", '', ['', 'windows', 'x11', 'linux', 'osx']))
opts.Add(EnumVariable('p', "Compilation target, alias for 'platform'", '', ['', 'windows', 'x11', 'linux', 'osx']))
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", 'no'))
opts.Add(PathVariable('target_path', 'The path where the lib is installed.', 'bin/'))
opts.Add(PathVariable('target_name', 'The library name.', 'pandita-addons', PathVariable.PathAccept))
opts.Add(EnumVariable("bits", "Target platform bits", "64" if is64 else "32", ("32", "64")))

# Pandita Addons sources
steam_addon_sources = "src/steam/"
discord_addon_sources = "src/discord/"

# Godot dependencies
godot_headers_path = "godot-cpp/godot-headers/"
godot_bindings_path = "godot-cpp/"
godot_library = "libgodot-cpp"

# Discord SDK
discord_sdk_path = "discord-game-sdk/"
discord_library = "discord_game_sdk"

# Updates the environment with the option variables.
opts.Update(env)

# Process some arguments
if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

if env['p'] != '':
    env['platform'] = env['p']

if env['platform'] == '':
    print("No valid target platform selected.")
    quit()


# Check our platform specifics
if env['platform'] == "osx":
    if host_platform != "osx":
        print("""warning: Building for OSX on non-OSX platform.
            \rCross-compilation is NOT supported and this will most likely error-out.""")

    env['target_path'] += 'osx/'
    
    godot_library += '.osx'

    env.Append(CCFLAGS=['-arch', 'x86_64'])
    env.Append(CXXFLAGS=['-std=c++17'])
    env.Append(LINKFLAGS=['-arch', 'x86_64'])

    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS=['-g', '-O2'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])


elif env['platform'] in ('x11', 'linux'):
    if host_platform != "linux":
        print("""warning: Building for Linux on non-Linux platform.
            \rCross-compilation is NOT supported and this will most likely error-out.""")

    env['target_path'] += 'x11/'
    
    godot_library += '.linux'

    env.Append(CCFLAGS=['-fPIC'])
    env.Append(CXXFLAGS=['-std=c++17'])

    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS=['-g3', '-Og'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])


elif env['platform'] == "windows":
    if host_platform != "windows":
        print("""warning: Building for Windows on non-Windows platform.
            \rCross-compilation is NOT supported and this will most likely error-out.""")

    env['target_path'] += 'win64/'

    godot_library += '.windows'

    env.Append(CPPDEFINES=["WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS"])
    env.Append(CCFLAGS=["-W3", "-GR"])
    
    if env["target"] == "debug":
        env.Append(CPPDEFINES=["_DEBUG"])
        env.Append(CCFLAGS=["-EHsc", "-MDd", "-ZI"])
        env.Append(LINKFLAGS=["-DEBUG"])
    else:
        env.Append(CPPDEFINES=["NDEBUG"])
        env.Append(CCFLAGS=["-O2", "-EHsc", "-MD"])
    
    env.Append(CCFLAGS=["/std:c++14"])
    

# discord libs has no debug releases
if env['target'] in ('debug', 'd'):
    godot_library += '.debug'
else:
    godot_library += '.release'


# only in windows 64 and 32 bits support for discord libs
godot_library += '.' + str(env['bits'])


# Godot stuff
env.Append(CPPPATH=[godot_headers_path, godot_bindings_path + 'include/', godot_bindings_path + 'include/core/', godot_bindings_path + 'include/gen/'])
env.Append(LIBPATH=[godot_bindings_path + 'bin/'])

# Discord stuff
env.Append(CPPPATH=[discord_sdk_path + 'include/'])
env.Append(LIBPATH=[discord_sdk_path + 'bin/'])

# Linked libs
env.Append(LIBS=[godot_library, discord_library])

# Sources
env.Append(CPPPATH=['src/', steam_addon_sources, discord_addon_sources])
sources = Glob('src/*.cpp')
sources += Glob(steam_addon_sources + '*.cpp')
sources += Glob(discord_addon_sources + '*.cpp')

# We have to add discord sdk sources too
sources += Glob(discord_sdk_path + 'src/*.cpp')

library = env.SharedLibrary(target=env['target_path'] + env['target_name'] , source=sources)

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))