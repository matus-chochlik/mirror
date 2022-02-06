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
            def dataset_color(self, dataset, col_index):
                return self.color_from_to(
                    col_index, 0, dataset.column_count() - 1);

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
                col_info["label"] = head
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
    def column_label(self, col_index):
        return self._col_infos[col_index]["label"]

    # --------------------------------------------------------------------------
    def data_column(self, col_index):
        try:
            _gen = ((k, v[col_index]) for k, v in sorted(self._data.items()))
            temp = numpy.array([e for e in _gen]).transpose()
        except KeyError:
            _gen = ([k, 0.0] for k in sorted(self._data.keys()))
            temp = numpy.array([e for e in _gen]).transpose()
        return (col_index, temp[0], temp[1])

    # --------------------------------------------------------------------------
    def data_columns(self):
        for col_index in self._col_index.values():
            if col_index is not None and col_index != self._bln_index:
                yield self.data_column(col_index)

    # --------------------------------------------------------------------------
    def baseline_column(self):
        return self.data_column(self._bln_index)

# ------------------------------------------------------------------------------
