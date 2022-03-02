#!/usr/bin/python3 -B
# coding=utf8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
# ------------------------------------------------------------------------------
import os
import re
import sys
import argparse
# ------------------------------------------------------------------------------
class ArgParser(argparse.ArgumentParser):
    # --------------------------------------------------------------------------
    def __init__(self, **kw):
        argparse.ArgumentParser.__init__(self, **kw)

        inc_dir = os.path.realpath(
            os.path.join(
                os.path.dirname(__file__),
                os.pardir, "include", "mirror"))

        self.add_argument(
            '-i', '--input',
            metavar='OUTPUT-FILE',
            dest='input_path',
            nargs='?',
            default=os.path.join(inc_dir, "all.hpp"), 
            type=os.path.realpath
        )

        self.add_argument(
            '-o', '--output',
            metavar='OUTPUT-FILE',
            dest='output_path',
            nargs='?',
            default=os.path.join(inc_dir, "all_ce.hpp"), 
            type=os.path.realpath
        )

    # --------------------------------------------------------------------------
    def make_options(self):
        opts = self.parse_args()
        if not os.path.exists(opts.input_path):
            self.error("%s is not a file" % opts.input_path)

        if opts.output_path is None or os.path.basename(opts.output_path) == "-":
            opts.output = sys.stdout
        else:
            try:
                opts.output = open(opts.output_path, "wt")
            except Exception as err:
                self.error("cannot open output file %s: %s" % (
                    opts.output_path, str(err)))

        return opts

# ------------------------------------------------------------------------------
def make_argparser():
    return ArgParser(prog=os.path.basename(__file__))

# ------------------------------------------------------------------------------
def process_input(strip_re, inc_re, inc_dir, ofd, ifd, input_path, already_done):
    already_done.add(input_path)
    if_doxy = False
    not_doxy = False
    for line in ifd.readlines():
        if line.startswith("#if defined(MIRROR_DOXYGEN)"):
            if_doxy = True
            continue
        if if_doxy:
            if line.startswith("#else"):
                if_doxy = False
                not_doxy = True
                continue
            elif line.startswith("#endif"):
                if_doxy = False
                not_doxy = False
                continue
        elif not_doxy:
            if line.startswith("#endif"):
                not_doxy = False
                continue

        if strip_re.match(line) or if_doxy:
            continue

        inc_match = inc_re.match(line)
        if inc_match is None:
            ofd.write(line)
        else:
            included = os.path.realpath(
                os.path.join(
                    os.path.dirname(input_path),
                    inc_match.group(1)))
            if os.path.exists(included):
                if not included in already_done:
                    with open(included, "rt") as iifd:
                        process_input(
                            strip_re,
                            inc_re,
                            inc_dir,
                            ofd,
                            iifd,
                            included,
                            already_done)
            else:
                ofd.write(line)

# ------------------------------------------------------------------------------
def do_it(options):
    options.output.write("// Automatically generated file (all edits will be lost)\n")
    options.output.write("// Copyright Matus Chochlik.\n")
    options.output.write("// Distributed under the Boost Software License, Version 1.0.\n")
    options.output.write("// See accompanying file LICENSE_1_0.txt or copy at\n")
    options.output.write("//  http://www.boost.org/LICENSE_1_0.txt\n")

    with open(options.input_path, "rt") as ifd:
        process_input(
            re.compile("\s*//[/-].*"),
            re.compile("\s*#include\s+\"([^\"]+)\".*"),
            os.path.realpath(
                os.path.join(
                    os.path.dirname(__file__),
                    os.pardir,
                    "include")),
            options.output,
            ifd,
            options.input_path,
            set())

# ------------------------------------------------------------------------------
def main():
    do_it(make_argparser().make_options())
    return 0
# ------------------------------------------------------------------------------
if __name__ == "__main__":
    exit(main())
# ------------------------------------------------------------------------------

