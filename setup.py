from distutils.core import setup, Extension
import os
os.environ["CC"] = "gcc"
os.environ["CXX"] = "gcc"

argon2_hash_module = Extension('argon2_hash',
                               sources = ['ar2/argon2.c',
                                          'ar2/core.c',
                                          'ar2/encoding.c',
                                          'ar2/genkat.c',
                                          'ar2/opt.c',
                                          'ar2/thread.c',
                                          'ar2/blake2/blake2b.c',
                                          'argon2module.c'],
                               include_dirs=['.', './ar2'])


setup (name = 'argon2_hash',
       version = '1.0',
       description = 'Bindings for Argon2 proof of work used by Bitmark',
       ext_modules = [argon2_hash_module])
