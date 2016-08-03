# coding=utf-8
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
import os, sys 

def print_bash_complete_script(argparser):

	import argparse

	print('#  Distributed under the Boost Software License, Version 1.0.')
	print('#  (See accompanying file LICENSE_1_0.txt or copy at')
	print('#  http://www.boost.org/LICENSE_1_0.txt)')
	print('#')
	print('#  Automatically generated file. Do NOT modify manually,')
	print('#  edit %(self)s instead' % {"self" : os.path.basename(sys.argv[0])})
	print(str())
	print('function _mirror_config()')
	print('{')
	print('	COMPREPLY=()')
	print('	local curr="${COMP_WORDS[COMP_CWORD]}"')
	print('	local prev="${COMP_WORDS[COMP_CWORD-1]}"')
	print(str())

	options_with_path=list()
	for action in argparser._actions:
		if action.type == os.path.abspath:
			options_with_path += action.option_strings

	print('	case "${prev}" in')
	print('		-h|--help)')
	print('			return 0;;')
	print('		--generator)')
	print('			OLDIFS=${IFS}')
	print('			IFS=$\'\\r\\n\'')
	print('			COMPREPLY=($(')
	print('				cmake --help |')
	print('				sed -n \'/^Generators\s*$/,$p\' |')
	print('				tail -n +4 |')
	print('				grep -v -e \'^\s\+=\' |')
	print('				grep -v -e \'^\s*$\' |')
	print('				cut -d= -f 1 |')
	print('				sed \'s/^\s*\([^ ].\+[^ ]\)\s*$/\\1/\' |')
	print('				grep -e "^${curr}" |')
	print('				sed \'s/ /\\\\ /g\'')
	print('			))')
	print('			IFS=${OLDIFS}')
	print('			return 0;;')
	print('		%s)' % str("|").join(options_with_path))
	print('			COMPREPLY=($(compgen -f "${curr}"))')
	print('			return 0;;')


	for action in argparser._actions:
		if action.choices is not None:
			print('		%s)' % str("|").join(action.option_strings))
			ch = str(" ").join([str(c) for c in action.choices])
			print('			COMPREPLY=($(compgen -W "%s" -- "${curr}"))' % ch)
			print('			return 0;;')

	print('		*)')
	print('	esac')
	print(str())

	print('	local only_once_opts=" \\')
	for action in argparser._actions:
		if type(action) != argparse._AppendAction:
			print('		%s \\' % str(" ").join(action.option_strings))
	print('	"')
	print(str())

	muog_list = list()
	muog_id = 0
	for group in argparser._mutually_exclusive_groups:
		print('	local muog_%d=" \\' % muog_id)
		for action in group._group_actions:
			print('		%s \\' % str(" ").join(action.option_strings))
		print('	"')
		print(str())
		muog_list.append('muog_%d' % muog_id)
		muog_id += 1

	print('	local repeated_opts=" \\')
	for action in argparser._actions:
		if type(action) == argparse._AppendAction:
			print('		%s \\' % str(" ").join(action.option_strings))
	print('	"')
	print(str())
	print('	local opts="${repeated_opts}"')
	print(str())
	print('	for opt in ${only_once_opts}')
	print('	do')
	print('		local opt_used=false')
	print('		for pre in ${COMP_WORDS[@]}')
	print('		do')
	print('			if [ "${opt}" == "${pre}" ]')
	print('			then opt_used=true && break')
	print('			fi')
	print('		done')
	print('		if [ "${opt_used}" == "false" ]')
	print('		then')
	print('			for muog in "${%s}"' % str('}" "${').join(muog_list))
	print('			do')
	print('				local is_muo=false')
	print('				for muo in ${muog}')
	print('				do')
	print('					if [ "${opt}" == "${muo}" ]')
	print('					then is_muo=true && break')
	print('					fi')
	print('				done')
	print('				if [ "${is_muo}" == "true" ]')
	print('				then')
	print('					for pre in ${COMP_WORDS[@]}')
	print('					do')
	print('						for muo in ${muog}')
	print('						do')
	print('							if [ "${pre}" == "${muo}" ]')
	print('							then opt_used=true && break')
	print('							fi')
	print('						done')
	print('					done')
	print('				fi')
	print('			done')
	print(str())
	print('			if [ "${opt_used}" == "false" ]')
	print('			then opts="${opts} ${opt}"')
	print('			fi')
	print('		fi')
	print('	done')
	print(str())
	print('	if [ ${COMP_CWORD} -le 1 ]')
	print('	then opts="--help ${opts}"')
	print('	fi')
	print(str())
	print('	COMPREPLY=($(compgen -W "${opts}" -- "${curr}"))')
	print('}')
	print('complete -F _mirror_config ./mirror-config')

def man_highlight(info_text):
	import re

	return re.sub(
		r'(MIRROR_[A-Z0-9_]+|CXXFLAGS|LDFLAGS|GL.*/[A-Za-z0-9_]+.h)',
		r'\\fI\1\\fR',
		info_text
	)

def print_manual(argparser):
	import argparse
	import datetime

	now = datetime.datetime.now()
	print(
		'.TH CONFIGURE-MIRROR 1 "%s" "Configuration script for Mirror."' %
		str(now.date())
	)
	print('.SH "NAME"')
	print('configure-mirror \\- configuration script for the Mirror library.')
	print('.SH "SYNOPSIS"')
	print('.B configure-mirror')
	print('[')
	print('OPTIONS')
	print(']')

	print('.SH "DESCRIPTION"')
	print('This script is a more user-friendly way to invoke the cmake-based')
	print('build system of \\fBMirror\\fR.')


	print('.SH "OPTIONS"')

	for action in argparser._actions:
		print(".TP")
		opt_info = str()
		for opt_str in action.option_strings:
			if opt_info:
				opt_info += ", "
			opt_info += '\\fB'+opt_str+'\\fR'
			if action.type == os.path.abspath:
				opt_info += ' <\\fI'+str(action.dest).upper()+'\\fR>';
			if action.choices is not None:
				opt_info += ' {\\fB'
				opt_info += '\\fR,\\fB'.join(map(str, action.choices))
				opt_info += '\\fR}'
		print(opt_info)
		print(
			str(' ').join(man_highlight(action.help).split()) % {
				"prog": "\\fBconfigure-mirror\\fR",
				"default": "\\fB"+str(action.default)+"\\fR"
			}
		)


	print('.SH "AUTHOR"')
	print('Matus Chochlik, chochlik@gmail.com')

	print('.SH "COPYRIGHT"')
	print('Copyright (c) Matus Chochlik')

	print(".PP")
	print("Permission is granted to copy, distribute and/or modify this document")
	print("under the terms of the Boost Software License, Version 1.0.")
	print("(See a copy at http://www.boost.org/LICENSE_1_0.txt)")

