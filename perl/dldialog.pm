#!/usr/bin/perl
####################################################
#						   #
# File:		dldialog.pm   		           #
# Authors:	Till Bubeck                        #
#                                                  #
# Last change:  Sun Jan  3 23:06:43 CET 1999       #
#						   #
# DLD - German Linux Distribution -		   #
#						   #
# Copyright (c) 1993-1999  delix Computer GmbH	   #
#                          Schloﬂstraﬂe 98	   #
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


##############################################################################
# In diesem Modul wird eine objektorientierte Kapsel fuer DLDialog angeboten.
# Dazu wird fuer jeden gewuenschten DLDialog ein eigenes Perl-Objekt angelegt,
# dass alle Informationen fuer den jeweiligen Dialog mit sich traegt. Durch
# Aufruf der Methode "show()" kann der gewuenschte Dialog zur Anzeige gebracht
# werden.
#
# Beispiel fuer die Verwendung von DLDialog in Perl:
#
#   require "dldialog.pm";
#
#   $d = new dldialog(<<EOF, "namen");
#   {
#       text "Bitte geben Sie Ihren Namen ein:";
#       input -var "namen";
#   }
#   EOF
#
#   $namen = "bubeck";                        # Default setzen
#   $d->show();                               # Dialog anzeigen
#   print "Hello world, $namen\n";            # Ergebnis auswerten
#

package dldialog;
use IPC::Open2;

##############################################################################
# Konstruktor new. Erzeugt ein neues DLDialog-Objekt. Neben dem Text der
# Dialogbox muss dem Konstruktor eine Liste von Ein/Ausgabe-Variablen
# uebergeben werden. Das DLDialog-Objekt merkt sich die Namen der Variablen
# als "Eingabewerte" fuer den eigentlichen DLDialog. Zu diesem werden die
# Variableninhalte ueber Umgebungsvariablen transportiert. DLDialog traegt
# einen Default in Eingabefelder ein, oder selektiert bestimmte Buttons, wenn
# Umgebungsvariablen den gewuenschten Wert tragen.
#
# Damit eine Verbindung zwischen den Perl-Variablen und den gleichnamigen
# Umgebungsvariablen hergestellt wird, muessen die Perl-Variablen an DLDdialog
# "gebunden" werden. Dazu dient diese Funktion.
#
# Es muss eine Liste von Variablennamen uebergeben werden, die
# Eingabeparameter an den gewuenschten DLDialog-Prozess transportieren sollen.
#
# -> 0:   Referenzobjekt oder Klasse (immer dldialog)
#    1:   Text der Dialogbox
#    2-n: Namen von Ein/Ausgabe-Variablen
# <- 0: Neues Objekt
#
sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene oder ermittelte Attribute merken
    $self->{_dialogtext}     = shift;
    $self->{_vars}           = [@_];       # Referenz auf Parameter merken
    $self->{_caller_package} = $package;

    bless($self, $class);
    return $self;
}

##############################################################################
# Setzt den Text der Dialogbox neu.
#
# -> 0:   Referenzobjekt oder Klasse
#    1:   Text der Dialogbox
# <-  :   void
#
sub setText 
{
    my ($self,$text) = @_;               # OO: zugehoeriges Objekt holen
    
    $self->{_dialogtext} = $text;
}

##############################################################################
# Bringt den Dialog zur Anzeige. Dazu werden alle eingetragenen
# Eingabevariablen in Umgebungsvariablen ueberfuehrt und danach der DLDialog
# aufgerufen. Dann wird der Rueckgabestring geparst und in die entsprechenden
# Perl-Variablen ueberfuehrt.
#
# -> 0:   Referenzobjekt
# <-  :   void
#
sub show
{
    my ($self) = shift;                 # OO: zugehoeriges Objekt holen
    my $caller_package = $self->{_caller_package};

    # Alle Eingabevariablen in Umgebungsvariablen schreiben:
    # print "Setze Umgebungsvariablen:\n";
    foreach $var (@{$self->{_vars}}) {
	$ENV{$var} = $ {$caller_package . "::" . $var};
	# printf "%20s = %s\n", "\$" . $var,$ {$caller_package . "::" . $var};
    }
    
    # DLDialog-Prozess starten...
    # print "Rufe jetzt auf: " , $self->{_dialogtext}, "\n";
    open2('RDR', 'WTR', '/usr/bin/dldialog -q');
    print WTR $self->{_dialogtext};
    close (WTR);

    # Rueckgabe lesen und auswerten
    @lines=<RDR>;
    close (RDR);
    $self->eval_result(@lines);
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
    my ($self) = shift;                 # OO: zugehoeriges Objekt holen
    local ($i);
    local (@lines);
    local ($tmp);
    my $caller_package = $self->{_caller_package};

    # Setzt alle uebergebenen Parameter zu einem langen Gesamtstring zusammen
    # und trennt diesen in einzelne Zeilen auf.
    @lines = split("\n", join("\n",@_) );
    chomp(@lines);

    # ... dann alle Variablenzuweisungen raussuchen und umsetzen
    for ( $i = 0; $i < @lines; $i++) {
	$lines[$i] =~ /^\s*([^=]*)=(.*)/s;
	if ( uc($1) eq "PATH" ) { 
	    print STDERR "forbidden assignment catched.";
	}
	$tmp .= "\$" . $caller_package . "::$1 = $2;";
   }

    # ... und auswerten...
    # print "Werte aus: $tmp\n";
    eval $tmp;
}

1; # Keep require happy

