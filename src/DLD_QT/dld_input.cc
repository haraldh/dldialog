/******************************************************************************
**
** $Id: dld_input.cc,v 1.1 2001/03/14 02:33:12 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_input.h"
#include "dld_text.h"
#include "dld_dialog.h"

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <qregexp.h>
#include <qstring.h>
#include <qkeycode.h>

DLD_QTInput::
DLD_QTInput (QWidget *_parent, const string& name, DLD_QTDialog *pd) :
   QLineEdit (_parent, convstr(name).c_str()),
   DLD_QTObj (name, pd),
   isIp(false),
   isNum(false),
   isPass(false),
   dld_length(0)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "input " << dld_name << " constructed "
	  << endl << flush;
#endif
   setMaxLength (1024);
}


DLD_QTInput::
~DLD_QTInput ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "input deleted\n";
#endif
}

void DLD_QTInput::slotTextChanged1(const char *)
{
   varvalue = text();
   DLD_Obj::activate ();
}

void DLD_QTInput::slotTextChanged2(const QString &)
{
   varvalue = text();
   DLD_Obj::activate ();
}

void DLD_QTInput::slotReturn()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "return pressed" 
	  << endl << flush;
#endif      
   varvalue = text ();
   DLD_QTObj::activate ();
}

void DLD_QTInput::
create ()
{
   setText(pardia->get_env(varname).c_str());

   if (isPass)
   {
      setEchoMode(Password);
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "input passwd\n";
#endif      
   }

   if (isNum)
   {
      setValidator (new DLD_NumInput (this));
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "input numeric\n";
#endif
      setMinimumWidth (sizeHint ().width ());
   }
   else if (isIp)
   {
      if(!strlen(text())) 
	 setText("0.0.0.0");
      setMaxLength (15);
      setValidator (new DLD_IPInput (this));
      setFixedWidth (sizeHint ().width ());
      fixed_width = true;
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "input IP\n";
#endif
   }
   else
      setMinimumWidth (sizeHint ().width ());

   setFixedHeight (sizeHint ().height ());
   fixed_height = true;
      
   if(dld_length) {
      setMaxLength (dld_length);
      int w = sizeHint ().width () / 15 * (dld_length+1);
      setMinimumWidth (w);
      setFixedWidth (w);
      fixed_width = true;
   }

   connect( this, SIGNAL(returnPressed(void)),
	    this, SLOT(slotReturn(void)));
#if QT_VERSION < 200
   connect( this, SIGNAL(textChanged(const char *)),
	    this, SLOT(slotTextChanged1(const char *)));
#else
   connect( this, SIGNAL(textChanged(const QString &)),
	    this, SLOT(slotTextChanged2(const QString &)));
#endif

   DLD_Obj::create();
}

void DLD_QTInput::keyPressEvent ( QKeyEvent * e ) 
{
   if (e->key() == Key_Return || e->key() == Key_Enter ) {
      QLineEdit::keyPressEvent(e);
      emit returnPressed();
   }
   else
      QLineEdit::keyPressEvent(e);
}

void DLD_QTInput::focusInEvent ( QFocusEvent * e) {
   setText(pardia->get_env(varname).c_str());
   QLineEdit::focusInEvent(e);
}


DLD_IPInput::
 DLD_IPInput (QWidget * parent, const char *name):
    QValidator (parent, name)
{
}

DLD_IPInput::
~DLD_IPInput ()
{
}

QValidator::State DLD_IPInput::
validate (QString & input, int &)
#if QT_VERSION > 200
const
#endif
{
   QRegExp accept = QRegExp ("^[0-2]?[0-9]?[0-9]?\\.[0-2]?[0-9]?[0-9]?\\.[0-2]?[0-9]?[0-9]?\\.[0-2]?[0-9]?[0-9]?$", FALSE, FALSE);

   QRegExp correct = QRegExp ("^[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]$", FALSE, FALSE);

   if(correct.match(input) == 0) {
      int num[4], i;

      if(sscanf(input, "%d.%d.%d.%d", &num[0], &num[1], &num[2], &num[3]) != 4)
	 return QValidator::Invalid;

      for(i=0; i<4; i++) {
	 // DLDerr << "Checking num" << i << "=" << num[i] << endl << flush;
	 if(num[i] < 0 || num[i] > 255) 
	    return QValidator::Invalid;
      }

      return QValidator::Valid;
   }

   if (accept.match(input) == 0) {
      return QValidator::Acceptable;
   }

 return QValidator::Invalid;

}

void DLD_IPInput::
fixup (QString &)
{
}

DLD_NumInput::
 DLD_NumInput (QWidget * parent, const char *name):
    QValidator (parent, name)
{
}

DLD_NumInput::
~DLD_NumInput ()
{
}

QValidator::State DLD_NumInput::
validate (QString & input, int &)
#if QT_VERSION > 200
const
#endif
{
   QRegExp accept = QRegExp ("^[0-9]*$");
   QRegExp correct = QRegExp ("^[0-9]+$");

   if(correct.match(input) == 0)
     return QValidator::Valid;
   
   if (accept.match(input) == 0)
    return QValidator::Acceptable;

 return QValidator::Invalid;

}

void DLD_NumInput::
fixup (QString &)
{
}
