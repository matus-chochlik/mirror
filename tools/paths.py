# coding=utf-8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
import os 

# returns the common valid prefix for the specified paths
def common_path_prefix(paths):
	prefix = os.path.commonprefix(paths)
	for path in paths:
		if prefix != path:
			suffix = path[len(prefix):]
			if not suffix.startswith(os.path.sep):
				return os.path.dirname(prefix)
	return prefix


# returns the shortest path from the directory
# at source_path to the directory at target_path
def shortest_path_from_to(source_path, target_path):
	source_path = os.path.abspath(source_path)
	target_path = os.path.abspath(target_path)

	if source_path == target_path:
		return os.path.curdir

	common_prefix = common_path_prefix([
		source_path,
		target_path
	])
	backtrace = os.path.curdir
	while source_path != common_prefix:
		source_path = os.path.dirname(source_path)
		backtrace = os.path.join(os.path.pardir, backtrace)
	backtrace = os.path.normpath(backtrace)

	relative_path = target_path[len(common_prefix):]
	if relative_path.startswith(os.path.sep):
		relative_path = relative_path[len(os.path.sep):]
	relative_path = os.path.normpath(os.path.join(
		backtrace,
		relative_path
	))
	if len(relative_path) < len(target_path):
		return relative_path
	else: return target_path

# shortens a full command path to a command name only
# if possible
def shorten_command(command_path):
	def is_exe(filepath):
		return os.path.isfile(filepath) and os.access(filepath, os.X_OK)

	command_dir, command = os.path.split(command_path)

	for path_dir in os.environ["PATH"].split(os.pathsep):
		if command_dir == path_dir and is_exe(command_path):
			return command
	return command_path

