/*
 *  viewer-fltk.cc
 *  Avida
 *
 *  Created by Charles on 7/8/07
 *  Copyright 1999-2007 Michigan State University. All rights reserved.
 *
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; version 2
 *  of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <csignal>

#include "Avida.h"
#include "AvidaTools.h"

#include "cAvidaConfig.h"
#include "cDriverManager.h"
#include "cWorld.h"

#include "cDriver_FLTKViewer.h"


using namespace std;


int main(int argc, char * argv[])
{
  Avida::Initialize();
  
  Avida::PrintVersionBanner();
  
  // Initialize the configuration data...
  cAvidaConfig* cfg = new cAvidaConfig();
  Avida::ProcessCmdLineArgs(argc, argv, cfg);

  tList<cString> errors;
  cWorld* world = cWorld::Initialize(cfg, AvidaTools::FileSystem::GetCWD(), &errors);
  
  if (!world) {
    tListIterator<cString> it(errors);
    while ((it.Next())) {
      cerr << "error: " << *it.Get() << endl;
      delete it.Get();
    }
    return -1;
  }

  cAvidaDriver* driver = NULL;
  
  // Test to see if we should be in analyze mode only...
//  if (world->GetConfig().ANALYZE_MODE.Get() > 0); // @CAO Do something here...

  // Turn control over to the driver!
  driver = new cDriver_FLTKViewer(world);
  driver->Run();
  
  return 0;
}
