#!/usr/bin/perl
####################################################
#						   #
# File:		DlHelp.pm        	           #
#

package DlHelp;
use IPC::Open2;
####################################################
#
# Konstruktor new: legt einen neue  DlHelp Dialog an und gibt
# die Referenz darauf zur�ck.
# �bergabeparameter:
# Helpfile: Datei, die den Hilfetext enth�lt.
# DlHelp wird von tdialog verwendet und dort indirekt �ber
# tdialog->sethelp() initialisiert und �ber 
# tdialog->{_help}->show() dargestellt

sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my $helpfile = shift;
    $self->{_helpfile} = $helpfile;
    # DLDialog-Versin pr�fen
    my $version = `rpm -q dldialog`;
    unless ($version =~ /0\.8/) {$self->{_dialogprefix}='dialog'}

    $self->{_caller_package} = $package;
    bless($self, $class);
    $self->parse_helpfile();
    return $self;
    
  }

sub parse_helpfile {
  my $self = shift;
  my @tmp = `cat $self->{_helpfile}`;
  foreach (@tmp) {
    next if (/^#/);
    if (/^<title>\s*(.+)/) { 
      $self->{_title} = $1;
      next; }
    if (/^<\s*(.+)>/) {
      $top=$1;
      push @topics, $top;
      next; }
    push  @{$text->{$top}}, $_;
  }
}
      

sub show {
     my ($self) = shift;
     my $top = shift;
     unless ($_topic) { $_topic = $top || $topics[0] }
     my $dialogoption = $ENV{DLDIALOG} || 'q';
     $_help="";
     $chooseit = "W�hlen Sie ein Hilfekapitel";
     $content = "Inhalt";
     $showit = "anzeigen";
     $back = "&Zur�ck";
     if (@topics) {
       $combo = "text \"$chooseit\";
       row {
       combobox \"content\" { ";
       foreach $item (@topics) { $combo.="comboitem \"$item\" -var _topic -set \"$item\"; " }
       $combo .=" } button \"$showit\" -var _help -set \"show\" -exit;  }";
     }
  until ($_help eq 'back') { 
    $ENV{_topic}=$_topic;
    my $dialogtext = "$self->{_dialogprefix} \"$self->{_title}\"\n { $combo
    textbox  \"@{$text->{$_topic}}\"; 
    button \"$back\" -var _help -set \"back\" -exit;  }";
#    print "HELP:Wir haben: $dialogtext\n";
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
    }
return $top;
}
 



1; # Keep require happy
