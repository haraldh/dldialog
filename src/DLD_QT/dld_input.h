/*************************************************************************
**
** $Id: dld_input.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
*************************************************************************/

#ifndef DLD_QTINPUT_H
#define DLD_QTINPUT_H

#include "../dld_input.h"
#include "dld_qtobj.h"
#include <qlined.h>
#include <qvalidator.h>

/** The input widget in qt style
 *
 */
class DLD_QTInput : public QLineEdit, public DLD_Input, public DLD_QTObj
{
   Q_OBJECT;
public:
   ///
   DLD_QTInput(QWidget *_parent, const string& name, DLD_QTDialog *pd);
   ///
   ~DLD_QTInput();
   ///
   void create();  
   /** Set the maximal length of the input field
    * @param len the length
    */
   void set_length(int len) { dld_length = len; };
   void set_ip(bool b) { isIp = b;};
   void set_passwd(bool b) { isPass = b;};
   void set_numeric(bool b) { isNum = b; };

public slots:
   void slotReturn();

   void slotTextChanged1(const char *);
   void slotTextChanged2(const QString &);

protected:
   virtual void keyPressEvent ( QKeyEvent * e );
   virtual void focusInEvent ( QFocusEvent * ) ;
   bool isIp, isNum, isPass;
   int dld_length;
};

/** The input widget validator for ip input
 *
 */
class DLD_IPInput : public QValidator
{
public:
  ///
  DLD_IPInput(QWidget * parent, const char * name = 0);
  ///
  virtual ~DLD_IPInput();
  ///
#if QT_VERSION < 200
  State validate ( QString &, int & );
#else
  State validate ( QString &, int & ) const;
#endif
  ///
  void fixup ( QString & );
};

/** The input widget validator for numeric input
 *
 */
class DLD_NumInput : public QValidator
{
public:
  ///
  DLD_NumInput(QWidget * parent, const char * name = 0);
  ///
  virtual ~DLD_NumInput();
  ///
#if QT_VERSION < 200
  State validate ( QString &, int & ) ;
#else
  State validate ( QString &, int & ) const;
#endif
  ///
  void fixup ( QString & );
};

#endif
