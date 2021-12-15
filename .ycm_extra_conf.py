# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os
import sys
import subprocess
#------------------------------------------------------------------------------#
def thisDir():
    return os.path.dirname(os.path.abspath(__file__))
#------------------------------------------------------------------------------#
def absPath(path, work_dir = thisDir()):
    if not os.path.isabs(path):
        path = os.path.join(work_dir, path)
    return os.path.realpath(path)
#------------------------------------------------------------------------------#
def makeOptionPathsAbsolute(old_opts, work_dir = thisDir()):
    new_opts = list()
    make_next_abs = False
    path_flags = ['-include', '-isystem', '-I', '-iquote', '--sysroot=']

    for opt in old_opts:
        new_opt = opt
        if make_next_abs:
            new_opt = absPath(opt, work_dir)
            make_next_abs = False
        else:
            for path_flag in path_flags:
                if opt == path_flag:
                    make_next_abs = True
                    break
                if opt.startswith(path_flag):
                    path = opt[len(path_flag):]
                    new_opt = path_flag + MakePathAbsolute(path, work_dir)
                    break

        new_opts += [new_opt]
    return new_opts
#------------------------------------------------------------------------------#
def binaryDir():
    try:
        with open(os.path.join(thisDir(), "BINARY_DIR"), "rt") as bdf:
            return absPath(bdf.read(), thisDir())
    except: pass
    return os.path.join(thisDir(), "_build")
#------------------------------------------------------------------------------#
def llvmPrefixDir():
    try:
        with open(os.path.join(thisDir(), "LLVM_PREFIX"), "rt") as lpf:
            return absPath(lpf.read(), thisDir())
    except: pass
    return "/opt/llvm"
#------------------------------------------------------------------------------#
compiler_opts = [
    '-DMIRROR_YCM',
    '-pedantic',
    '-Wall',
    '-Weverything',
    '-Werror',
    '-Wno-language-extension-token',
    '-Wno-c++98-compat',
    '-Wno-c++98-compat-pedantic',
    '-Wno-c++20-compat',
    '-Wno-c++2a-extensions',
    '-Wno-padded',
    '-Wno-documentation-unknown-command',
    '-std=c++2b',
    '-stdlib=libc++',
    '-freflection-ts',
    '-freflection-ext',
    '-x', 'c++',
]
#------------------------------------------------------------------------------#
def scanForSystemIncludeDirs():
    try:
        clang_exe = os.path.join(llvmPrefixDir(), 'bin', 'clang++')
        clang_args = [clang_exe, '-xc++', '-E', '-v', '-']
        clang_proc = subprocess.Popen(
            clang_args,
            stdin=open("/dev/null"),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        unused, output = clang_proc.communicate()
        tokens = [t.decode('utf8') for t in output.split()]

        result = []
        for i in range(1, len(tokens)):
            if tokens[i-1].endswith("-isystem"):
                if os.path.isdir(tokens[i]):
                    result.append(tokens[i])

        return result
    except Exception as err:
        print(err)

    return [
        "/usr/include",
        "/usr/local/include"
    ]
#------------------------------------------------------------------------------#
system_include_dirs = scanForSystemIncludeDirs()

#------------------------------------------------------------------------------#
project_include_dirs = [
    os.path.join(llvmPrefixDir(), "include"),
    os.path.join(llvmPrefixDir(), "include", "c++", "v1"),
    os.path.join(binaryDir(), "include"),
    'include'
]
#------------------------------------------------------------------------------#
def FlagsForFile(filename, ** kwargs):
    final_opts = compiler_opts

    for path in system_include_dirs:
        apath = absPath(path)
        if os.path.isdir(apath):
            final_opts += ['-isystem', apath]

    for path in project_include_dirs:
        apath = absPath(path)
        if os.path.isdir(apath):
            final_opts += ['-I', apath]

    path, ext = os.path.splitext(filename)

    if ext in [".hpp", ".inl", ".cpp", ".h"]:
        final_opts += ['-include', 'include/mirror/meta.hpp']

    return {
        'flags': makeOptionPathsAbsolute(final_opts),
        'do_cache': True
    }
#------------------------------------------------------------------------------#
if __name__ == "__main__":
    for arg in sys.argv[1:]:
        if os.path.isfile(arg):
            print(FlagsForFile(arg))
#------------------------------------------------------------------------------#
