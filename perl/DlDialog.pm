#!/usr/bin/perl
####################################################
#						   #
# File:		DlDialog.pm   		           #
# Authors:	Thomas Hagedorn                    #
#                                                  #
# Last change:  Mon 3 . 5.  1999                   #
#						   #
# DLD - German Linux Distribution -		   #
#						   #
# Copyright (c) 1993-1999  delix Computer GmbH	   #
#                          Schloßstraße 98	   #
#                          D-70176 Stuttgart	   #
# All rights reserved.				   #
#						   #
####################################################
#						   #
#  This program is free software; you can 	   #
#  redistribute it and/or modify it under the 	   #
#  terms of the GNU General Public License as 	   #
#  published by the Free Software Foundation; 	   #
#  either version 2 of the License, or (at your	   #
#  option) any later version.			   #
#       					   #
####################################################


package DlDialog;
use IPC::Open2;
use DlWidgetGroup;
use DlList;
use DlButtonGroup;
use DlButton;
use DlRadioList;
use DlCheckList;
use DlComboBox;
use DlFileSelect;
use DlInputField;
use DlMessage;
use DlHelp;
##############################################################################
# looks for dldialog

###############################################################################
  



##############################################################################
# Konstruktor new. Erzeugt ein neues DLDialog-Objekt. Dem Konstruktor kann
# ein Titel für das Objekt übergeben werden.
# Das Objekt wird mit addGroup() mit DlWidgetGroup-Objekten gefüllt.
#
# -> 0:   Referenzobjekt oder Klasse (immer dldialog)
#    1:   Titel der Dialogbox (optional)
# <- 0: Neues Objekt
#
sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();
    # Uebergebene oder ermittelte Attribute merken
    my $title = shift;
    $title = "TurboDialog" unless $title;
    $self->{_dialogtitle}    = $title;
    my $orient = shift;
    if ($orient =~ /^r/i) {$orient = 'row'}
    if ($orient =~ /^c/i) {$orient = 'col'}
    if ($orient =~ /^f/i) {$orient = 'form'}
    $self->{_orient} = $orient || 'col';
    # DLDialog-Versin prüfen
    my $version = `rpm -q dldialog`;
    unless ($version =~ /0\.8/) {$self->{_dialogprefix}='dialog'}

    $self->{_caller_package} = $package;
    bless($self, $class);
    # set the default image
    $self->{_imagedir} = "../icons";
    $self->{_image} = "DLD.xpm";
    return $self;
}

##############################################################################
# Setzt den Titel der Dialogbox neu.
#
# -> 0:   Referenzobjekt oder Klasse
#    1:   Titel der Dialogbox
# <-  :   alter Titel der Dialogbox | ""
#
sub setTitle {
  my ($self,$text) = @_;               # OO: zugehoeriges Objekt holen
  my $oldtitle = $self->getTitle();
  $self->{_dialogtitle} = $text;
  return $oldtitle;
}

##############################################################################
# Gibt den Titel der Dialogbox zurück.
#
# -> 0:   Referenzobjekt oder Klasse
# <-  :   Titel der Dialogbox
#
sub getTitle {
  my $self = shift;
  my $title = $self->{_dialogtitle};
  return $title;
}

##############################################################################
# Setzt eine Callbackfunktion
#
# -> 0:   Referenzobjekt oder Klasse
# -> 1:   Name der Funktion
#
sub setCallback {
  my $self = shift;
  my $callback = shift;
  $self->{_callback} = $self->{_caller_package}."::".$callback;
}

##############################################################################
# Setzt den Text der Dialogbox .
#
# -> 0:   Referenzobjekt oder Klasse
#    1:   Text der Dialogbox

sub setText {
  my $self = shift;
  $self->{_text} = shift,
}

##############################################################################
# Fügt der Dialogbox eine neue DlWidgetGroup hinzu.
#
# -> 0:   Referenzobjekt oder Klasse
#    1:   DlWidgetGroup
#    2:   Position im WidgetStack
# <-  :   Anzahl der DlWidgetGroup-Objekte
#

sub addGroup {
  my $self = shift;
  my $widget = shift;
  my $pos = shift;
  if ($pos > 0) {
    if ($self->{_Reftable}[$pos-1] eq 1) {
      return 0
    }
    else {
      $self->{_Widgets}[$pos-1] = $widget;
    }
  }
  else {
    push @{$self->{_Widgets}}, $widget;
    $pos = $#{$self->{_Widgets}}+1;
  }
  $self->{_Reftable}[$pos-1] = 1;
  foreach $element (@{$widget->{_elements}}) {
    if ($element->{_var}) { push @{$self->{_vars}}, $element->{_var} } 
  }
  if ($widget->{_var}) { push @{$self->{_vars}}, $widget->{_var} }
  if (@{$widget->{_vars}}) {
    push @{$self->{_vars}}, @{$widget->{_vars}}    
  }
  
  return $pos;
}

##############################################################################
# Entfernt eine DlWidgetGroup der Dialogbox.#
# -> 0:   Referenzobjekt oder Klasse
#    1:   Nummer der DlWidgetGroup, die entfernt wird 
# <-  :   Nummer der DlWidgetGroup, die entfernt wurde 
#

sub removeGroup {
  my $self = shift;
  my $widgetnr = shift;
  if ($widgetnr <= 0) {return 0}
  $widgetnr--;
  unless ($self->{_Reftable}[$widgetnr]) { return 0}
  if ($widgetnr eq $#{$self->{_Widgets}}) { # ist hinterstes Widget
    pop @{$self->{_Widgets}};
    pop @{$self->{_Reftable}};
  }
  else {
    $self->{_Reftable}[$widgetnr] = 0;
    undef $self->{_Widgets}[$widgetnr];
  }
    return $widgetnr+1;
}


##############################################################################
# sets the image of the dialog which is displayed at the left side of
# the dialog, substitutes the defaultimage.
# returns the substituted image or 1 if the image could be set

sub setImage {
  my $self  =shift;
  my $image = shift;
  if ( -f $image ) {
    my $oldimage = $self->{_image} || 1;
    $self->{_image}  =$image;
    return $oldimage;
  }
  else { return 0};
}

##############################################################################
# returns the current image af the dialog

sub getImage {
  my $self  =shift;
  return $self->{_image};
}


##############################################################################
# Fügt der Dialogbox einen Hilfetext hinzu
# Wenn ein Hilfetext gesetzt wird, wird automatisch der
# 'Hilfe'-Button angezeigt
# Übergeben wird entweder ein Textstring, der dan zur Anzeige kommt, 
# oder der Pfad einer Datei, die den Hilfetext enthält 
# 
sub setHelp {
  my $self = shift;
  my $helpfile = shift;
  $helpfile =~ s/^~/$ENV{HOME}/;
  $rundir = `pwd`;
  chomp $rundir;
  $helpfile =~ s/^\./$rundir/;
  $self->{_help} = new DlHelp($helpfile);
}

##############################################################################
# Fügt der Dialogbox ein bereits exixtierendes Hilfe-Widget hinzu
# wird nur intern verwendet von DlWizzard

sub setHelpWidget {
  my $self = shift;
  $self->{_help} = shift;
}


##############################################################################
# Bringt den Dialog zur Anzeige. Dazu werden alle eingetragenen
# Eingabevariablen in Umgebungsvariablen ueberfuehrt , der Dialog
# aus den einzelnen Objekten zusammengebaut und danach DLDialog
# aufgerufen. Dann wird der Rueckgabestring geparst und in die entsprechenden
# Perl-Variablen ueberfuehrt.
#
# -> 0:   Referenzobjekt
# <-  :   void
#

sub show {
    my ($self) = shift;                 # OO: zugehoeriges Objekt holen
    my $param = shift;
    my $caller_package = $self->{_caller_package};
    # Confirm-Buttons hinzufügen
    my $spacer = new DlWidgetGroup('col', '');
    my $spacer2 = new DlWidgetGroup('row', '', 100, 100);
    my $confirm = new DlButtonGroup('row',"","","_confirm", 10, 100);
    $spacer->insertElement($spacer2, $confirm);
    $self->{help} = '';
    $self->{back} = '';
    $self->{next} = '';
    $self->{cancel} = '';
    $self->{ok} = '';
    if ($self->{_help}) {
      $self->{help} = $confirm->insertButton("&Hilfe");
      $confirm->setImage($self->{help}, "$self->{_imagedir}/hilfe.xpm");
    }
    unless ($param eq 'start') {
      $self->{back} = $confirm->insertButton("&Zurück");
      $confirm->setImage($self->{back}, "$self->{_imagedir}/zurueck.xpm");
    }
    if (($param eq 'wizzard') || ($param eq 'start')) {
      $self->{next} = $confirm->insertButton("&Weiter");
      $confirm->setImage($self->{next}, "$self->{_imagedir}/weiter.xpm");
    }
    if ( ($param eq 'end')) {
      $self->{ok} = $confirm->insertButton("&Ok");
      $confirm->setImage($self->{ok}, "$self->{_imagedir}/exit.xpm");
    }
    if (($param eq 'wizzard') || ($param eq 'start') || ($param eq 'end')) {
      $self->{cancel} = $confirm->insertButton("&Abbrechen");
      $confirm->setImage($self->{cancel}, "$self->{_imagedir}/delete.xpm");
    }
    unless (($param eq 'wizzard') || ($param eq 'start') || ($param eq 'end')) {
      $self->{ok} = $confirm->insertButton("&Ok");
      $confirm->setImage($self->{ok}, "$self->{_imagedir}/exit.xpm");
    }
#    $confirmButtons = addGroup($self, $spacer);
    # Alle Eingabevariablen in Umgebungsvariablen schreiben:
    foreach $var (@{$self->{_vars}}) {
      next unless $var;
	$ENV{$var} = $ {$caller_package . "::" . $var};
	$val = $ {$caller_package . "::" . $var};
#	print "Var $var is $val\n";
    }
    # Den Dialog zusammensetzen:
    my $dialog = " { col { ";
    $dialog .= "row -width 100 -height 100 {
 col -height 100 { col -height 100 {}
	    image \"$self->{_imagedir}/$self->{_image}\"; }";
    $dialog .= " $self->{_orient} {";
    if ($self->{_text}) {$dialog .="text \"$self->{_text}\";"}
    my $size = $#{$self->{_Widgets}};
    for ($i=0;$i<=$size;$i++) {
      if ($self->{_Reftable}[$i] eq 0) {next};
      $widget = $self->{_Widgets}[$i];
      #    foreach $widget (@{$self->{_Widgets}}) {
      #      next unless $widget->getCode();
#      print "get code for widget Nr. $i: $widget, refstate is $self->{_Reftable}[$i]\n";
      $dialog .= $widget->getCode()."\n";
    }
    $dialog .="}}". $spacer->getCode()."\n";


    $dialog .= "}}";
    # Dialogbox zusammensetzen
    my $dialogtext = "$self->{_dialogprefix} \"$self->{_dialogtitle}\"\n$dialog";
#    print "Wir haben: $dialogtext\n";                   #debug
    # DLDialog-Prozess starten...
    for (;;) {
      $ENV{_confirm}="";
      open2('RDR', 'WTR', "/usr/bin/dldialog -$dialogoption");
      print WTR $dialogtext;
      close (WTR);
      
      # Rueckgabe lesen und auswerten
      @lines=<RDR>;
      close (RDR);
      removeGroup($self, $confirmButtons);
      $self->eval_result(@lines);
      $self->{result} = $_confirm;
      last unless ($self->{help} && ($_confirm eq $self->{help}))
    }
    if ($_confirm) {
#      print "DlDialog: confirm is $_confirm\n";
      if ($_confirm eq $self->{back}) {return 'back'}
      elsif ($_confirm eq $self->{next}) {return 'next'}
      elsif ($_confirm eq $self->{cancel}) {return 'cancel'}
      elsif ($_confirm eq $self->{ok}) {return 'ok'}
    }
    else {return 'signal'}
  }


##############################################################################
# Auswerten der Ausgaben von DLDialog. Dabei handelt es sich um eine Reihe von
# Variablenzuweisungen in Shellnotation (z.B. name="till"), die in
# gleichnamige Perl-Variablen ueberfuehrt werden muessen. Nach dem Aufruf 
# dieser Funktion mit dem obigen String ist eine Perl-Variable $name definiert,
# die den Inhalt "till" traegt. Diese Variable muss im Scope des Aufrufers 
# angelegt werden.
#
# -> 0-n: mehrzeilige Strings, die maximal eine Zuweisung pro Zeile
#         enthalten duerfen.
# 
sub eval_result
{
    my $self = shift;                 # OO: zugehoeriges Objekt holen
    my $i;
    my @lines;
    my $tmp;
    my %var;
    my $caller_package = $self->{_caller_package};
#    print "Caller is $caller_package\n";

    # Setzt alle uebergebenen Parameter zu einem langen Gesamtstring zusammen
    # und trennt diesen in einzelne Zeilen auf.
    @lines = split("\n", join("\n",@_) );
    chomp(@lines);

    # ... dann alle Variablenzuweisungen raussuchen und umsetzen
    foreach (@lines) {
      /^\s*([^=]*)=(.*)/s;
      $vname = $1;
      $value = $2;
      eval "\$$vname = '';";
      eval "\$" . $caller_package . "::$vname = '';";
      # setzt ungesetzte Variablen auf '' (wichtig für Checkboxen)
      if ( $value =~ /'([^';]+)/ ) {         # wenn Variable nicht leer
        $var{$vname}=$1;
	$tmp .= "\$" . $caller_package . "::$vname = $value;";}
      shift @lines;                          # sonst wird der Wert zu Variablen
   }

    # ... und auswerten...
    foreach $vname (sort keys %var) {
       $$vname = $var{$vname};                 # lokale Perl-Variable erzeugen
    }
    eval $tmp;
	if (($self->{_help}) && ($_confirm eq $self->{help})) {
    # Hilfe anzeigen und zurück zum Dialog
	  $self->{_help}->show();
	}

}

1;

