/******************************************************************************
**
** $Id: dld_geom.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_geom.h"
#include <algorithm>
#include <numeric>

long Len::checkMin(long pref_len)
{
   long min = getMin();

   if(pref_len < min)
      return min;

   return pref_len;
}

long Len::getMin() 
{
   if(!child.size())
      return min;

   long maxmin = 0;

   for( LI i = child.begin(); i != child.end(); ++i) {
      Len& l = **i;
      long m = l.getMin();
      if(max_flag) {
	 if(m > maxmin)
	    maxmin = m;
      } 
      else 
	 maxmin += m;
   }
   return maxmin + sad;
}

long Len::getPref() 
{
   long m = getMin();

   if(pref) {
      return (pref > m) ? pref : m;
   }

   /* No pref set and no childs */
   if(!child.size())
      return m*1000;

   if (max_flag == true) {
      long maxmin = getMin();
      
      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;
	 long pr = l.getPref();
	 if(pr > maxmin)
	    maxmin = pr;
      }
      return maxmin+sad;
   }

   long all_per = 0;
   long nwidth = 0;
   long fixed = 0;

   for( LI i = child.begin(); i != child.end(); ++i) {
      Len& l = **i;
      if(l.per)
	 all_per += l.per;
      else {
	 fixed += l.getMin();
	 nwidth += l.getPref();
      }
   }

   if(all_per)
   {
      if(all_per >= 100)
      {
	 nwidth = 0;
      }
      else {
	 nwidth = 100 * nwidth / (100 - all_per);
	 all_per = 100;
	 fixed = 0;
      }

      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;
	 
	 if(l.per) {
	    long t1 = all_per 
	       * l.checkMin(nwidth * l.per / all_per) 
	       / l.per;

	    long t2 = all_per * l.checkMin(l.getPref()) / l.per;
	    if(t1 > nwidth) 
	       nwidth = t1;

	    if(t2 > nwidth) 
	       nwidth = t2;
	 }
      }
   }
   else fixed = 0;

   return nwidth + fixed + sad;
}

long Len::calcSize(long length) 
{
   long min = getMin();
   long hundred = 100;
   long fixed = sad;

/*   if(length && (length == real))
      return real;
*/
   if(length < min) 
      length = min;

   if (child.size()) {
      length -= sad;

      long all_per = 0;
      unsigned long nwidth = 0;
      long nfix = 0;

      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;

	 long min = l.getMin();

	 if(l.per) {
	    all_per += l.per;
	 }
	 else {
	    nwidth += l.getPref();
	    nfix += min;
	 }
	 fixed += min;
      }
      length = max((long)length, (long)fixed);

      long remain = length - fixed;

      if(all_per >= 100)
	 hundred = all_per;


      bool prop = false;
      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;
	    if(l.per && (l.per * length / hundred < l.getMin()))
	       prop = true;
      }      

      long nremain = (hundred-all_per) * length / hundred;
      int apos = 0;

      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;
	 long plus = 0;
	 long min = l.getMin();

	 if(l.per) {
	    if(remain) {
	       // All nonpercent elements exceed the total size
	       if(nfix > nremain) {
		  plus = remain * l.per / hundred;
	       }
	       else  {
		  if(prop) {
		     plus = remain * l.per / hundred;
		  }
		  else {
		     // All right
		     plus = length * l.per / hundred  - min;
		  }
	       }
	    }
	 }
	 else {	   
	    if((nfix < nremain) && remain) {
	       if(prop) {
		  plus = (remain + nfix) * (hundred - all_per) / hundred 
		     * l.getPref() / nwidth - min;
	       }
	       else
		  plus = (nremain - nfix) * l.getPref() / nwidth;
	    }
	 }

	 if (plus < 0)
	    plus = 0;

	 l.setSize(min + plus);
	 l.pos = apos;
	 apos += l.real;
      }     
   }
   return ( length );
}

long Len::getMaxSize(long length) 
{
   if (child.size()) {

      long min = getMin();

      if(length < min)
	 length = min;

      length -= sad;

      bool recalc;
      long all_per = 100;

      for( LI i = child.begin(); i != child.end(); ++i) {
	 Len& l = **i;
	 if(l.per > all_per)
	    all_per = l.per;
      }
     
      do {
	 recalc = false;
	 for( LI i = child.begin(); i != child.end(); ++i) {
	    Len& l = **i;	    
	    long perc = l.getPer();
	    long nl = l.setSize( perc ? 
					 length * perc / all_per : length );
	    l.pos = 0;
	    if(nl > length) {
	       length = nl;
	       recalc = true;
	       break;
	    }
	 }	 
      } while (recalc);
      length += sad;
   }
   else
   {
      long pref = getPref();
      if(length > pref)
	 length = pref;

      long min = getMin();
      if(length < min)
	 length = min;
   }

   return length;
}

long Len::setSize(long length) 
{
   if (max_flag == true)
      return real = getMaxSize(length);
   else
      return real = calcSize(length);
}
