<!-- -*- sgml -*- -->
<!--
/******************************************************************************
**
** $Id: dldialog.sgml.cpp,v 1.2 2002/04/04 15:25:24 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (dldialog@parzelle.de) 
** Copyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
** 
******************************************************************************/
-->
<!doctype linuxdoc PUBLIC "-//LinuxDoc//DTD LinuxDoc 96//EN"> 
<linuxdoc>
  <article>
    <titlepag>
      <title>The DLDialog Handbook</title>
      <author><name>Harald Hoyer, <tt><htmlurl url="mailto:dldialog@parzelle.de" name="dldialog@parzelle.de"></tt></name></author>
      <date>Version @VERSION@, @DATE@</date>
      <abstract>This Handbook describes DLDialog Version @VERSION@</abstract>
    </titlepag>
    <toc>
    <sect><heading>Introduction</heading>
      <p>
<em>Please don&acute;t forget to read the frequently asked questions! 
Thank You!</em>
      </p><p>
DLDialog offers the capability to draw a variety of widgets,
in order to ease the human user in feeding input to the script. 
The program is designed to be particularly useful to implement system 
administration scripts.
I hope you will enjoy this program.  
      </p><p>
<tt>Harald Hoyer</tt>   
<htmlurl url="mailto:dldialog@parzelle.de" name="dldialog@parzelle.de"> 
</p>
    </sect>
    <sect><heading>Installation</heading>      
      <sect1><heading>How to obtain DLDialog</heading>
	<p>
DLDialog can be found in 
<url url="http://parzelle.de/Linux/Applications/dldialog">.
</p></sect1>
      <sect1><heading>Requirements</heading>
	<p>
In order to successfully compile DLDialog, you need:
<itemize>
	    <item>qt-2 or newer versions</item>
	    <item>tvision 0.7 or newer versions</item>
	    <item>libdl</item>
	    <item>gettext, if you want i18n (internationalisation)</item>
	    <item>automake version 1.4 or newer versions</item>
	    <item>Autoconf version 2.13 or newer versions</item>
	    <item>libtool version 1.2 or newer versions</item>
	    <item>kdoc (ftp.kde.org part of kdevelop) for documentation purposes</item>
	    <item>sgml-tools version &gt;= 1.0.8 for documentation purposes</item>
	  </itemize>
	</p><p>
Some of the required libraries as well as DLDialog itself can
 be found on <url url="http://parzelle.de/Linux/Applications/">.
</p>
      </sect1>
      <sect1><heading>Compilation and installation</heading>
	<sect2><heading>Normal compilation procedure</heading>
	  <p><code>
&dollar; aclocal
&dollar; autoheader
&dollar; automake -a
&dollar; autoconf
&dollar; ./configure --prefix=/usr
</code>
If you do have kdoc installed:
<code>
&dollar; make
</code>
else:
<code>
&dollar; cd src;make
</code>
To install type:
<code>
&dollar; su -c "make install"
</code>
If you want to deinstall it just do a:
<code>
&dollar; su -c "make uninstall"
</code>
</p></sect2>
	<sect2><heading>More options for configure</heading>
	  <p>
<itemize>
	      <item>  --without-qt                                if you want to build DLDialog without qt
</item><item>  --with-qt-dir=&lt;dir&gt;            where the root of qt is installed 
</item><item>  --with-qt-includes=&lt;dir&gt;       where the qt includes are. 
</item><item>  --with-qt-libraries=&lt;dir&gt;      where the qt library is installed.
</item><item>  --without-tv                         if you want to build DLDialog without tvision
</item><item>  --with-tvision-dir=&lt;dir&gt;       where the root of tv is installed 
</item><item>  --with-tvision-includes=&lt;dir&gt;  where the tv includes are. 
</item><item>  --with-tvision-libraries=&lt;dir&gt; where the tv library is installed.
</item></itemize> 
</p><p>See also the files README and INSTALL that come with the distribution. 
</p><p><bf>Again:</bf> 
Should you run into problems, please report them to me.   
</p></sect2>
	<sect2><heading>INSTALL</heading>
	  <p>
<verb>
<!-- @include ../INSTALL -->
</verb>
</p>
	</sect2></sect1></sect>
    <sect><heading>The Manual Page</heading>
      <!-- @include dldialog.man.sgml.body -->
    </sect>
    <sect><heading>DLDialog Program Syntax</heading>
      <p>
In the following text, contents in brackets &lt;&gt; is defined 
at other locations in this text and contents in square brackets 
&lsqb;] is optional.
</p>
      <sect1><heading>General Syntax</heading>
	<p><descrip>
	    <TAG><bf>//</bf><em> &lsqb;&lt;comment&gt;]</em></TAG>
	    <p>DLDialog ignores the rest of the line after //.
</p>
	    <TAG><bf>&num;</bf><em> &lsqb;&lt;comment&gt;]</em></TAG>
	    <p>DLDialog ignores the rest of the line after &num;.
</p>
	    <TAG><em><bf>&lcub;</bf>&lt;block&gt;<bf>&rcub;</bf></em></TAG>
	    <p>
block consists of multiple combinations of commands surrounded by braces.
</p>
	    <TAG><em>&lt;name&gt;</em></TAG>
	    <p>
name is a single word or several words surrounded by parenthesis. A &amp;
will specify the next letter as the shortcut for this item.
</p>
	    <TAG><bf>"</bf><em>&lt;string&gt;</em><bf>" 
"</bf><em>&lt;string&gt;</em><bf>"</bf></TAG>
	    <p>
Strings are concatenated like in ANSI C.
</p>
	    <TAG><em>&lt;varname&gt;</em></TAG>
	    <p>
varname is a single word beginning with an alphabetic letter, 
which contains no special characters.
</p>
	    <TAG><em>&lt;value&gt;</em></TAG>
	    <p>
value is a &lt;varname&gt;, a &lt;name&gt; or a number.
</p>
	    <TAG><em>&lt;executable&gt;</em></TAG>
	    <p>
executable is a filename that has the executable flag set and can be 
executed by e.g. <em>sh -c "&lt;executable&gt;"</em>.

This file will be executed and the standard output of this file will be
parsed and executed as a DLDialog program.

Variables set with the executable will have global effect.
</p>
	    <TAG><em>&lt;command&gt;</em><bf>;</bf></TAG>
	    <p>normal commands end with a semicolon.</p>
	  </descrip></p>
      </sect1>
      <sect1><heading>Common options</heading>
	<p>The following options can be given to all commands:
	<descrip>
	    <TAG><em>&lsqb;</em><bf>-fork</bf></TAG>
	    <p>
Together with the -exec tag this will let your spawned childs live if the parent dies. 
</p>
	    <TAG><em>&lsqb;</em><bf>-height</bf>
                 <em>&lt;height in percent&gt;]</em></TAG>
	    <p>
Specifies the height of the element in percent 
of the parent size.
</p>
	    <TAG><em>&lsqb;</em><bf>-width</bf> 
                 <em>&lt;width in percent&gt;]</em></TAG>
	    <p>
Specifies the width of the element in percent of the parent size.
</p>
	    <TAG><em>
&lsqb;</em><bf>-font</bf><em> &lt;X11 font specifier&gt;]
&lsqb;</em><bf>-size</bf><em> &lt;fontsize&gt;] 
&lsqb;</em><bf>-bg</bf><em> &lt;backgroundcolor&gt;] 
&lsqb;</em><bf>-fg</bf><em> &lt;foregroundcolor&gt;] 
                 </em></TAG>
	    <p>
-font specifies the font of the element in X11/QT mode.

-size specifies the size of the font. E.g. a  absolut numeric size or 
  mini, small, normal, large, huge or big. Default size is 12.

-bg specifies the background color of the font. Can be e.g. blue, white, "#FF0010".

-fg specifies the foreground color of the font. Can be e.g. blue, white, "#FF0010".

</p>
	  </descrip></p>
      </sect1>
      <sect1><heading>Container Commands</heading>
	<p><descrip>
	    <TAG><bf>dialog</bf>&nbsp;<em>&lsqb;&lt;name&gt;] 
&lsqb;</em><bf>-modal</bf><em>] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a dialog window with title &lt;name&gt; which contains the 
elements contained in &lt;block&gt;.

If the argument -modal is set, input for other dialogs is blocked 
until the last modal dialog exited.

There should be one or more buttons with the -exit argument in 
this dialog to let the user exit the dialog.
</p>
	    <TAG><bf>form</bf>&nbsp;<em>&lsqb;&lt;name&gt;] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a rectangle with title &lt;name&gt; which contains the elements
in &lt;block&gt;.

DLDialog tries to order the elements more or less effective in this 
rectangle.
</p>
	    <TAG><bf>row</bf> <em>&lsqb;&lt;name&gt;] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a rectangle with title &lt;name&gt; which contains the elements
in &lt;block&gt;.

DLDialog orders the elements in a row in this rectangle.
</p>
	    <TAG><bf>col</bf> <em>&lsqb;&lt;name&gt;] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a rectangle with title &lt;name&gt; which contains the elements
in &lt;block&gt;.

DLDialog orders the elements in a column in this rectangle.
</p>
	    <TAG><bf>radiolist</bf> <em>&lsqb;&lt;name&gt;] 
&lsqb;</em><bf>-var</bf><em> &lt;varname&gt;] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a rectangle with title &lt;name&gt; which contains radio buttons
in &lt;block&gt;.

DLDialog orders the radio buttons in a column in this rectangle.

The -var argument specifies a variable named &lt;varname&gt;.

At creation this variable will be read and if set to a number, the 
radio button with this number will be activated per default.

If the dialog exits the variable will be set to the number of the 
selected radio button.

E.g. TESTVAR="1".
</p>
	    <TAG><bf>checklist</bf> <em>&lsqb;&lt;name&gt;] 
&lsqb;</em><bf>-var</bf><em> &lt;varname&gt;] 
</em><bf>&lcub;</bf><em>&lt;block&gt;</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a rectangle with title &lt;name&gt; which contains check buttons 
in &lt;block&gt;.

DLDialog orders the check buttons in a column in this rectangle.

The -var argument specifies a variable named &lt;varname&gt;.

At creation this variable will be read and if set to a number(s), the 
check button(s) with this number(s) will be activated per default.

If the dialog exits the variable will be set to the number(s) of the 
selected check button(s).

E.g. TESTVAR="1 3 5".
</p>
	    <TAG><bf>list</bf> <em>&lsqb;&lt;name&gt;] 
&lsqb;</em><bf>-var</bf><em> &lt;varname&gt;] 
&lsqb;</em><bf>-multi</bf> <em>]</em> 
<bf>&lcub; listitem</bf> 
<em>&lsqb;&lt;args&gt;]</em><bf>;</bf>
<em> ...</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a scrollable list with title &lt;name&gt; which contains the 
listitem elements in &lt;block&gt;.

DLDialog orders the list items in a column in this rectangle.

The -var argument specifies a variable named &lt;varname&gt;.

At creation this variable will be read and if set to a number(s), the 
listitem(s) with this number(s) will be activated per default.

If the dialog exits the variable will be set to the number(s) of the 
selected listitem(s).

E.g. TESTVAR="1 3 5".

The -multi argument enables multi line selection, where the line numbers,
that were selected, are stored space separated in the variable.

In tvision mode <bf>F7</bf> marks all, <bf>F8</bf>unmarks all and 
<bf>F9</bf> toggles all.
</p>
	    <TAG><bf>combobox</bf> 
<bf>-var</bf><em> &lt;varname&gt;] 
</em><bf>&lcub; comboitem</bf> 
<em>&lsqb;&lt;args&gt;]</em><bf>;</bf><em> 
...</em><bf>&rcub;</bf></TAG>
	    <p>
Draws a combobox with title &lt;name&gt; which contains the comboitem 
elements in &lt;block&gt;.

The -var argument specifies a variable named &lt;varname&gt;.

At creation this variable will be read and if set to a number(s), 
the n&acute;th comboitem will be activated per default.

If the dialog exits the variable will be set to the number of the 
selected comboitem.

E.g. TESTVAR="1".
</p>
	  </descrip>
</p></sect1>
      <sect1><heading>Simple Commands</heading>
	<p>
<descrip>
	    <TAG><bf>button</bf> <em>&lt;name&gt; 
&lsqb;</em><bf>-var </bf><em>&lt;varname&gt; 
&lsqb;</em><bf>-set</bf><em> &lt;value&gt;] 
&lsqb;</em><bf>-add </bf><em>&lt;value&gt;]] 
&lsqb;</em><bf>-exec </bf><em>&lt;executable&gt;] 
&lsqb;</em><bf>-image </bf><em>&lt;image file&gt;] 
&lsqb;</em><bf>-movie </bf><em>&lt;movie file&gt;] 
&lsqb;</em><bf>-sign </bf><em>] 
&lsqb;</em><bf>-exit</bf><em>]&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Draws a button labelled with &lt;name&gt;.

The -var argument specifies a variable named &lt;varname&gt;, which will
be set, if the button is pressed,&nbsp; to the either the &lt;value&gt; 
specified with -set

If instead of the -set argument -add is specified, the old value of 
the variable is not cleared but the &lt;value&gt; will be appended 
with a space as a separator.

The -exec argument specifies an executable, which will be executed if 
the button is pressed.

The -image argument specifies an image file, which will be displayed left to 
the text. If the -sign option is given additionally, the image will be 
displayed on top of the text.

The -movie argument specifies an animated image file, which will be 
displayed left to the text. If the -sign option is given additionally, 
the image will be displayed on top of the text.

The -exit argument means that the dialog will be terminated if the 
button is pressed.
</p>
	    <TAG><bf>checkbutton</bf> <em>&lt;name&gt; 
&lsqb;</em><bf>-var </bf><em>&lt;varname&gt; 
&lsqb;</em><bf>-set</bf> <em>&lt;value&gt;] 
&lsqb;</em><bf>-add </bf><em>&lt;value&gt;]]&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Draws a check button labelled with &lt;name&gt;.

Check buttons can only be grouped with the checklist command.

The -var argument specifies a variable named &lt;varname&gt;, which 
will be set if the button&nbsp; is selected to the either the &lt;value&gt;
specified with -set.

If instead of the -set argument -add is specified, the old value of the
variable is not cleared but the &lt;value&gt; will be appended with a 
space as a separator.

If the variable is already set to the value specified with -set or the 
variable contains a value specified with -add, the checkbutton is 
activated per default.
</p>
	    <TAG><bf>radiobutton</bf> <em>&lt;name&gt; 
&lsqb;</em><bf>-var </bf><em>&lt;varname&gt; 
&lsqb;</em><bf>-set</bf> <em>&lt;value&gt;] 
&lsqb;</em><bf>-add </bf><em>&lt;value&gt;]]&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Draws a radio button labelled with &lt;name&gt;.

Radio buttons can only be grouped with the radiolist command.

The -var argument specifies a variable named &lt;varname&gt;, which 
will be set ,if the button is selected, to the either the &lt;value&gt;
specified with -set.

If instead of the -set argument -add is specified, the old value of 
the variable is not cleared but the &lt;value&gt; will be appended 
with a space as a separator.

If the variable is already set to the value specified with -set or the 
variable contains a value specified with -add, the radiobutton is 
activated per default.

NOTE: If multiple radio buttons are activated per default, the last one 
set will only be activated.
</p>
	    <TAG><bf>comboitem</bf> <em>&lt;name&gt; 
&lsqb;</em><bf>-var </bf><em>&lt;varname&gt; 
&lsqb;</em><bf>-set</bf> <em>&lt;value&gt;] 
&lsqb;</em><bf>-add </bf><em>&lt;value&gt;]]&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Draws a combobox item labeled with &lt;name&gt;.

Comboitems can only be grouped with the combolist command.

The -var argument specifies a variable named &lt;varname&gt;, which 
will be set ,if the item is selected, to the either the &lt;value&gt;
specified with -set.

If instead of the -set argument -add is specified, the old value of 
the variable is not cleared but the &lt;value&gt; will be appended with 
a space as a separator.

If the variable is already set to the value specified with -set or the
variable contains a value specified with -add, the item is activated per
default.

NOTE: If multiple items are activated per default, the last one set will
only be activated.
</p>
	    <TAG><bf>listitem</bf> <em>&lt;name&gt; 
&lsqb;</em><bf>-var </bf> <em>&lt;varname&gt; 
&lsqb;</em><bf>-set</bf> <em>&lt;value&gt;] 
&lsqb;</em><bf>-add </bf><em>&lt;value&gt;]]&nbsp;
&lsqb;</em><bf>-exec </bf><em>&lt;executable&gt;] 
&lsqb;</em><bf>-image </bf><em>&lt;image file&gt;] 
&lsqb;</em><bf>-exit</bf><em>]&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Draws a listitem labeled with &lt;name&gt;.

listitems can only exists within a list block.

The -var argument specifies a variable named &lt;varname&gt;, which 
will be set ,if the button is selected, to the either the &lt;value&gt;
specified with -set.

If instead of the -set argument -add is specified, the old value of the
variable is not cleared but the &lt;value&gt; will be appended with a 
space as a separator.

If the variable is already set to the value specified with -set or the
variable contains a value specified with -add, the listitem is activated
per default.

NOTE: If multiple listitems are activated per default and -multi is not
set in the list, the last one set will only be activated.

The -image argument specifies an image file, which will be displayed left to 
the text. 

The -exec argument specifies an executable, which will be executed 
if the listitem is activated.

The -exit argument means that the dialog will be terminated 
if the listitem is double-clicked.

</p>
	    <TAG><bf>text</bf> <em>&lt;name&gt;&nbsp;</em><bf>;</bf></TAG>
	    <p>
Displays &lt;name&gt; as text. Should not be longer than 255 chars, 
because of some limitations in the tvision library!

Text can include newlines or backslashed characters, which will be 
transformed like in C strings. E.g. &bsol;n is newline, &bsol;t 
tabulator, etc.
</p>
	    <TAG><bf>textbox</bf> <em>&lt;name&gt;&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Displays &lt;name&gt; as text in a box with scrollbars, if needed.

Text can include newlines or backslashed characters, which will be 
transformed like in C strings. 
E.g. &bsol;n is newline, &bsol;t tabulator, etc.
</p>
	    <TAG><bf>textbox</bf> 
<bf>-file </bf><em>&lt;filename&gt;&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Displays the file &lt;filename&gt; as text in a box with scrollbars, 
if needed.
</p>
	    <TAG><bf>input</bf> 
<bf>-var </bf><em>&lt;varname&gt;
&lsqb;</em><bf>-passwd</bf><em>] &nbsp;
&lsqb;</em><bf>-length </bf><em>&lt;value&gt; 
&lsqb;</em><bf>-numeric</bf><em>] 
&lsqb;</em><bf>-ip</bf><em>]
</em><bf> ;</bf></TAG>
	    <p>
Displays an input field, which is named &lt;name&gt;.

If -passwd is specified, no text is shown.

If -length is specified, the field is &lt;varname&gt; long.

If -numeric is specified, only numeric input is accepted

If -ip is specified, only IP address formatted input is accepted

-ip and -numeric can&acute;t be used together!

The -var argument specifies a variable named &lt;varname&gt;, which 
will be set to the contents of the input field, if the dialog exits.

If the variable is already set it will be the default value for the 
input field.

The -exec argument specifies an executable, which will be executed 
if return is pressed or the dialog exits.

The -exit argument means that the dialog will be terminated 
if return is pressed.
</p>
	    <TAG><bf>image</bf> <em>&lt;name&gt;&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Displays an image with filename &lt;name&gt;.
</p>
	    <TAG><bf>movie</bf> <em>&lt;name&gt;&nbsp;
</em><bf>;</bf></TAG>
	    <p>
Displays an animated image with filename &lt;name&gt;.
</p>
	    <TAG><bf>gauge</bf> 
<bf>-var</bf><em> &lt;varname&gt; 
&lsqb;</em><bf>-exec</bf> <em>&lt;executable&gt;] 
&lsqb;</em><bf>-exit</bf><em>] 
</em><bf>;</bf></TAG>
	    <p>
Draws a meter labeled with &lt;name&gt;.&nbsp; The meter indicates the 
percentage.

The -exec argument specifies an executable, which will be executed 
immediately.

New percentages are read from standard input of the executable.
Integer or double values are accepted separated by spaces. Non-digit characters
will be over-read.
The meter is updated to reflect each new percentage.
The variable specified with the varname is set to the percentage, when 
the dialog exits or to the exit status of the executable, if it exits 
with a negative value.

If the -exit argument is set, the dialog will be exited if the -exec
child exits.
</p>
	    <!--
<TAG><bf>menuitem</bf> <em>&lt;name&gt; 
	    &lsqb;</em><bf>-global</bf><em>] 
	    &lsqb;</em><bf>-exec </bf><em>&lt;executable&gt;] 
	    &lsqb;</em> <bf>-exit</bf><em>] 
	  </em><bf>;</bf></TAG>
<p>
	    Installs a menu in either the current dialog or if -global specified for
	    the all dialogs.

	    The menuitem appears in the menu specified by the name. 
	    E.g. "&amp;File/&amp;Exit"
	    will create an entry "Exit" in the menu "File". If the sub menu or 
	    menu title does not exist, it will be created.

	    The -exec argument specifies an executable, which will be executed, if
	    the menu is selected.

	    If the -exit argument is set, the dialog (or all dialogs if defined 
	    -global) will be exited immediately or after the execution of an 
	    eventually specified -exec.
	  </p>
<TAG><bf>menucheck </bf><em>&lt;name&gt;</em> 
<bf>-var</bf>&nbsp;<em>&lt;varname&gt;&nbsp;
	    &lsqb;</em><bf>-set</bf> <em>&lt;value&gt;] 
	    &lsqb;</em><bf>-add </bf><em>&lt;value&gt;] 
	    &lsqb;</em><bf>-global</bf><em>]</em><bf> ;</bf></TAG>
<p>Installs a menu in either the current dialog or if -global 
	    specified for all dialogs.

	    The menucheck appears in the menu specified by the name. 
	    E.g. "&amp;Option/&amp;Foo"
	    will create an entry "Foo" in the menu "Option". 
	    If the sub menu or menu title does not exist, it will be created.

	    The -set argument specifies a variable that will be set if the check is
	    activated or unset if deactivated.
	  </p>
	    -->
	    <TAG><em>&lt;varname&gt;</em><bf>=</bf><em>&lt;value&gt; 
</em><bf>;</bf></TAG>
	    <p>
Sets the global variable &lt;varname&gt; to &lt;value&gt;.
</p>
	  </descrip>
</p>
      </sect1>
      <sect1><heading>Script Example</heading>
	<p>Has no sense ... just to demonstrate all language elements of DLDialog.
<code>
#!./dldialog -tf
 dialog "All GUI Elements" -width 100 -height 100 &lcub;
      col &lcub;
	 text "A Column"; 
	 button "Button 1 30%" -height 30;
	 button "Button 2 70%" -height 70;
      &rcub;
      
      text ""; //Spacer
      
      col &lcub;
	 text "A Row";
	 row -width 100 &lcub;
	    button "Button 1 20%" -width 20;
	    button "Button 1 30%" -width 30;
	    button "Button 2 50%" -width 50;
	 &rcub;
      &rcub;
      
      text ""; //Spacer
      
      col &lcub;
	 text "The Lists";
	 row -width 100 &lcub;
	    lv="2";
	    list "A &amp;List" -width 33 -var lv &lcub;
	       listitem "1. Listitem";
	       listitem "2. Listitem";
	       listitem "3. Listitem";
	    &rcub;
	    
	    text "  "; //Spacer
	    
            checkvar="1 3";
	    checklist "A &amp;Checklist" -var checkvar -width 33 &lcub;
	       checkbutton "&amp;1. checkbutton";
	       checkbutton "&amp;2. checkbutton";
	       checkbutton "&amp;3. checkbutton";
	    &rcub;
	    
	    text "  "; //Spacer
	    
	    radiovar="2";

	    radiolist "A &amp;Radiolist" -var radiovar -width 33 &lcub;
	       radiobutton "&amp;1. radiobutton";
	       radiobutton "&amp;2. radiobutton";
	       radiobutton "&amp;3. radiobutton";
	    &rcub;
	 &rcub;
     &rcub;
      
      text ""; //Spacer
      col &lcub;
         STATIC_GAUGE="50";
         text "Gauges";
         row &lcub; 
	   gauge  -exit -exec "sh -c 'for i in `seq 1 100`;do echo $i;sleep 1;done'";
           gauge  -var STATIC_GAUGE;
	 &rcub;
      &rcub;	 
      text ""; //Spacer
      row &lcub;
         text "ComboBox";
	 cb="2";
	 combobox -var cb &lcub;
	   comboitem "Item 1" -var ci -set "1"; 
	   comboitem "Item 2" -var ci -set "2"; 
	   comboitem "Item 3" -var ci -set "3"; 
	 &rcub;
      &rcub;	 
      text ""; //Spacer
      
      row -width 100 &lcub; 
	 text "Normal:"; 
	 iv="bla bla bla";
	 input -var iv;

	 text " Numeric:"; 
	 ivn="1234567890";
	 input -var ivn -numeric;
	 
	 text " IP:"; 
	 ivi="123.123.123.123";
	 input -var ivi -ip;
      &rcub;
   
      text ""; //Spacer
      
      row -width 100 &lcub;
	 button "&amp;OK - seen all" -exit;
	 button "&amp;Source" -exec "./dldialog <<EOF 
	   dialog \"Source\" -width 100 -height 100 &lcub;
		 textbox \"A TextBox\" -file \"../tests/test8\" -width 100 -height 100 ;
		 text \"\"; //Spacer
		 button \"OK\" -exit;
	   &rcub;
EOF";
	 button "&amp;Not OK - output is scrambled" -exit;
      &rcub;
&rcub;   
</code></p>
      </sect1></sect>
    <sect><heading>Questions and answers</heading>
      <sect1><heading>What is this start, stop for?</heading>
	<p>
If you plan to display several dialogs in your session, it is useful
to start a dialog server with:
<code>
if [ -z "$DLDIALOG_INFIFO" ]; then
  dld_waitforend="yes";
fi   

function dldialog_start () $lcub;
  ret=$($DLDIALOG --start $@)
  ERR="$?"
  if [ "$ERR" != "0" ]; then
    echo Exited with $ERR
    exit 10;
  fi
  eval "$ret"
  export DLDIALOG_INFIFO
  trap dldialog_stop EXIT
  trap dldialog_stop SIGCHLD
  trap dldialog_stop SIGPIPE
&rcub;

dldialog_start $ARGS
</code>
At the end of the script dldialog_stop is now called, which can look 
like this:
<code>
function dldialog_stop () &lcub;
  if [ "$dld_waitforend" = "yes" ]; then
     $DLDIALOG --wait
     dldirname=`dirname "$DLDIALOG_INFIFO"`
     if [ -d $dldirname ]; then 
       rm -fr $dldirname
     fi
  else    
     $DLDIALOG --stop  
  fi
&rcub;
</code>
All of these functions (and more) can be found in dldialog_funcs, which 
is in this documentation directory or in the tests directory of the 
source package.
</p>
      </sect1>
      <sect1><heading>How can I display a status box (info box)?</heading>
	<p>
You want the user to see, what is going on. OK here is an example:
<code>
#!/bin/sh

function infobox () &lcub;
  $(dldialog -q <<EOF
  dialog "Please wait...         " &lcub;
    text "$1";
    gauge -exit -exec "$2" ;
  &rcub;
EOF)  
&rcub;

infobox "Preparing the system" "echo 0;sleep 2;echo 50;sleep 2;echo 100;";

function testf () &lcub;
# Print the percent of completition
  echo 0;
# Do s.th. useful :)
  sleep 2;
# Print the percent of completition
  echo 50;
# Do s.th. useful :)
  sleep 2;
# Print the percent of completition
  echo 100;
&rcub;

declare -fx testf

infobox "Preparing the system" testf;
</code>
</p></sect1>
      <sect1><heading>How can I specify the geometry of the dialog in qt mode?</heading>
	<p>
Start dldialog with the -geometry in the EXTRA OPTIONS section. E.g.:
<code>
$ dldialog -q -- -geometry 640x480 << EOF
dialog "TEST" &lcub;
    text "TEST";
    button "&amp;OK" -exit;
&rcub;
EOF
</code>
</p></sect1>
      <sect1><heading>How can I change elements depending on others?</heading>
	<p>
Suppose you want to get the host name and domain name of a host. You want to
preset the domain name with the domain of the host name, once the user has
entered it.
<code>
#!/bin/sh

# Start the server
result=$(dldialog --start $@)
eval "$result"
export DLDIALOG_INFIFO

export OK="0";

while [ "$OK" != "1" ]; do

  result=$(dldialog <<EOF
  dialog "Maindialog" &lcub;
    hostname="$hostname";
    domain="$domain";
    text "";
      row &lcub;
        col &lcub;
          text "Hostname:";
          text "Domainname:";
        &rcub;
        col &lcub;
          input -var hostname -length 20 -exit;
          input -var domain -length 20;
        &rcub;
      &rcub;
      button "&amp;OK" -var OK -set "1" -exit;
  &rcub;
EOF)

  eval "$result"

  if [ -z "$domain" ]; then
    export domain=`echo $hostname|(IFS='.' read a b;echo $b)`;
  fi

done

dldialog --wait
</code>
<bf>Note:</bf> The user has to press return after entering the 
hostname to let the dialog exit.
</p></sect1>
      <sect1><heading>How can I configure my xterm to 
display nice colours?</heading>
	<p>Try to set the TERM variable to one of: xterm-color, 
color-xterm or rxvt. Best results are on Linux console or in a rxvt.
<code>
$ export TERM=xterm-color
</code>
</p></sect1>
      <sect1><heading>Why does my dialog start up so minimised?</heading>
	<p>
Same as below.
    </p></sect1>

      <sect1><heading>Why can't I see my list?</heading>
	<p>
If no -width and -height is specified the element shows up with it's 
smallest size. </p>
<p>Remember: -width and -height are relative to the element 
with the most inner &lcub;&rcub;. The dialog element's width and height 
tags are relative to the -geometry size (or as a default 600x400).</p>
<p>
Specifying -width and -height also gives dldialog a hint which elements
have to grow how much, if the dialog resizes.
</p>
<p>This one is ugly:<code>
dialog "Not so nice" &lcub;
  list "A very small list" &lcub;
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
  &rcub;
&rcub;
</code>
Here a nicer one:
<code>
dialog "Not so nice" -width 100 -height 100 &lcub;
  list "A very small list" -width 100 -height 100 &lcub;
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
    listitem "Item";
  &rcub;
&rcub;
</code>
    </p></sect1>

      <!-- <sect1><heading></heading>
    <p>
    </p></sect1>
      -->
    </sect>
    <sect><heading>NEWS</heading>
      <p>
<verb>
<!-- @include ../NEWS -->
</verb>
</p></sect>
    <sect><heading>The Change Log</heading>
      <p>
<verb>
<!-- @include ../ChangeLog -->
</verb>
</p></sect>
    <sect><heading>The TODO List</heading>
      <p>
<verb>
<!-- @include ../TODO -->
</verb>
</p></sect>
    <sect><heading>COPYING</heading>
      <p>
<verb>
<!-- @include ../COPYING -->
</verb>
</p></sect>
<!--    <sect><heading>Appendix</heading>
      <p>
</p></sect>-->
  </article>
</linuxdoc>
<!-- Keep this comment at the end of the file
Local variables:
mode: sgml
sgml-set-face: t
sgml-omittag:t
sgml-shorttag:t
sgml-minimize-attributes:nil
sgml-always-quote-attributes:t
sgml-indent-step:2
sgml-indent-data:nil
sgml-parent-document:nil
sgml-exposed-tags:nil
sgml-local-catalogs:nil
sgml-local-ecat-files:nil
End:
-->

