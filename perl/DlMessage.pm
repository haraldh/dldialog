#!/usr/bin/perl
####################################################
#						   #
# File:		DlMessage.pm  	                   #
#

package DlMessage;
use IPC::Open2;
####################################################
#
# Gibt eine Nachricht aus und bietet je nach Aufruf 
# verschiedene Möglichkeiten an
#

sub show {
  my $self = shift;
  my $title = shift;
  my $text = shift;
  my $type = shift;
  my $hsize = shift;
  my $vsize = shift;
  my $yes = "&Ja";
  my $no = "&Nein";
  my $break = "&Abbruch";
  my $continue = "&Weiter";
  my $back = "&Zurück";
  # DLDialog-Versin prüfen
  my $version = `rpm -q dldialog`;
  unless ($version =~ /0\.8/) {$self->{_dialogprefix}='dialog'}
#  if ($hsize) {$dialogsize=" WIDTH '$hsize'"}
#  if ($vsize) {$dialogsize.=" height '$vsize'"}
  my $dialogoption = $ENV{DLDIALOG} || 'q';
  if ($type =~ /^[jy]/i) {  $type = 'yesno'}
  elsif ($type =~ /^b/i) {  $type = 'break'}
      my $dialogtext = "$self->{_dialogprefix} \"$title\" $dialogsize\n { 
    text  \"$text\"; 
    row { ";
  if ($type eq 'yesno') {
    $dialogtext .= "button \"$yes\" -var _msg -set \"yes\" -exit;
                    button \"$no\" -var _msg -set \"no\" -exit; }"}
  elsif ($type eq 'break') {
    $dialogtext .= "button \"$break\" -var _msg -set \"break\" -exit;
                    button \"$continue\" -var _msg -set \"continue\" -exit; }"}
  else {
    $dialogtext .= "button \"$back\" -var _msg -set \"back\" -exit;  }"}
  $dialogtext .= "}";

    open2('RDR', 'WTR', "/usr/bin/dldialog -$dialogoption");
    print WTR $dialogtext;
    close (WTR);
    @lines=<RDR>; 
    close (RDR);
    foreach $line (@lines) {
	$line =~ /^\s*([^=]*)=(.*)/s;
	$vname = $1;
	$value = $2;
	if ( $value =~ /'([^';]+)/ ){         # wenn Variable nicht leer
           $$vname = $1;
         }
      
    }
return $_msg;
}

1;
