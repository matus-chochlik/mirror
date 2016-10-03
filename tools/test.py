#!/usr/bin/python
# coding=utf-8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os, sys, glob, subprocess

def root_dir():
	return os.path.abspath(os.path.join(
		os.path.dirname(sys.argv[0]),
		os.path.pardir
	))

def test_src_dir():
	return os.path.join(root_dir(), "test")

def build_dir():
	try:
		p = open(os.path.join(root_dir(), "BINARY_DIR"), "rt").read()
		if os.path.isdir(p):
			return p
	except: pass
	return os.path.join(root_dir(), "_build")

def test_build_dir():
	return os.path.join(build_dir(), "test")

def lib_src_dir(library):
	return os.path.join(test_src_dir(), library)

def lib_build_dir(library):
	return os.path.join(test_build_dir(), library)

def exec_test(work_dir, test_name):
	suffix = test_name[-2:]

	if suffix in ["_c", "_r"]:
		subprocess.call(["make", test_name], cwd=work_dir)

	if suffix in ["_r"]:
		test_exe = os.path.join(work_dir, test_name)
		subprocess.call([test_exe], cwd=work_dir)

def exec_tests():
	try:
		library = sys.argv[1]
	except IndexError:
		sys.stderr.write("Error: Missing library name.\n")
		sys.exit(1)

	if not os.path.isdir(lib_src_dir(library)):
		sys.stderr.write("Error: Invalid library name '%s'\n" % library)
		sys.exit(3)

	exec_dir = lib_build_dir(library)

	if not os.path.isdir(exec_dir):
		sys.stderr.write("Error: Tests for '%s' not configured\n" % library)
		sys.exit(4)

	tests = sys.argv[2:]

	for test_patt in tests:
		test_glob = os.path.join(
			lib_src_dir(library),
			test_patt+"_[cr].cpp"
		)
		test_names = [
			os.path.splitext(os.path.basename(x))[0]
			for x in glob.glob(test_glob)
		]
		for test_name in test_names:
			exec_test(exec_dir, "%s-%s" % (library, test_name))


exec_tests()
