/*
 * This file part of makedict - convertor from any dictionary format to any
 * http://xdxf.sourceforge.net
 * Copyright (C) 2006 Evgeniy <dushistov@mail.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cstring>

#include "xml.hpp"

const char Xml::raw_entrs[] = { '<',   '>',   '&',    '\'',    '\"',    0 };
const char* Xml::xml_entrs[] = { "lt;", "gt;", "amp;", "apos;", "quot;", 0 };

void Xml::add_and_encode(std::string& str, char ch)
{


	char *res = strchr(raw_entrs, ch);
	if (!res)
		str += ch;
	else {
		str += '&';
		str += xml_entrs[res - raw_entrs];
	}
}

void Xml::encode(const std::string& str, std::string& res)
{
	std::string::size_type irep = str.find_first_of(raw_entrs);
	if (irep == std::string::npos) {
		res = str;
		return;
	}

	res = std::string(str, 0, irep);
	std::string::size_type isize = str.size();

	while (irep != isize) {
		std::string::size_type ient;
		for (ient = 0; raw_entrs[ient] != 0; ++ient)
			if (str[irep] == raw_entrs[ient]) {
				res += '&';
				res += xml_entrs[ient];
				break;
			}
		if (raw_entrs[ient] == 0)
			res += str[irep];
		++irep;
	}
}
