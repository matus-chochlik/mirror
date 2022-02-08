# coding=utf8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
# ------------------------------------------------------------------------------
import os
import re
import numpy
import argparse

# ------------------------------------------------------------------------------
class PlotArgParser(argparse.ArgumentParser):
    # --------------------------------------------------------------------------
    def _add_baseline_input_arg(self):
        self.add_argument(
            '-b', '--baseline',
            metavar='INPUT-FILE',
            nargs='?',
            default=None,
            dest='baseline_path',
            type=os.path.realpath
        )
    # --------------------------------------------------------------------------
    def _add_single_input_arg(self):
        self.add_argument(
            '-i', '--input',
            metavar='INPUT-FILE',
            nargs='?',
            default=None,
            dest='input_path',
            type=os.path.realpath
        )
    # --------------------------------------------------------------------------
    def _add_multi_input_arg(self):
        self.add_argument(
            '-i', '--input',
            metavar='INPUT-FILE',
            nargs='?',
            default=None,
            dest='input_path',
            type=os.path.realpath,
            action="append"
        )
    # --------------------------------------------------------------------------
    def __init__(self, **kw):
        argparse.ArgumentParser.__init__(self, **kw)

        self.add_argument(
            '-o', '--output',
            metavar='OUTPUT-FILE',
            dest='output_path',
            nargs='?',
            type=os.path.realpath
        )

        self.add_argument(
            '-W', '--view',
            dest='viewer',
            default=False,
            action="store_true"
        )

        self.add_argument(
            '-L', '--label-format',
            dest='label_format',
            default=None,
            choices=[
                "reflection_kind"
            ]
        )

    # --------------------------------------------------------------------------
    def make_options(self):
        opts = self.parse_args()
        # ----------------------------------------------------------------------
        class _Options(object):
            # ------------------------------------------------------------------
            def __init__(self, base):
                self.__dict__.update(base.__dict__)
                self.min_jobs = 1
                self._fmt_re_rk = re.compile(".*-(tbr|vbr).*-(tmp|cmp)-.*")
            # ------------------------------------------------------------------
            def initialize(self, plot, fig):
                if self.output_path:
                    fig.set_size_inches(8, 4.5)

            # ------------------------------------------------------------------
            def color_from_to(self, i, mini, maxi):
                lc = (1.0, 0.8, 0.1)
                rc = (0.6, 0.8, 1.0)
                mul = [0.85, 1.15]
                m = mul[i % len(mul)]
                f = (i - mini) / (maxi - mini)
                return tuple(
                    max(min(m * (l * (1.0 - f) + r * f), 1), 0)
                    for l, r in zip(lc, rc)
                )

            # ------------------------------------------------------------------
            def dataset_color(self, dataset, col_index):
                return self.color_from_to(
                    col_index, 0, dataset.column_count() - 1);

            # ------------------------------------------------------------------
            def measurement_label(self, name):
                if self.label_format == "reflection_kind":
                    found = self._fmt_re_rk.search(name)
                    if found:
                        return {
                            "tbr-tmp":"TB template",
                            "tbr-cmp":"TB consteval",
                            "vbr-tmp":"VB template",
                            "vbr-cmp":"VB consteval"
                        }["%s-%s" % (found.group(1), found.group(2))]
                        print()
                    
                return name

            # ------------------------------------------------------------------
            def finalize(self, plot):
                if self.viewer:
                    plot.show()
                elif self.output_path:
                    plot.savefig(
                        self.output_path,
                        orientation="landscape",
                        transparent=True,
                        format="pdf"
                    )

        return _Options(opts)

# ------------------------------------------------------------------------------
class DataSet:
    # --------------------------------------------------------------------------
    def __init__(self):
        self._key_name = ""
        self._bln_index = None
        self._col_index = {}
        self._col_infos = {}
        self._data = {}

    # --------------------------------------------------------------------------
    def parse_row(self, rowstr):
        return rowstr.strip().split(';')

    # --------------------------------------------------------------------------
    def get_row(self, key):
        try:
            key = float(key)
        except ValueError:
            pass
        try:
            return self._data[key]
        except KeyError:
            result = self._data[key] = {}
            return result

    # --------------------------------------------------------------------------
    def merge_head(self, row, set_name, key_col):
        result = []
        for i in range(len(row)):
            head = row[i]
            if i == key_col:
                col_key = None
            else:
                col_key = (set_name, head)

            try:
                result.append(self._col_index[col_key])
            except KeyError:
                if i == key_col:
                    col_idx = None
                else:
                    col_idx = len(self._col_index)
                try:
                    col_info = self._col_infos[col_idx]
                except:
                    col_info = {
                        "sources": []
                    }
                    col_info = self._col_infos[col_idx] = col_info

                col_info["sources"].append((set_name, head))
                col_info["set_name"] = set_name
                col_info["head"] = head
                result.append(col_idx)
                self._col_index[col_key] = col_idx

        return result

    # --------------------------------------------------------------------------
    def merge_row(self, row, col_indices, key_col):
        rowdata = self.get_row(row[key_col])
        for i in range(len(row)):
            if col_indices[i] is not None:
                rowdata[col_indices[i]] = float(row[i])

    # --------------------------------------------------------------------------
    def merge_csv(self, csv, set_name, key_col=0, bln_col=None):
        col_indices = self.merge_head(
            self.parse_row(csv.readline()), set_name, key_col)

        if bln_col is not None:
            self._bln_index = col_indices[bln_col]

        for line in csv.readlines():
            self.merge_row(self.parse_row(line), col_indices, key_col)

    # --------------------------------------------------------------------------
    def column_count(self):
        return len(self._col_index)

    # --------------------------------------------------------------------------
    def column_label(self, options, col_index):
        return options.measurement_label(self._col_infos[col_index]["set_name"])

    # --------------------------------------------------------------------------
    def subtract_baseline(self, x, y, i):
        j = self._bln_index
        if j is not None:
            return y[i] - y[j]

        return y[i]

    # --------------------------------------------------------------------------
    def data_column(self, col_index):
        def _gen():
            for k, v in sorted(self._data.items()):
                try:
                    yield k, self.subtract_baseline(k, v, col_index)
                except KeyError:
                    pass

        temp = numpy.array([e for e in _gen()]).transpose()
        return (col_index, temp[0], temp[1])

    # --------------------------------------------------------------------------
    def data_columns(self):
        for col_index in self._col_index.values():
            if col_index is not None and col_index != self._bln_index:
                yield self.data_column(col_index)

# ------------------------------------------------------------------------------
