#!/usr/bin/sed
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
s/metaobject<M>)/metaobject<M> mo)/g
s/metaobject<M>,/metaobject<M> mo,/g
s/__metaobject_is_meta_\(\w\+\)(M)\([^;]\)/reflects_\1(mo)\2/g
