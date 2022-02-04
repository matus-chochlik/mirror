# coding=utf8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
# ------------------------------------------------------------------------------
import os
import numpy
import argparse

# ------------------------------------------------------------------------------
class PlotArgParser(argparse.ArgumentParser):
    # --------------------------------------------------------------------------
    def _add_single_input_arg(self):
        self.add_argument(
            '-i', '--input',
            metavar='INPUT-FILE',
            dest='input_path',
            nargs='?',
            type=os.path.realpath
        )
    # --------------------------------------------------------------------------
    def _add_multi_input_arg(self):
        self.add_argument(
            '-i', '--input',
            metavar='INPUT-FILE',
            dest='input_path',
            nargs='?',
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

    # --------------------------------------------------------------------------
    def make_options(self):
        opts = self.parse_args()
        # ----------------------------------------------------------------------
        class _Options(object):
            # ------------------------------------------------------------------
            def __init__(self, base):
                self.__dict__.update(base.__dict__)
                self.min_jobs = 1
            # ------------------------------------------------------------------
            def initialize(self, plot, fig):
                if self.output_path:
                    fig.set_size_inches(8, 4.5)

            # ------------------------------------------------------------------
            def color_from_to(self, i, mini, maxi):
                lc = (1.0, 0.8, 0.1)
                rc = (0.6, 0.8, 1.0)
                f = (i - mini) / (maxi - mini)
                return tuple(
                    max(min(l * (1.0 - f) + r * f, 1), 0) for l, r in zip(lc, rc)
                )

            # ------------------------------------------------------------------
            def dataset_color(self, dataset, col_name):
                return self.color_from_to(
                    dataset.column_index(col_name),
                    0, dataset.column_count() - 1);

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
        self._key_head = "key"
        self._col_heads = {}
        self._col_index = {}
        self._data = {}

    # --------------------------------------------------------------------------
    def parse_row(self, rowstr):
        return rowstr.strip().split(';')

    # --------------------------------------------------------------------------
    def get_row(self, key):
        try:
            return self._data[key]
        except KeyError:
            result = self._data[key] = {}
            return result

    # --------------------------------------------------------------------------
    def merge_head(self, row, col_names, key_col):
        for i in range(len(row)):
            col_name = col_names[i]
            if not self._col_index.get(col_name):
                self._col_index[col_name] = len(self._col_index)
            if i != key_col:
                self._col_heads[col_name] = row[i]
            else:
                self._key_head = row[i]

    # --------------------------------------------------------------------------
    def merge_row(self, row, col_names, key_col):
        rowdata = self.get_row(row[key_col])
        for i in range(len(row)):
            rowdata[col_names[i]] = float(row[i])

    # --------------------------------------------------------------------------
    def merge_csv(self, csv, col_names, key_col=0):
        if not isinstance(col_names, dict):
            if not isinstance(col_names, list):
                col_names = ["", col_names]
            col_names = {i:col_names[i] for i in range(len(col_names))}

        self.merge_head(self.parse_row(csv.readline()), col_names, key_col)

        for line in csv.readlines():
            self.merge_row(self.parse_row(line), col_names, key_col)

    # --------------------------------------------------------------------------
    def key_column(self):
        return self._key_head, numpy.fromiter(self._data.keys(), float)

    # --------------------------------------------------------------------------
    def column_index(self, col_name):
        return self._col_index[col_name]

    # --------------------------------------------------------------------------
    def column_count(self):
        return len(self._col_index)

    # --------------------------------------------------------------------------
    def data_column(self, col_name):
        return col_name, numpy.fromiter((v.get(col_name) for k, v in self._data.items()), float)

    # --------------------------------------------------------------------------
    def data_columns(self):
        for col_name in self._col_heads.keys():
            yield self.data_column(col_name)

# ------------------------------------------------------------------------------
