Only confirmed to work with pypy3 <=7.3.0, it definitely doesn't work with pypy3 7.3.1 (Filed upstream at https://foss.heptapod.net/pypy/pypy/issues/3236)

1. I downloaded the pypy3 7.3.0 tarball for my OS from https://bitbucket.org/pypy/pypy/downloads/ (e.g. pypy3.6-v7.3.0-linux64.tar.bz2)
2. I extracted it and moved it to `/opt/pypy3`
3. I ran `/opt/pypy3/bin/pypy3 build.py` in the pypyninja directory
4. I manually edited binary ninja settings.json to set interpreter to my pypy shim:
```
{
    "python" :
    {
        "interpreter" : "/home/username/pypyninja/libpypyshim.so"
    }
}
```
5. I ran binary ninja from the command line, like
```
LD_LIBRARY_PATH=/opt/pypy/bin ~/binaryninja/binaryninja -de
```

6. `print(sys.version)` in the binja console showed it was using pypy as the interpreter
