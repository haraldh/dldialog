/******************************************************************************
**
** $Id: dld_list.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_list.h"
#include "dld_listitem.h"
#include "dld_qtapp.h"

#include <qstring.h>
#include <iostream.h>

DLD_QTList:: 
DLD_QTList (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QListBox (_parent, name.c_str()),
   DLD_QTObj (name, pd),
   dict ()
{
  set_multi(false);
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list ";
#endif
   connect (this, SIGNAL(selected(int)),
	    this, SLOT(slotSelected(int)));
}

DLD_QTList::
~DLD_QTList ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list delete\n";
#endif
   slotSelected(0);
}

void DLD_QTList::slotSelected(int)
{
   deactivate();
   QString str (""), istr;
   int i, cnt = count ();

   for (i = 0; i < cnt; i++)
   {
      DLD_QTObj *obj = dict.find (item (i));
      if (obj)
      {
	 if (!isSelected (i))
	    obj->deactivate();	  
      }
   }

   for (i = 0; i < cnt; i++)
   {
      DLD_QTObj *obj = dict.find (item (i));
      if (obj)
      {
	 if (isSelected (i))
	 {
	    if(is_multi) {
               str += istr.setNum (i + 1);
	       str += QString (" ");
            } else {
               str = istr.setNum (i + 1);
            }

#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "list activate " << obj->dld_name
		   << endl << flush;
#endif
	    obj->activate ();
	 }
      }
   }

   varvalue = (const char *)str;

   activate ();
}

DLD_ListItem *DLD_QTList::
listitem (const string& name)
{
   DLD_QTListItem *lbi = new DLD_QTListItem(this, name, pardia);
   QListBox::insertItem (lbi);

   add_child(lbi);

   dict.insert ((QListBoxItem *) lbi, lbi);

   return lbi;
}


QSize DLD_QTList::
sizeHint ()
{
   int cnt = count ();
   int height = 0;
   int i;
   cnt = (cnt <= 12) ? cnt : 12;
   for (i = 0; i < cnt; i++)
     height += (itemHeight (i) + 2);
   return QSize (maxItemWidth () + 10, 10 + height);
}


void DLD_QTList::
create (void)
{
  bool wasset=false;
  clearSelection ();

  QString str, istr;
  int i, cnt = count ();

  // This must be here .... do not REMOVE!
  if(cnt)
    setCurrentItem(0);

  if ( fontname.length() > 0 ) {
     QFont newfont( fontname.c_str() , fontsize, false );
     this->setFont( newfont );
  }

  setMinimumSize(((maxItemWidth() < 100) ? maxItemWidth() : 100 ) 
                 + 10, 10 + itemHeight (0) * ((count() <= 3) ? count() : 3));
   
  if(cnt) {

     // First check the listitems
     for (i = 0; i < cnt; i++)
     {
        DLD_QTListItem *obj = dict.find (item (i));
        if (obj)
        {
           if (obj->test_env())
           {
              wasset=true;
              setSelected(i, TRUE);
#ifdef DEBUG
              DLDdbg << DLD_LIB_PREFIX "list activate " << i << " obj " 
                     << obj->dld_name << "\n";
#endif
           }
        }
     }
     
     // Now check my own variable
     for (i = 0; i < cnt; i++)
     {
        if (test_env(string(istr.setNum (i + 1))))
        {
           wasset=true;
           setSelected(i, TRUE);
#ifdef DEBUG
           DLDdbg << DLD_LIB_PREFIX "list activate " << i << "\n";
#endif
        }
     }

     if (!is_multi && !wasset ) {
        setSelected(0, TRUE);
     }

     centerCurrentItem();
     updateCellWidth();
     repaint();
     
//   pardia->dld_app->processEvents();
//     slotSelected(0);
     
     for (i = 0; i < cnt; i++)
     {
        DLD_QTListItem *obj = dict.find (item (i));
        if (obj)
        {
           obj->create();
        }
     }
     
     DLD_Obj::create();
  }
}

void DLD_QTList::
set_multi(bool on)
{
   setMultiSelection (on);
   DLD_List::set_multi(on);
}

