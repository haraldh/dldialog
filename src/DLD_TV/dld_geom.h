/******************************************************************************
**
** $Id: dld_geom.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_GEOM_H
#define DLD_GEOM_H

#include <string>
#include <numeric>
#include <list>

/** 
 * Basic class for one dimensional size handling.
 *
 * Used to implement a geometry handler.
 *
 * @author Harald Hoyer <Harald@Hoyer.org>
 * @version $Id: dld_geom.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
 * @short basic class for one dimensional size handling.
 */
class Len {
public:
   /** 
    * Constructs a one dimensional length with child support
    * @param _flag true if the length is a max length, false if the size 
    * has to be calculated by the childs.
    * @param _min the minimal length. The length will never be shorter.
    * @param _pref the preferred size. Is taken to calculate also properties.
    * @param _per the length in percent from the parent length.
    */
   Len ( long _min = 0, long _pref = 0,
	 long _per = 0) : 
      min(_min), pref(_pref), 
      real(0), pos(0), sad(0), per(_per), max_flag(true)
      {};

   ~Len() {};

   /// Get the actual length.
   long getLen() {
      return real;
   };

   /// Get the actual position.
   int getPos() {
      return pos;
   };

   /// Get the actual position.
   void setPos(int _pos) {
      pos = _pos;
   };

   /// Get the additional size.
   int getSizeAdd() {
      return sad;
   };

   /// Get the actual position.
   void setSizeAdd(int _sad) {
      sad = _sad;
   };

   /// Get the minimal length
   long getMin();

   /// Set the minimal length
   void setMin(long _min) {min = _min;};

   /// Get the preferred length
   long getPref();

   /// Set the preferred length
   void setPref(long _pref) {pref = _pref;};

   /// Get length in percent 
   long getPer() { return per; };

   /// Set length in percent 
   void setPer(long _per) { per = _per; };

   long setSize(long length);

   /** 
    *  Adds a children to the calculation process
    *  @param childlen the child
    */
   void addChild(Len *childlen) {child.push_back(childlen);};

   /** 
    *  Deletes a children from the calculation process
    *  @param childlen the child
    */
   void delChild(Len *childlen) {child.remove(childlen);};

   Len& operator=(Len a) {
      // child.clear();
      child.erase(child.begin(), child.end());

      min = a.min;
      pref = a.pref;
      real = a.real;
      per = a.per;
   };

   void setSizeFlag(bool flag) { max_flag = flag; };

protected:

   long getMaxSize(long length);

   /** 
    * Calculates the length of the children for the desired length.
    * The length is never shorter than the minimal length.
    * If no percent size is specified, the preferred size is taken to
    * calculate the size.
    * If a percent size is given, the algorithm tries to fit it with these
    * properties in the parent length.
    * If all percent sizes exceed 100. All non percent lengths take their
    * minimum value and the rest is shared under the percent lengths according
    * to their minimum values and percent sizes.
    * @param length the desired length
    * @return the real length after calculation
    */
   long calcSize(long length);

private:
   /** 
    *  Check if the len is in the valid range.
    *  @param len the len to be checked
    */
   long checkMin(long len);

   /// the childlist
   list<Len*> child;

   /// the iterator for the childlist
   typedef list<Len*>::const_iterator LI; 

   /// minimal length
   long min;

   /// prefered length
   long pref;

   /// real length
   int real;

   /// real pos
   int pos;

   /// additional size
   int sad;

   /// percentual length of the parent
   long per;

   bool max_flag;
};

#endif
