from libpypyshim import ffi
import sys

# HACK: rlcompleter imports __main__
if not '__main__' in sys.modules:
    class FakeMain: pass
    sys.modules['__main__'] = FakeMain() # type: ignore

_version = ffi.new('char[]', sys.version.encode('utf8') + b'\0')

@ffi.def_extern()
def pps_eval(s):
    code = ffi.string(s).decode('utf8')
    exec(code)

@ffi.def_extern()
def pps_get_version():
    return _version

@ffi.def_extern()
def pps_sys_path_insert(i, path):
    path = ffi.string(path).decode('utf8')
    sys.path.insert(i, path)
