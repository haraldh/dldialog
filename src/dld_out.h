/******************************************************************************
**
** $Id: dld_out.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (Harald.Hoyer@hot.spotline.de) 
** for delix Computer GmbH (http://www.delix.de)
**
******************************************************************************/


/******************************************************************************
 *
 * IMPORTANT:
 * ----------
 *
 * If you modify anything of this you have to modify 
 * GUI_VERSION_INFO in configure.in following the guidelines in
 * README.developers
 *
 *****************************************************************************/


#ifndef DLD_GUI_OUT_H
#define DLD_GUI_OUT_H

#include <sys/types.h>
#include <fstream.h>		// for ifstream
#include <unistd.h>
#include <string>

/**
 * Output pipe class.
 * It opens a pipe and closes it after all copies are deleted.
 * @short Output pipe class.
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_Out {
public:
   /**
    * Normal Constructor.
    * @param path The path to the output pipe.
    */
   DLD_Out(const string& path);

   /**
    * Copy Constructor.
    * @param copy The DLD_Out to create a copy from.
    */
   DLD_Out(const DLD_Out & copy);

   /**
    * Default destructor.
    * Closes the pipe only if there are no copies and deletes the file.
    */
   ~DLD_Out();

   /** Create a copy from another DLD_Out.
    * @param copy The DLD_Out to create a copy from.
    */
   void init(const DLD_Out & copy) const;

   /** Closes the pipe only if there are no copies and deletes the file.
    */
   void flush() const;

   /** The output stream.
    */
   ofstream *out;

private:
   /** The internal counter.
    */
   int *counter;

   /** The path to the pipe.
    */
   string path;
};

#endif
