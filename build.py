import cffi
ffi = cffi.FFI()

with open('shim.c') as f:
    ffi.set_source('libpypyshim', f.read())
with open('shim.h') as f:
    ffi.embedding_api(f.read())
with open('shim.py') as f:
    ffi.embedding_init_code(f.read())

ffi.compile()
