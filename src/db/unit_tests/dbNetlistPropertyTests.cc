
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2018 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#include "dbNetlistProperty.h"

#include "tlUnitTest.h"
#include "tlVariant.h"

#include <memory>

TEST(1_Basic)
{
  db::NetNameProperty name;
  EXPECT_EQ (name.to_string (), "name:''");

  name.set_name ("abc");
  EXPECT_EQ (name.to_string (), "name:abc");
  EXPECT_EQ (name.name (), "abc");

  db::NetNameProperty n2 = name;
  EXPECT_EQ (n2.name (), "abc");

  n2 = db::NetNameProperty ("xyz");
  EXPECT_EQ (n2.name (), "xyz");

  n2.set_name ("\"quoted\"");
  EXPECT_EQ (n2.to_string (), "name:'\"quoted\"'");

  tl::Extractor ex ("net42");
  n2.read (ex);
  EXPECT_EQ (n2.name (), "net42");
}

TEST(2_Variants)
{
  std::auto_ptr<db::NetNameProperty> nn (new db::NetNameProperty ());
  nn->set_name ("net42");

  tl::Variant v (nn.release (), db::NetlistProperty::variant_class (), true);
  EXPECT_EQ (v.is_user<db::NetlistProperty> (), true);
  EXPECT_EQ (dynamic_cast<db::NetNameProperty &>(v.to_user<db::NetlistProperty> ()).name (), "net42");
  EXPECT_EQ (v.to_string (), "name:net42");

  tl::Variant vv = v;
  v = tl::Variant ();
  EXPECT_EQ (v.is_user<db::NetlistProperty> (), false);
  EXPECT_EQ (vv.is_user<db::NetlistProperty> (), true);
  EXPECT_EQ (dynamic_cast<db::NetNameProperty &>(vv.to_user<db::NetlistProperty> ()).name (), "net42");
}